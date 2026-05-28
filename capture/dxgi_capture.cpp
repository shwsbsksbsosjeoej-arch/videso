#include "dxgi_capture.h"
#include <Windows.h>

DXGICapture::DXGICapture() = default;

bool DXGICapture::Init() {
    HRESULT hr = D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
        D3D11_SDK_VERSION, &m_device, nullptr, &m_context);
    if (FAILED(hr)) return false;

    Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
    m_device.As(&dxgiDevice);
    Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
    dxgiDevice->GetParent(IID_PPV_ARGS(&adapter));
    Microsoft::WRL::ComPtr<IDXGIOutput> output;
    adapter->EnumOutputs(0, &output);

    Microsoft::WRL::ComPtr<IDXGIOutput1> output1;
    output.As(&output1);

    output1->DuplicateOutput(m_device.Get(), &m_duplication);

    DXGI_OUTDUPL_DESC desc;
    m_duplication->GetDesc(&desc);
    m_width = desc.ModeDesc.Width;
    m_height = desc.ModeDesc.Height;

    return true;
}

bool DXGICapture::Capture(cv::Mat& mat) {
    if (!m_duplication) return false;
    Microsoft::WRL::ComPtr<IDXGIResource> resource;
    DXGI_OUTDUPL_FRAME_INFO info;
    HRESULT hr = m_duplication->AcquireNextFrame(100, &info, &resource);
    if (FAILED(hr)) return false;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
    resource.As(&tex);
    D3D11_TEXTURE2D_DESC desc = {};
    tex->GetDesc(&desc);

    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    desc.Usage = D3D11_USAGE_STAGING;
    desc.BindFlags = 0;
    desc.MiscFlags = 0;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> cpuTex;
    m_device->CreateTexture2D(&desc, nullptr, &cpuTex);
    m_context->CopyResource(cpuTex.Get(), tex.Get());

    D3D11_MAPPED_SUBRESOURCE mapped = {};
    hr = m_context->Map(cpuTex.Get(), 0, D3D11_MAP_READ, 0, &mapped);
    if (FAILED(hr)) {
        m_duplication->ReleaseFrame();
        return false;
    }

    cv::Mat tmp(m_height, m_width, CV_8UC4, mapped.pData, mapped.RowPitch);
    cv::cvtColor(tmp, mat, cv::COLOR_BGRA2BGR);

    m_context->Unmap(cpuTex.Get(), 0);
    m_duplication->ReleaseFrame();

    return true;
}

void DXGICapture::Release() {
    m_duplication.Reset();
    m_context.Reset();
    m_device.Reset();
}

DXGICapture::~DXGICapture() {
    Release();
}
