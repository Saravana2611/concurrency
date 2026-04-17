#include <memory>

#include "MessageQueue.hpp"

const int NO_OF_WORKS = 10;

class Producer
{
    std::shared_ptr<MessageQueue> queue_;
    int id_;

public:
    Producer() = delete;
    Producer(int id, std::shared_ptr<MessageQueue> queue);
    void operator()();
};