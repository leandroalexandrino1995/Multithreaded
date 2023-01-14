#include "../inc/Queue.h"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>


class TestQueue : public Queue<int>{};


static void ReadThreadTest(Queue<int>*Fifo){
	    std::this_thread::sleep_for(std::chrono::milliseconds(500));
	    Fifo->Pop();
	    std::this_thread::sleep_for(std::chrono::milliseconds(500));
	    Fifo->Pop();
	    std::this_thread::sleep_for(std::chrono::milliseconds(500));
	    Fifo->Pop();
	    std::this_thread::sleep_for(std::chrono::milliseconds(500));
	    Fifo->Pop();
}

static void WriteThreadTest(Queue<int>*Fifo){
	    Fifo->Push(10);
	    Fifo->Push(20);
	    Fifo->Push(30);
	    Fifo->Push(40);
}


/* Test if count starts at 0. */
TEST(TestQueue,QueueInitCount)
{
	Queue<int> *QueueToTest = new Queue<int>(2);
	EXPECT_EQ(QueueToTest->Count(),0);
};


/* Test if count is incremented in new Push() */
TEST(TestQueue,PushCounter)
{
	Queue<int> *QueueToTest = new Queue<int>(2);
	QueueToTest->Push(1);
	EXPECT_EQ(QueueToTest->Count(),1);
};


/* Test if count is decremented in new Pop() */
TEST(TestQueue,PopCounter)
{
	Queue<int> *QueueToTest = new Queue<int>(2);
	QueueToTest->Push(1);
	QueueToTest->Pop();
	EXPECT_EQ(QueueToTest->Count(),0);
};


/* Test if adding 4 elements and removing ends with 0 total elements  */
TEST(TestQueue, ThreadPush)
{
    Queue<int> *QueueToTest = new Queue<int>(2);
    thread t1(WriteThreadTest, QueueToTest);
    thread t2(ReadThreadTest, QueueToTest);
    t1.join();
    t2.join();
    
    
    EXPECT_EQ(QueueToTest->Count(),0);

}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


