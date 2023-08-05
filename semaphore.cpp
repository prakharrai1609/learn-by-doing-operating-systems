#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdio>

using namespace std;

class Semaphore {
public:
    Semaphore(int initialCount) : count(initialCount) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mutex);
        while (count == 0) {
            condition.wait(lock);
        }
        count--;
    }

    void release() {
        std::lock_guard<std::mutex> lock(mutex);
        count++;
        condition.notify_one();
    }

private:
    int count;
    std::mutex mutex;
    std::condition_variable condition;
};

Semaphore semaphore(2); // Initialize semaphore with a count of 2

void worker(int id) {
    semaphore.acquire();
    std::cout << "Worker " << id << " acquired the semaphore." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate some work
    std::cout << "Worker " << id << " releasing the semaphore." << std::endl;
    semaphore.release();
}

int main() {

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
