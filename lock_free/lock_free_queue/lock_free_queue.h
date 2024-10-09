#ifndef LOCK_FREE_QUEUE_
#define LOCK_FREE_QUEUE_

#include <atomic>

template<typename T>
class LockFreeQueue
{
    public:
        LockFreeQueue(const size_t& capacity) 
        : buffer(new T[capacity]), head_(0), tail_(0), capacity_(capacity) {} 

        ~LockFreeQueue()
        {
            delete [] buffer;
        }

        bool enqueue(const T& value)
        {
            size_t newTail = (tail_.load() + 1) % capacity_;  
            if (newTail == head_.load()) 
            {  
                // 队列满  
                return false;  
            }  
            while (true) 
            {  
                size_t currTail = tail_.load();  
                if (currTail == newTail) 
                {  
                    // 队列满，或tail被其他线程更新  
                    continue;  
                }  
                if (tail_.compare_exchange_weak(currTail, newTail)) 
                {  
                    buffer[currTail] = value;  
                    return true;  
                }  
                // CAS失败，重试  
            }  
        }

        bool dequeue(T& value)
        {
            if (head_.load() == tail_.load()) 
            {  
                // 队列空  
                return false;  
            }  
            while (true) 
            {  
                size_t currHead = head_.load();  
                size_t newHead = (currHead + 1) % capacity_;  
                if (currHead == tail_.load()) 
                {  
                    // 队列空，或head被其他线程更新  
                    continue;  
                }  
                if (head_.compare_exchange_weak(currHead, newHead)) 
                {  
                    value = buffer[currHead];  
                    return true;  
                }  
                // CAS失败，重试  
            }
        }

    private:
        T* buffer;
        std::atomic<size_t> head_,tail_;
        const size_t capacity_;
};

#endif