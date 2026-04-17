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

#if defined(USE_ONLY_MUTEX)
    for (int i = 0; i < NO_OF_WORKS; ++i)
    {
        randomDelay(100, 1000);
        std::cout << "Producer " << id_ << ": Adding item " << i << "." << std::endl;
        while (not queue_->addItem("Work " + std::to_string(i)))
        {
            randomDelay(100, 1000);
        }
    }
#elif defined(USE_COND_VAR)
    for (int i = 0; i < NO_OF_WORKS; ++i)
    {
        randomDelay(100, 1000);
        std::cout << "Producer " << id_ << ": Adding item " << i << "." << std::endl;
        queue_->waitAndAddItem("Work " + std::to_string(i));
    }
#else
#error "Define either USE_ONLY_MUTEX or USE_COND_VAR to select the producer implementation."
#endif
}
