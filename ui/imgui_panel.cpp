#include "imgui_panel.h"
#include <imgui.h>
#include <opencv2/opencv.hpp>

// 假定 ImGui 和渲染集成已在主循环初始化完毕

void ImGuiPanel::Update(const cv::Mat& frame, const std::vector<std::vector<cv::Point>>& contours, const std::vector<cv::Point>& centers, const cv::Mat& mask) {
    // 展示调试图片与检测目标
    if (ImGui::Begin("目标检测调试")) {
        ImGui::Text("frame: %dx%d", frame.cols, frame.rows);
        ImGui::Text("目标数: %d", (int)centers.size());
        for (int i = 0; i < centers.size(); ++i)
            ImGui::Text("center[%d]: (%d, %d)", i, centers[i].x, centers[i].y);
        // 若有集成ImGui绘制纹理：此处可贴图，否则注释掉
        //ImGui::Image(...);
    }
    ImGui::End();
}

void ImGuiPanel::Run(const std::function<void()>& onUpdate) {
    // 标准ImGui应用消息循环或挂到主渲染线程中
    while (true) {
        // ...事件处理和帧刷新...
        onUpdate();
        // ImGui::Render();
        // ...sleep or swap...
    }
}
