/*! \file Queue.h
	\brief Queue interface class.

	This header file implements a class interface for a queue using std::queue.
*/

#pragma once
#include <iostream>
#include <queue>
#include <mutex>
#include <cassert> 
#include <condition_variable>

using namespace std;

template <typename T>

class Queue
{
private:
	int SizeLimit = 0; /**< Maximum size of the queue (user specified).*/  
	std::queue<int> FIFO; /**< Queue using std::queue.*/ 
	std::mutex MutexLocker; /**< Mutex for resource mutual exclusion (std::mutex) */
	std::condition_variable PushNotifier; /**<  Signal to lock while waiting for Pop() (std::condition_variable). */
	std::condition_variable PopNotifier; /**< Signal to lock while waiting for Push() (std::condition_variable). */

public:
	/*! @brief Constructor of the queue class.
	*
	* Constructor of the queue class with an user specified size.
	*
	* @param[in] size Integer value with the size of the queue.
	* 
	* @pre size must be > 0.
	*/
	Queue(int size) {
		assert(size > 0); // Size must be > 0
		SizeLimit = size;
		PushNotifier.notify_one(); // at start, queue is empty
	}

	/*! @brief Count the number of elements in the queue.
	*
	* Function to return the number of elements in the queue.
	*
	* @param[out] Count Number of elements in the queue.
	*
	*/
	int Count(void)
	{
		return FIFO.size();
	};

	/*! @brief Maximum size of the queue.
	*
	* Function to return the maximum size of the queue that was user specified.
	*
	* @param[out] Size Maximum number of elements of the queue.
	*
	*/
	int Size(void)
	{
		return SizeLimit;
	};

	/*! @brief Push an element to the queue.
	*
	* If the queue is full: wait for the reading thread.
	* If the queue is not full: add element to the queue.
	* 
	* @param[in] Element Element to be added to the queue.
	*
	*/
	void Push(T element)
	{
		std::unique_lock<std::mutex> mlock(MutexLocker); // Mutual exclusive

		while (FIFO.size() == SizeLimit)  // If the queue is full, no element should be added
		{
			// 
			cout << "Queue is full. Waiting for the reading thread!" << endl;
			PushNotifier.wait(mlock); // Push condition variable
		}
		// Queue is not full, add a new element
		FIFO.push(element);  

		cout << "Element " << element << " added to the queue. New size: " << FIFO.size() << "." << endl; //terminal output

		// Remove the Mutex
		mlock.unlock();

		PopNotifier.notify_one(); // notify POP waiting thread

	};


	/*! @brief Pop an element from the queue.
	*
	* If the queue is empty: wait for the writing thread.
	* If the queue is not empty: remove the first element
	*
	* @param[out] Element Element removed from the queue.
	*
	*/
	T Pop(void) {

		std::unique_lock<std::mutex> mlock(MutexLocker); // Mutual exclusive


		while (FIFO.empty()) // If the queue is empty, no reading operation can be performed.
		{
			cout << "Queue is empty. Waiting for the writting thread!" << endl;
			PopNotifier.wait(mlock); // Pop condition variable
		}

		int ElementRemoved = FIFO.front(); // Acquire element that is going to be removed for terminal output
		
		FIFO.pop(); //Pop the queue

		cout << "Element " << ElementRemoved << " removed. Queue size : " << FIFO.size() << endl; //terminal output

		// Remove the Mutex
		mlock.unlock();

		PushNotifier.notify_one();  // notify Push waiting thread

		return ElementRemoved; // return the element removed
	}


};
