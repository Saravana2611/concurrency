#pragma once

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <string>
#include <queue>
#include <functional>
#include <optional>

class MessageQueue
{
    const int size_;
    bool stop_ = false;
    std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    std::queue<std::function<void()>> queue_;
    std::atomic<int> noOfItems_ = 0;

public:
    MessageQueue(const int size);
    void waitAndAddItem(std::function<void()> item);
    std::function<void()> waitAndRemoveItem();
    void shutdown();
    int getNoOfItems();
    bool isStopped();
};