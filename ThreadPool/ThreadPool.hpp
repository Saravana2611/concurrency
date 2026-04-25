#include "MessageQueue.hpp"

#include <thread>
#include <memory>

class ThreadPool
{
private:
    std::shared_ptr<MessageQueue> queue_;
    int noOfWorkers_;
    std::thread monitorThread_;
    std::vector<std::thread> workerThreads_;
    void threadMonitor(std::shared_ptr<MessageQueue> queue);
public:
    ThreadPool(int poolSize, int noOfWorkers);
    void submit(std::function<void()> task);
    ~ThreadPool();
};