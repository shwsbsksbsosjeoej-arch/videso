#include "capture/dxgi_capture.h"
#include "detection/hsv_detector.h"
#include "input/key_sender.h"
#include "ui/imgui_panel.h"
#include "config/config.h"
#include "utils/thread_pool.h"
#include "utils/logger.h"
#include <opencv2/opencv.hpp>
#include <thread>
#include <atomic>

Config g_config;
std::atomic<bool> running{true};

int main() {
    Logger::Init();
    Logger::Info("videso starting...");

    DXGICapture screen_cap;
    HSVDetector detector;
    KeySender key_sender;
    ImGuiPanel ui_panel;
    ThreadPool thread_pool(2);

    if (!screen_cap.Init()) {
        Logger::Error("DXGICapture init failed");
        return -1;
    }

    Logger::Info("Modules initialized.");

    thread_pool.enqueue([&]{
        while (running) {
            cv::Mat frame;
            if (screen_cap.Capture(frame)) {
                detector.Detect(frame);
                ui_panel.Update(frame, detector.GetLastContours(), detector.GetLastCenters(), detector.GetLastMask());
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });

    thread_pool.enqueue([&]{
        while (running) {
            if (detector.HasTarget()) {
                key_sender.TriggerKey(g_config.fire_key, g_config.fire_mode);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    });

    ui_panel.Run([&]{
        detector.SetHSV(g_config.h_min, g_config.h_max, g_config.s_min, g_config.s_max, g_config.v_min, g_config.v_max);
    });

    running = false;
    thread_pool.shutdown();
    Logger::Info("videso exited.");
    return 0;
}
