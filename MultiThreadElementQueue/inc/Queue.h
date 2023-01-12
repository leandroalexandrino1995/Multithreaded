// Queue.h
#pragma once
#include <iostream>
#include <queue>
#include <mutex>

using namespace std;
template <typename T>

class Queue
{
private:
	int SizeLimit = 0;
	std::queue<int> FIFO;
	std::mutex MutexLocker;
	std::condition_variable PushNotifier;
	std::condition_variable PopNotifier;

public:
	Queue(int size) {
		SizeLimit = size;
		PushNotifier.notify_one();

	}

	int Count(void)
	{
		return FIFO.size();
	};

	int Size(void)
	{
		return SizeLimit;
	};

	void Push(T element)
	{
		std::unique_lock<std::mutex> mlock(MutexLocker);
		while (FIFO.size() == SizeLimit) 
		{
			cout << "Queue is full. Waiting for the reading thread!" << endl;
			PushNotifier.wait(mlock);
		}
		FIFO.push(element);
		mlock.unlock();     
		cout << "Element " << element << " added to the queue. New size: " << FIFO.size() << "." << endl;
		PopNotifier.notify_one(); // notify one waiting thread

	};

	T Pop(void) {

		std::unique_lock<std::mutex> mlock(MutexLocker);
		while (FIFO.empty())
		{
			cout << "Queue is empty. Waiting for the writting thread!" << endl;
			PopNotifier.wait(mlock);
		}
		int ElementRemoved = FIFO.front();
		cout << "Element " << ElementRemoved << " removed. Queue size : " << FIFO.size() << endl;
		FIFO.pop();
		PushNotifier.notify_one();

		return ElementRemoved;
	}


};
