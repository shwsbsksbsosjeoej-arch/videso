#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

class HSVDetector {
public:
    HSVDetector();
    void SetHSV(int h_min, int h_max, int s_min, int s_max, int v_min, int v_max);
    void Detect(const cv::Mat& frame);
    bool HasTarget() const;
    std::vector<std::vector<cv::Point>> GetLastContours() const;
    std::vector<cv::Point> GetLastCenters() const;
    cv::Mat GetLastMask() const;
private:
    int h_min, h_max, s_min, s_max, v_min, v_max;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Point> centers;
    cv::Mat mask;
};
