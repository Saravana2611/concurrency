#include "ThreadPool.hpp"

#include <iostream>

const int NO_OF_CONSUMERS = 5;
const int NO_OF_ITEMS = 10;
const int QUEUE_SIZE = 4;

int main()
{
    ThreadPool pool(QUEUE_SIZE, NO_OF_CONSUMERS);

    for (int i = 0; i < NO_OF_ITEMS; ++i)
    {
        const auto task = [i]()
        {
            std::cout << "Main thread: Executing task for item " << i << "." << std::endl;
        };
        pool.submit(std::move(task));
    }
    return 0;
}