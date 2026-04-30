#include <memory>

#include "MessageQueue.hpp"

class Worker
{
private:
    int id_;
    std::shared_ptr<MessageQueue> queue_;

public:
    Worker(int id, std::shared_ptr<MessageQueue> queue);
    ~Worker();
    void operator()();
};
