#include "ThreadPool.hpp"
#include "Worker.hpp"

ThreadPool::ThreadPool(int poolSize, int noOfWorkers) : queue_(std::make_shared<MessageQueue>(poolSize)), noOfWorkers_(noOfWorkers)
{
    for (int i = 0; i < noOfWorkers_; ++i)
    {
        Worker newWorker(i, queue_);
        std::thread workerThread(std::move(newWorker));
        workerThreads_.push_back(std::move(workerThread));
    }
}

void ThreadPool::submit(std::function<void()> task)
{
    queue_->waitAndAddItem(std::move(task));
}

ThreadPool::~ThreadPool()
{
    queue_->shutdown();
    for (auto &workerThread : workerThreads_)
    {
        if (workerThread.joinable())
            workerThread.join();
    }
}