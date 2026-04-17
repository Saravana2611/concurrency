#include <iostream>

#include "Worker.hpp"
#include "Utils.hpp"

Worker::Worker(int id, std::shared_ptr<MessageQueue> queue) : id_(id), queue_(queue)
{
}

Worker::~Worker()
{
}

void Worker::operator()()
{
    std::cout << "Worker " << id_ << ": Starting to consume items." << std::endl;
    while (true)
    {
        const auto item = queue_->waitAndRemoveItem();
        if (not item)
        {
            std::cout << "Worker " << id_ << ": Received exit signal, stopping." << std::endl;
            break;
        }
        item();
    }
}
