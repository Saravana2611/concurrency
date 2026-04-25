#include "ThreadPool.hpp"
#include "Worker.hpp"

#include <iostream>

ThreadPool::ThreadPool(int poolSize, int noOfWorkers) : queue_(std::make_shared<MessageQueue>(poolSize)), noOfWorkers_(noOfWorkers)
{
    for (int i = 0; i < noOfWorkers_; ++i)
    {
        Worker newWorker(i, queue_);
        std::thread workerThread(std::move(newWorker));
        workerThreads_.push_back(std::move(workerThread));
    }

    std::thread monitorThread(&ThreadPool::threadMonitor, this, queue_);
    monitorThread_ = std::move(monitorThread);
}

void ThreadPool::threadMonitor(std::shared_ptr<MessageQueue> queue)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        int noOfItems = queue->getNoOfItems();
        std::cout << "Thread Monitor: Number of items in the queue: " << noOfItems << "." << std::endl;
        if (queue->isStopped() and noOfItems == 0)
        {
            std::cout << "Thread Monitor: No more items to process. Exiting." << std::endl;
            break;
        }
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
    if (monitorThread_.joinable())
    {
        monitorThread_.join();
    }
}