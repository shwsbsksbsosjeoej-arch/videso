#include "hsv_detector.h"

HSVDetector::HSVDetector() : h_min(20), h_max(40), s_min(100), s_max(255), v_min(150), v_max(255) {}

void HSVDetector::SetHSV(int hmi, int hma, int smi, int sma, int vmi, int vma) {
    h_min = hmi; h_max = hma; s_min = smi; s_max = sma; v_min = vmi; v_max = vma;
}

void HSVDetector::Detect(const cv::Mat& frame) {
    centers.clear();
    contours.clear();
    if (frame.empty()) return;
    cv::Mat hsv;
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
    cv::inRange(hsv,
        cv::Scalar(h_min, s_min, v_min),
        cv::Scalar(h_max, s_max, v_max), mask);

    cv::GaussianBlur(mask, mask, cv::Size(5, 5), 0);
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN,
                     cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

    std::vector<std::vector<cv::Point>> cs;
    cv::findContours(mask, cs, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (const auto& contour : cs) {
        double area = cv::contourArea(contour);
        if (area > 100) { // 面积过滤
            contours.push_back(contour);
            cv::Moments mu = cv::moments(contour);
            if (mu.m00 != 0)
                centers.emplace_back(int(mu.m10 / mu.m00), int(mu.m01 / mu.m00));
        }
    }
}

bool HSVDetector::HasTarget() const {
    return !centers.empty();
}

std::vector<std::vector<cv::Point>> HSVDetector::GetLastContours() const {
    return contours;
}

std::vector<cv::Point> HSVDetector::GetLastCenters() const {
    return centers;
}

cv::Mat HSVDetector::GetLastMask() const {
    return mask;
}
