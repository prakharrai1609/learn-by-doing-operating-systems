### 1. Header Inclusions:

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
```

This section includes necessary header files for input/output, thread management, mutexes, and condition variables.

### 2. Semaphore Class Definition:

```cpp
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
```

Here, a Semaphore class is defined to manage access to a shared resource. It contains member functions for acquiring and releasing the semaphore.

The constructor Semaphore(int initialCount) initializes the semaphore with an initial count.
The acquire() function tries to acquire the semaphore. It uses a std::unique_lock to lock the associated mutex. If the semaphore count is zero, it waits on the condition variable until it's signaled (released by another thread).
The release() function releases the semaphore. It locks the mutex using std::lock_guard and increments the semaphore count. It then notifies one waiting thread using condition.notify_one().

### 3. Semaphore Initialization:

```cpp
Semaphore semaphore(2); // Initialize semaphore with a count of 2
```

An instance of the Semaphore class is created with an initial count of 2. This means that two threads can initially acquire the semaphore without waiting.

### 4. Worker Function:

```cpp
void worker(int id) {
    semaphore.acquire();
    std::cout << "Worker " << id << " acquired the semaphore." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate some work
    std::cout << "Worker " << id << " releasing the semaphore." << std::endl;
    semaphore.release();
}
```

The worker function simulates a thread performing some work. It starts by acquiring the semaphore using semaphore.acquire(), prints a message indicating that the worker has acquired the semaphore, simulates work with a 2-second delay, prints another message indicating that the worker is releasing the semaphore, and finally releases the semaphore using semaphore.release().

### 5. Main Function:

```cpp
int main() {
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
```

In the main function, three threads (t1, t2, and t3) are created, each invoking the worker function with different worker IDs. The join() method is called on each thread to wait for their completion before the program exits.

### 6. Execution:
The three worker threads attempt to acquire the semaphore. Since the semaphore's initial count is 2, the first two threads will acquire the semaphore immediately, while the third thread will wait until one of the first two threads releases it. This demonstrates the principle of synchronization and how the semaphore regulates access to the shared resource.

In summary, the code showcases the use of semaphores to coordinate access to a shared resource among multiple threads, preventing resource contention and potential issues like race conditions.
