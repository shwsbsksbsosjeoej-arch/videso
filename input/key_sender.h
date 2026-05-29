#pragma once
#include <windows.h>

class KeySender {
public:
    void TriggerKey(int vk, int mode);
    // 可扩展: 鼠标侧键监听
};
