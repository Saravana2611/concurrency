#pragma once

#include <mutex>
#include <string>
#include <queue>
#include <optional>

class MessageQueue
{
        const int size_;
        std::mutex mutex_;
        std::queue<std::string> queue_;
    public:
        MessageQueue();
        MessageQueue(const int size);
        bool addItem(const std::string& item);
        std::optional<std::string> removeItem();
};