#include "Utils.h"
#include <chrono>
#include <thread>

void WaitTime(float seconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(seconds * 1000)));
}
