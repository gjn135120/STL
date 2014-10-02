#ifndef NEW_H
#define NEW_H 
#include <iostream>
#include <stdexcept>
#include <memory>

template <typename T>
class New
{
public:
    void *operator new(std::size_t );
    void operator delete(void *, std::size_t );
    virtual ~New() { }
protected:
    T *_next;
private:
    static void addToFreeList(T *);     //将内存块加入链表
    static std::allocator<T> _alloc;     //内存分配器
    static T *_freeList;                //空闲内存的链表
    static const std::size_t _chunk;    //一次分配的块数
};

template <typename T> std::allocator<T> New<T>::_alloc;
template <typename T> T *New<T>::_freeList = NULL;
template <typename T> const std::size_t New<T>::_chunk = 24;


template <typename T>
void *New<T>::operator new(std::size_t sz)
{
    if(sz != sizeof(T))
        throw std::runtime_error("wrong size");
    std::cout << "operator new" << std::endl;

    if(_freeList == NULL)
    {
        T *newList = _alloc.allocate(_chunk);
        for(size_t i = 0; i != _chunk; ++ i)
            addToFreeList(&newList[i]);
    }

    T *p = _freeList;
    _freeList = _freeList->New<T>::_next;
    return p;
}

template <typename T>
void New<T>::operator delete(void *p, size_t sz)
{
    std::cout << "operator delete" << std::endl;
    if(p != NULL)
        addToFreeList(static_cast<T *>(p));
}


template <typename T>
void New<T>::addToFreeList(T *p)
{
    p->New<T>::_next = _freeList;
    _freeList = p;
}
#endif  /*NEW_H*/
