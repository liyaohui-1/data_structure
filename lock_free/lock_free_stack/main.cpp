#include <iostream>
#include <thread>

#include "lock_free_stack.h"

void producer(LockFreeStack<int>& stack)
{
    for(int i = 0; i < 100; ++i)
    {
        stack.push(i);
    }
}

void consumer(LockFreeStack<int>& stack)
{
    for(int j = 0; j < 100; ++j)
    {
        int value;
        if(stack.pop(value))
        {
            std::cout << "value: " << value << std::endl;
        }
    }
}

int main()
{
    LockFreeStack<int> stack;
    std::thread t1(producer,std::ref(stack));
    std::thread t2(consumer,std::ref(stack));

    t1.join();
    t2.join();

    return 0;
}