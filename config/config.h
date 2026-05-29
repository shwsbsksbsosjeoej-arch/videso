#pragma once
#include <string>

struct Config {
    int h_min = 20, h_max = 40, s_min = 100, s_max = 255, v_min = 150, v_max = 255;
    int fire_key = 0x58; // VK_X
    int fire_mode = 1; // 1=单发 2=连发
    bool enable = true;
    std::string profile_path = "settings.json";
    // 更多参数..
};

bool LoadConfig(Config& cfg, const std::string& path);
bool SaveConfig(const Config& cfg, const std::string& path);
