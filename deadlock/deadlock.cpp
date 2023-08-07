#include <iostream>
#include <queue>
#include <mutex>
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
    
}

void threadFunction(int id) {

}

int main() {

    

    return 0;
}
