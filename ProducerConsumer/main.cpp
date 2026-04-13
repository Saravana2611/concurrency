#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "MessageQueue.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"

const int NO_OF_PRODUCERS = 5;
const int NO_OF_CONSUMERS = 5;
const int NO_OF_ITEMS = 10;
const int QUEUE_SIZE = 4;

int main() {
    
    std::shared_ptr<MessageQueue> queue = std::make_shared<MessageQueue>(QUEUE_SIZE);

    std::vector<std::thread> producerThreads;
    for (int i = 0; i < NO_OF_PRODUCERS; ++i) {
        Producer newProducer(i, queue);
        std::thread producerThread(std::move(newProducer));
        producerThreads.push_back(std::move(producerThread));
    }

    std::vector<std::thread> consumerThreads;
    for (int i = 0; i < NO_OF_CONSUMERS; ++i) {
        Consumer newConsumer(i, queue);
        std::thread consumerThread(std::move(newConsumer));
        consumerThreads.push_back(std::move(consumerThread));
    }

    for (auto& producerThread : producerThreads)
    {
        if (producerThread.joinable())
            producerThread.join();
    }

    for (auto& consumerThread : consumerThreads)
    {
        if (consumerThread.joinable())
            consumerThread.join();
    }

    return 0;
}