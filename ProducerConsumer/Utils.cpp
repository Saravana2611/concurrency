#include "Utils.hpp"

void randomDelay(int start, int end)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(start, end);
    std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
}