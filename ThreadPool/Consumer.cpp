#include <iostream>

#include "Consumer.hpp"
#include "Utils.hpp"

Consumer::Consumer(int id, std::shared_ptr<MessageQueue> queue) : id_(id), queue_(queue)
{
}

Consumer::~Consumer()
{
}

void Consumer::operator()()
{
    std::cout << "Consumer " << id_ << ": Starting to consume items." << std::endl;
    while (true)
    {
        const auto item = queue_->waitAndRemoveItem();
        if (not item)
        {
            std::cout << "Consumer " << id_ << ": Received exit signal, stopping." << std::endl;
            break;
        }
        item();
    }
}
