#include <memory>

#include "MessageQueue.hpp"

class Producer
{
    std::shared_ptr<MessageQueue> queue_;
    int id_;

public:
    Producer() = delete;
    Producer(int id, std::shared_ptr<MessageQueue> queue);
    void operator()();
};