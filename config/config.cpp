#include "config.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool LoadConfig(Config& cfg, const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) return false;
    json j; in >> j;
    cfg.h_min = j.value("h_min", cfg.h_min);
    cfg.h_max = j.value("h_max", cfg.h_max);
    cfg.s_min = j.value("s_min", cfg.s_min);
    cfg.s_max = j.value("s_max", cfg.s_max);
    cfg.v_min = j.value("v_min", cfg.v_min);
    cfg.v_max = j.value("v_max", cfg.v_max);
    cfg.fire_key = j.value("fire_key", cfg.fire_key);
    cfg.fire_mode = j.value("fire_mode", cfg.fire_mode);
    cfg.enable = j.value("enable", cfg.enable);
    cfg.profile_path = j.value("profile_path", cfg.profile_path);
    return true;
}

bool SaveConfig(const Config& cfg, const std::string& path) {
    std::ofstream out(path);
    if (!out.is_open()) return false;
    json j = {
        {"h_min", cfg.h_min}, {"h_max", cfg.h_max},
        {"s_min", cfg.s_min}, {"s_max", cfg.s_max},
        {"v_min", cfg.v_min}, {"v_max", cfg.v_max},
        {"fire_key", cfg.fire_key},
        {"fire_mode", cfg.fire_mode},
        {"enable", cfg.enable},
        {"profile_path", cfg.profile_path}
    };
    out << j.dump(4);
    return true;
}
