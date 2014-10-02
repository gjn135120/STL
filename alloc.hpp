#ifndef ALLOCATOR_H
#define ALLOCATOR_H 

#include <stddef.h>
#include <limits>

template <typename T>
class Allocator
{
public:
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
    typedef T*          pointer;
    typedef const T*    const_pointer;
    typedef T&          reference;
    typedef const T&    const_reference;
    typedef T           value_type;

    template <typename V>
    struct rebind
    {
        typedef Allocator<V> other;
    };

    pointer address(reference value) const { return &value; }
    const_pointer address(const_reference value) const { return &value; }

    Allocator() throw() { }
    Allocator(const Allocator &v) throw() { }
    template <typename V>
    Allocator(const Allocator<V> &v) { } 

    ~Allocator() throw() { }

    size_type max_size() const throw()
    { return std::numeric_limits<size_type>::max() / sizeof(T); }

    pointer allocate(size_type num)
    { return (pointer)(::operator new(num * sizeof(T))); }

    void construct(pointer p, const T &value)
    { new((void*)p) T(value); }

    void destroy(pointer p)
    { p->~T(); }


    void deallocate(pointer p, size_type num)
    { ::operator delete((void*)p); }

};


template <typename T, typename V>
bool operator==(const Allocator<T> &a, const Allocator<V> &b)
{ return true; }


template <typename T, typename V>
bool operator!=(const Allocator<T> &a, const Allocator<V> &b)
{ return false; }
#endif  /*ALLOCATOR_H*/
