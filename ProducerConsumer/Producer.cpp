#include <iostream>

#include "Producer.hpp"

Producer::Producer(int id, std::shared_ptr<MessageQueue> queue)
    : id_(id), queue_(queue)
{
}

void Producer::operator()()
{
    std::cout << "Adding this work";
}
