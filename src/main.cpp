#include <iostream>
#include "../inc/Queue.h"
#include <chrono>
#include <thread>

using namespace std;

/* Queue writing thread. Push() every four elements. As size limit is 2, will wait for reading thread to pop elements. */
void WriteThread(Queue<int>* Fifo) {
    Fifo->Push(10);
    Fifo->Push(20);
    Fifo->Push(30);
    Fifo->Push(40);
}


/* Queue reading thread. Pop() every 0.5 seconds for better visualization. */
void ReadThread(Queue<int>*Fifo){
    /* Create a delay on this thread of 0.5s to see the impact */
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    /* Queue pop */
    Fifo->Pop();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    Fifo->Pop();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    Fifo->Pop();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    Fifo->Pop();
}

int main() {

    cout << "Multi-threaded element queue in C++. Bosch interview." << endl;


    /* Initialize the queue with a size of 2 */
    Queue<int> *QueueManagement = new Queue<int>(2);

    cout << "\nQueue initialized with a size of " << QueueManagement->Size() << "." << endl;

    /* Create a thread for writting */
    std::thread t1(WriteThread, QueueManagement);
    /* Create a thread for reading */
    std::thread t2(ReadThread, QueueManagement);


    /* Join in order not to terminate with error */
    t1.join();
    t2.join();

    return 0;
}

