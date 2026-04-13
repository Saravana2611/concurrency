#include <iostream>

#include "Consumer.hpp"

Consumer::Consumer(int id, std::shared_ptr<MessageQueue> queue) : id_(id), queue_(queue)
{
}

Consumer::~Consumer()
{
}

void Consumer::operator()()
{
    std::cout << "Consuming work";
}
