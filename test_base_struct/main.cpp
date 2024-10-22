#include "bounded_queue.h"
#include <iostream>

using namespace idrive::iros::base;

int main(int argc, char* argv[])
{
    std::cout << "---------------->start" << std::endl;
    BoundedQueue<int> queue;
    queue.Init(5, new TimeoutBlockWaitStrategy(1000));
    bool b = queue.WaitEnqueue(1);
    std::cout << std::boolalpha << b << std::endl;
    std::cout << "---------------->end1" << std::endl;

    b = queue.WaitEnqueue(2);
    std::cout << b << std::endl;
    std::cout << "---------------->end2" << std::endl;

    b = queue.WaitEnqueue(3);
    std::cout << b << std::endl;
    std::cout << "---------------->end3" << std::endl;

    b = queue.WaitEnqueue(4);
    std::cout << b << std::endl;
    std::cout << "---------------->end4" << std::endl;

    std::cout << "---------------->end5" << std::endl;
    return 0;
}