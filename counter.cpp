#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

static int counter = 0;
std::mutex counter_mutex;

void inc_counter(int val)
{
    std::lock_guard<std::mutex> lock(counter_mutex);
    std::cout << "Incrementing counter value by " << val << " in thread " << std::this_thread::get_id() << std::endl;
    for (int i = 0; i < val; i++)
    {
        counter += 1;
    }
}

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 2; i++)
    {
        std::thread t(inc_counter, 10000000);
        threads.push_back(std::move(t));
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    std::cout << "Final counter value is " << counter << std::endl;
    return 0;
}