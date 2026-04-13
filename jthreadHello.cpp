#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

void hello(int thread_id = 0)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "Hello Concurrent World from thread " << thread_id << "\n";
}

int main()
{
    std::vector<std::jthread> threads;
    for (int i = 0; i < 100; i++)
    {
        std::jthread t(hello, i);
        threads.push_back(std::move(t));
        // t.detach();
    }

    for (auto &thread : threads)
    {
        // thread.join();
    }
    return 0;
}   