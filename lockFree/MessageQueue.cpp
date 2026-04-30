#include "MessageQueue.hpp"

#include <iostream>

MessageQueue::MessageQueue() : stop_(false)
{
    Node* dummy = new Node{nullptr, nullptr};
    head.store(dummy);
    tail.store(dummy);
}

void MessageQueue::enqueue(std::function<void()> item)
{
    Node* newNode = new Node{item, nullptr};
    while (true)
    {
        Node* last = tail.load();
        Node* next = last->next.load();

        if (last == tail.load())
        {
            if (next == nullptr)
            {
                if (last->next.compare_exchange_weak(next, newNode))
                {
                    tail.compare_exchange_weak(last, newNode);
                    noOfItems_++;
                    not_empty_.notify_one();
                    return;
                }
            }
            else
            {
                tail.compare_exchange_weak(last, next);
            }
        }
    }
}

std::function<void()> MessageQueue::dequeue()
{
    while (true)
    {
        Node* first = head.load();
        Node* last = tail.load();
        Node* next = first->next.load();
        if (first == head.load())
        {
            if (first == last)
            {
                if (next == nullptr)
                {
                    std::unique_lock<std::mutex> lock(mutex_);
                    not_empty_.wait(lock, [this]
                        { return noOfItems_ or stop_; });
                    if (stop_ and noOfItems_ == 0)
                    {
                        return nullptr;
                    }
                    continue;
                }
                tail.compare_exchange_weak(last, next);
            }
            else
            {
                std::function<void()> item = next->item;
                if (head.compare_exchange_weak(first, next))
                {
                    delete first;
                    noOfItems_--;
                    return item;
                }
            }
        }
    }
    
}

int MessageQueue::getNoOfItems()
{
    return noOfItems_.load();
}

void MessageQueue::shutdown()
{
    std::cout << "MessageQueue: Shutting down the queue." << std::endl;
    std::unique_lock<std::mutex> lock(mutex_);
    stop_ = true;
    lock.unlock();
    not_empty_.notify_all();
}

bool MessageQueue::isStopped()
{
    std::unique_lock<std::mutex> lock(mutex_);
    return stop_;
}