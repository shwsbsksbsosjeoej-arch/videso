#include "key_sender.h"
#include <thread>

void KeySender::TriggerKey(int vk, int mode) {
    INPUT inputK[2] = {};
    inputK[0].type = INPUT_KEYBOARD;
    inputK[0].ki.wVk = vk;
    inputK[0].ki.dwFlags = 0;

    inputK[1].type = INPUT_KEYBOARD;
    inputK[1].ki.wVk = vk;
    inputK[1].ki.dwFlags = KEYEVENTF_KEYUP;

    if (mode == 2) { // 连发
        for (int i = 0; i < 3; ++i) {
            SendInput(2, inputK, sizeof(INPUT));
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    } else { // 单发
        SendInput(2, inputK, sizeof(INPUT));
    }
}
