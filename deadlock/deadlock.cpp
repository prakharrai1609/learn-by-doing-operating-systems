#include <iostream>
#include <queue>
#include <mutex>
#include <cstdlib>
#include <thread>

using namespace std;

const int THREAD_COUNT = 6;
const int RECORD_COUNT = 3;

typedef struct {
    mutex lock;
} Record;

typedef struct {
    Record record[RECORD_COUNT];
} Database;

Database db;

void acquireLock(int id, int recId) {
    cout << "Thread " << id << " wants to acquire lock on record id " << recId << endl;
    db.record[recId].lock.lock();
    cout << "Thread " << id << " acquired lock on record id " << recId << endl;
}

void releaseLock(int id, int recId) {
    cout << "Thread " << id << " released the lock on record id " << recId << endl;
    db.record[recId].lock.unlock();
}

// mimics load / work
void threadFunction(int id) {

    while (1) {
        int rec1 = rand() % 3;
        int rec2 = rand() % 3;

        if (rec1 == rec2) continue;

        // Comment this line to create a dead lock.
        // This is called "total ordering..."
        
        // if (rec1 > rec2) swap(rec1, rec2);

        acquireLock(id, rec1);
        acquireLock(id, rec2);

        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate some work

        releaseLock(id, rec2);
        releaseLock(id, rec1);

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate some work
    }

}

int main() {

    thread threads[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++) {
        threads[i] = thread(threadFunction, i);
    }

    for (int i = 0; i < THREAD_COUNT; i++) threads[i].join();

    return 0;
}
