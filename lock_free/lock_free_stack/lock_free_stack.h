#ifndef LOCK_FREE_STACK
#define LOCK_FREE_STACK

#include <atomic>
#include <memory>

template<typename T>
class LockFreeStack
{
    public:
        LockFreeStack() : head_(nullptr)
        {}
        ~LockFreeStack();

        void push(const T& value);
        bool pop(T& value);

    private:
        struct Node
        {
            T data_;
            Node* next_;

            Node(const T& data) : data_(data),next_(nullptr)
            {}
        };

        std::atomic<Node*> head_;
};

template<typename T>
void LockFreeStack<T>::push(const T& value)
{
    Node* new_data = new Node(value);
    new_data->next_=head_.load(std::memory_order_relaxed);
    while(!head_.compare_exchange_weak(new_data->next_, new_data, std::memory_order_release, std::memory_order_relaxed));
    {
        // CAS失败，继续尝试
    }
}

template<typename T>
bool LockFreeStack<T>::pop(T& value)
{
    Node* old_head = head_.load(std::memory_order_relaxed);
    while(old_head && !head_.compare_exchange_weak(old_head, old_head->next_,std::memory_order_acquire, std::memory_order_relaxed))
    {
        // CAS失败，继续尝试
    }
    
    if(old_head)
    {
        value = old_head->data_;
        delete old_head;
        return true;
    }
    return false;
}

template<typename T>
LockFreeStack<T>::~LockFreeStack()
{
    Node* current = head_.load();
    while(current)
    {
        Node* to_delete = current;
        current=current->next_;
        delete to_delete;
    }
}

#endif