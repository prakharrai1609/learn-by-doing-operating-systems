#include <iostream>
#include <thread>

using namespace std;

const int THREAD_COUNT = 2;

int counter = 0;

void threadFunction() {
    counter++;
}

int main() {
    thread threads[THREAD_COUNT];
    for (int i = 1;;i++) {
        for (int i = 0; i < THREAD_COUNT; i++) {
            threads[i] = thread(threadFunction);
        }

        cout << "Iteration #" << i << ": counter = " << counter << endl;

        for (int i = 0; i < THREAD_COUNT; i++) {
            threads[i].join();
        }
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate some work
    }
}
