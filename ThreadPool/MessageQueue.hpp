#pragma once

#include <mutex>
#include <condition_variable>
#include <string>
#include <queue>
#include <functional>
#include <optional>

class MessageQueue
{
    const int size_;
    std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    std::queue<std::function<void()>> queue_;

public:
    MessageQueue();
    MessageQueue(const int size);
    void waitAndAddItem(const std::function<void()> &item);
    std::function<void()> waitAndRemoveItem();
};