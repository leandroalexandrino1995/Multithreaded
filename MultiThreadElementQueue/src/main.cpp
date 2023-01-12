#include <iostream>
#include "..\inc\Queue.h"
#include <thread>

using namespace std;

void WriteThread(Queue<int>* Fifo) {
    Fifo->Push(10);
    Fifo->Push(20);
    Fifo->Push(30);
    Fifo->Push(40);
}

void ReadThread(Queue<int>*Fifo){
    Fifo->Pop();
    Fifo->Pop();
    Fifo->Pop();
    Fifo->Pop();
}

int main() {

    cout << "Multi-threaded element queue in C++. Bosch interview." << endl;

    Queue<int> *QueueManagement = new Queue<int>(2);

    cout << "\nQueue initialized with a size of " << QueueManagement->Size() << "." << endl;


    std::thread t1(WriteThread, QueueManagement);
    std::thread t2(ReadThread, QueueManagement);

    t1.join();
    t2.join();

    return 0;
}

