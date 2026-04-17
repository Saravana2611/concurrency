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

#if defined(USE_ONLY_MUTEX)
        randomDelay(100, 200);
        const auto item = queue_->removeItem();
        if (item)
        {
            if (*item == "Exit")
            {
                std::cout << "Consumer " << id_ << ": Received exit signal, stopping." << std::endl;
                break;
            }
            std::cout << "Consumer " << id_ << ": Processing " << *item << "." << std::endl;
        }

#elif defined(USE_COND_VAR)
        const auto item = queue_->waitAndRemoveItem();
        if (item == "Exit")
        {
            std::cout << "Consumer " << id_ << ": Received exit signal, stopping." << std::endl;
            break;
        }
        std::cout << "Consumer " << id_ << ": Processing " << item << "." << std::endl;
#else

#error "Define either USE_ONLY_MUTEX or USE_COND_VAR to select the consumer implementation."
#endif
    }
}
