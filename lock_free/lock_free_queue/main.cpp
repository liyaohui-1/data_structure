#include <iostream>
#include <thread>

#include "lock_free_queue.h"

void producer(LockFreeQueue<int>& queue)
{
    for(int i = 0; i < 100; ++i)
    {
        queue.enqueue(i);
    }
}

void consumer(LockFreeQueue<int>& queue)
{
    for(int j = 0; j < 100; ++j)
    {
        int value;
        if(queue.dequeue(value))
        {
            std::cout << "value: " << value << std::endl;
        }
    }
}

int main()
{
    LockFreeQueue<int> queue(100);
    std::thread t1(producer,std::ref(queue));
    std::thread t2(consumer,std::ref(queue));

    t1.join();
    t2.join();

    return 0;
}