#pragma once
#include <opencv2/core.hpp>
#include <wrl.h>
#include <d3d11.h>
#include <dxgi1_2.h>

class DXGICapture {
public:
    DXGICapture();
    bool Init();
    bool Capture(cv::Mat& mat);
    void Release();
    ~DXGICapture();
private:
    Microsoft::WRL::ComPtr<ID3D11Device>           m_device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>    m_context;
    Microsoft::WRL::ComPtr<IDXGIOutputDuplication> m_duplication;
    int m_width = 0, m_height = 0;
};
