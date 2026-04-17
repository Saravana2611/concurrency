#include <memory>

#include "MessageQueue.hpp"

class Consumer
{
private:
    int id_;
    std::shared_ptr<MessageQueue> queue_;

public:
    Consumer(int id, std::shared_ptr<MessageQueue> queue);
    ~Consumer();
    void operator()();
};