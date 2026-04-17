#include <iostream>

#include "Producer.hpp"
#include "Utils.hpp"

Producer::Producer(int id, std::shared_ptr<MessageQueue> queue)
    : id_(id), queue_(queue)
{
}

void Producer::operator()()
{
    std::cout << "Producer " << id_ << ": Starting to produce " << NO_OF_WORKS << " items." << std::endl;
    for (int i = 0; i < NO_OF_WORKS; ++i)
    {
        randomDelay(100, 1000);
        std::cout << "Producer " << id_ << ": Adding item " << i << "." << std::endl;
        const auto task = [id = id_, i]()
        {
            std::cout << "Producer " << id << ": Executing task for item " << i << "." << std::endl;
        };
        queue_->waitAndAddItem(std::move(task));
    }
}
