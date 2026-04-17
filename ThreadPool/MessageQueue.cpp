#include "MessageQueue.hpp"

MessageQueue::MessageQueue(const int size) : size_(size), stop_(false)
{
}

MessageQueue::MessageQueue() : size_(0), stop_(false)
{
}

void MessageQueue::waitAndAddItem(const std::function<void()> &item)
{
    std::unique_lock<std::mutex> lock(mutex_);
    not_full_.wait(lock, [this]
                   { return queue_.size() < size_ && not stop_; });
    if (stop_)
    {
        return;
    }
    queue_.push(item);
    lock.unlock();
    not_empty_.notify_one();
}

std::function<void()> MessageQueue::waitAndRemoveItem()
{
    std::function<void()> item;
    std::unique_lock<std::mutex> lock(mutex_);
    not_empty_.wait(lock, [this]
                    { return not queue_.empty() or stop_; });
    if (stop_ and queue_.empty())
    {
        return nullptr;
    }
    item = queue_.front();
    queue_.pop();
    lock.unlock();
    not_full_.notify_one();
    return item;
}

void MessageQueue::shutdown()
{
    std::unique_lock<std::mutex> lock(mutex_);
    stop_ = true;
    lock.unlock();
    not_empty_.notify_all();
    not_full_.notify_all();
}