#include <iostream>
#include <future>
#include <thread>
#include <chrono>

void asyncTask(std::promise<int> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(5));
    p.set_value(100);
}

int asyncTask2(const int& val)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return val;
}

int main() {
    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    std::thread t(asyncTask, std::move(promise));
    std::future<int> future2 = std::async(std::launch::async, asyncTask2, 10000);
    
    std::cout << "Waiting for the result..." << std::endl;
    int result = future.get();
    std::cout << "Result: " << result << std::endl;    
    t.join();


    std::cout << "Waiting for the result..." << std::endl;
    result = future2.get();
    std::cout << "Result: " << result << std::endl;  

    return 0;
}