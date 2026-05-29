#pragma once
#include <opencv2/core.hpp>
#include <vector>
#include <functional>

class ImGuiPanel {
public:
    void Update(const cv::Mat& frame, const std::vector<std::vector<cv::Point>>& contours, const std::vector<cv::Point>& centers, const cv::Mat& mask);
    void Run(const std::function<void()>& onUpdate);
};
