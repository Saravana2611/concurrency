#pragma once

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <string>
#include <functional>
#include <optional>

class MessageQueue
{
    struct Node
    {
        std::function<void()> item;
        std::atomic<Node*> next;
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;

    bool stop_ = false;
    std::mutex mutex_;
    std::condition_variable not_empty_;
    std::atomic<int> noOfItems_ = 0;

public:
    MessageQueue();
    void enqueue(std::function<void()> item);
    std::function<void()> dequeue();
    void shutdown();
    int getNoOfItems();
    bool isStopped();
};