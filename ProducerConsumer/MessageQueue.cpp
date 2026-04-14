#include "MessageQueue.hpp"

MessageQueue::MessageQueue(const int size) : size_(size)
{
}

MessageQueue::MessageQueue() : size_(0)
{
}

bool MessageQueue::addItem(const std::string &item)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.size() < size_)
    {
        queue_.push(item);
        return true;
    }
    return false;
}

std::optional<std::string> MessageQueue::removeItem()
{
    std::optional<std::string> item;
    std::lock_guard<std::mutex> lock(mutex_);
    if (not queue_.empty())
    {
        item = queue_.front();
        queue_.pop();
    }
    return item;
}