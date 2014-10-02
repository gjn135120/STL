#ifndef VECTOR_H
#define VECTOR_H 

#include <memory>
#include <algorithm>
#include <stddef.h>
#include <limits>
template <typename T, typename Alloc>
class Vector;

template <typename T, typename Alloc>
bool operator== (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b);
template <typename T, typename Alloc>
bool operator!= (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b);
template <typename T, typename Alloc>
bool operator> (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b);
template <typename T, typename Alloc>
bool operator>= (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b);
template <typename T, typename Alloc>
bool operator< (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b);
template <typename T, typename Alloc>
bool operator<= (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b);


template <typename T, typename Alloc = std::allocator<T> >
class Vector
{
    friend bool operator==<T, Alloc> (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b);
    friend bool operator!=<T, Alloc> (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b);
    friend bool operator> <T, Alloc> (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b);
    friend bool operator>=<T, Alloc> (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b);
    friend bool operator< <T, Alloc> (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b);
    friend bool operator<=<T, Alloc> (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b);
   
    class reverse_iterator;
    class const_reverse_iterator;
public:
    typedef T value_type;
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef reverse_iterator reverse_iterator;
    typedef const_reverse_iterator const_reverse_iterator;
    typedef T &reference;
    typedef const T &const_reference;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef Alloc allocator_type;
private:
    //逆序迭代器
    class reverse_iterator          
    {
    public:
        reverse_iterator(iterator it = NULL) :_current(it) { }
        iterator base() const {return _current; }
        reverse_iterator &operator++ ()
        {
            -- _current;
            return *this;
        }
        reverse_iterator operator++ (int)
        {
            reverse_iterator tmp(*this);
            -- _current;
            return tmp;
        }
        reverse_iterator &operator-- ()
        {
            ++ _current;
            return *this;
        }
        reverse_iterator operator-- (int)
        {
            reverse_iterator tmp(*this);
            ++ _current;
            return tmp;
        }

        reference operator*()
        {
            return *(_current - 1);
        }

        const_reference operator*() const
        {
            return *(_current - 1);
        }
    
        pointer operator-> ()
        { return _current - 1; }

        const_pointer operator-> () const
        { return _current - 1; }

        friend bool operator== (reverse_iterator i,
                                reverse_iterator j)
        {
            return i._current == j._current;
        }

        friend bool operator!= (reverse_iterator i,
                                reverse_iterator j)
        {
            return i._current != j._current;
        }


        friend difference_type operator-(reverse_iterator i,
                                         reverse_iterator j)
        {
            return i._current - j._current;
        }
    private:
            iterator _current;
    };
    //逆序迭代器


    //const逆序迭代器
    class const_reverse_iterator          
    {
    public:
        const_reverse_iterator(const_iterator it = NULL) :_current(it) { }
        const_reverse_iterator(reverse_iterator it) :_current(it.base()) { }
        const_iterator base() const {return _current; }
        const_reverse_iterator &operator++ ()
        {
            -- _current;
            return *this;
        }
        const_reverse_iterator operator++ (int)
        {
            reverse_iterator tmp(*this);
            -- _current;
            return tmp;
        }
        const_reverse_iterator &operator-- ()
        {
            ++ _current;
            return *this;
        }
        const_reverse_iterator operator-- (int)
        {
            reverse_iterator tmp(*this);
            ++ _current;
            return tmp;
        }

        const_reference operator*() const
        {
            return *(_current - 1);
        }
    

        const_pointer operator-> () const
        { return _current - 1; }

        friend bool operator== (const_reverse_iterator i,
                                const_reverse_iterator j)
        {
            return i._current == j._current;
        }

        friend bool operator!= (const_reverse_iterator i,
                                const_reverse_iterator j)
        {
            return i._current != j._current;
        }


        friend difference_type operator-(const_reverse_iterator i,
                                         const_reverse_iterator j)
        {
            return i._current - j._current;
        }
    private:
            const_iterator _current;
    };
    //const逆序迭代器



public:
    //三种构造Vector的方法
    Vector() { create(); }

    explicit Vector(size_type n, const value_type &val = value_type())
    { create(n, val); }

    template <typename In>
    Vector(In i, In j)
    { create(i, j); }
    
    //复制v对象
    Vector(const Vector &v)
    { create(v.begin(), v.end()); }
    //赋值函数
    Vector &operator= (const Vector &v);
    //析构函数
    ~Vector() { uncreate(); }
    //assign操作的几种形式
    template <typename In>
    void assign(In i, In j)
    {
        uncreate();
        create(i, j);
    }

    void assign(size_type n, const T &val)
    {
        uncreate();
        create(n, val);
    }
    //下标操作
    reference operator[] (size_type index) { return _data[index]; }
    const_reference operator[] (size_type index) const { return _data[index]; }
    //at操作
    reference at(size_type index) { return _data[index]; }
    const_reference at(size_type index) const { return _data[index]; }
    //front、back操作
    reference front() { return *begin(); }
    reference back() { return *rbegin(); }
    const_reference front() const { return *begin(); }
    const_reference back() const { return *rbegin(); }
    
    //pop_back操作
    void pop_back()
    { _alloc.destroy(-- _avail); }
    //insert函数的几种操作
    iterator insert (iterator pos, const value_type &val);

    void insert(iterator pos, size_type n, const value_type &val);

    template <typename InputIterator>
    void insert(iterator pos, InputIterator first, InputIterator last);

    //erase的几种操作
    iterator erase(iterator pos);

    iterator erase(iterator first, iterator last);


    //resize和reserve的操作
    void resize(size_type n, value_type val = value_type());
    void reserve(size_type n);
    
    //判断是否为空、查看元素个数、查看空间大小
    bool empty() const { return _data == _avail; }
    size_type size() const { return _avail - _data; }

    size_type capacity() const { return _limit - _data; }

    size_type max_size() const
    { return std::numeric_limits<size_type>::max() / sizeof(T); }
    //begin、end迭代器操作
    iterator begin() { return _data; }
    const_iterator begin() const { return _data; }

    iterator end() { return _avail; }
    const_iterator end() const { return _avail; }

    //rbegin、rend迭代器操作
    reverse_iterator rbegin() { return reverse_iterator(_avail); }
    reverse_iterator rend() { return reverse_iterator(_data); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(_avail); }
    const_reverse_iterator rend() const { return const_reverse_iterator(_data); }
    //push_back操作
    void push_back(const T &t)
    {
        if(_avail == _limit)
            grow();
        unCheckdAppend(t);
    }

    //与other对象进行交换
    void swap(Vector &other)
    {
        std::swap(_data, other._data);
        std::swap(_avail, other._avail);
        std::swap(_limit, other._limit);
    }
    //  
    allocator_type get_allocator() const
    { return _alloc; }


private:
    iterator _data;             //数组首元素
    iterator _avail;            //数组最后一个元素的下一个位置
    iterator _limit;            //最后一块内存的下一块位置

    std::allocator<T> _alloc;   //内存分配器


    void create();
    void create(size_type, const value_type &);

    template <typename In>
    void create(In i, In j);


    void uncreate();

    void grow();            //内存增长
    void unCheckdAppend(const T &val);

    void growTon(size_type n);
};
//复制构造函数
template <typename T, typename Alloc>
Vector<T, Alloc> &Vector<T, Alloc>::operator= (const Vector &v)
{
    if(this != &v)
    {
        uncreate();
        create(v.begin(), v.end());
    }

    return *this;
}


//三个构造函数
template <typename T, typename Alloc>
void Vector<T,Alloc>::create()
{
    _data = _avail = _limit = NULL;
}


template <typename T, typename Alloc>
void Vector<T, Alloc>::create(size_type n, const T &val)
{
    //先分配内存
    _data = _alloc.allocate(n);
    //初始化赋值
    std::uninitialized_fill(_data, _data + n, val);
    _avail = _limit = _data + n;
}

    
template <typename T, typename Alloc>
template <typename In>
void Vector<T, Alloc>::create(In i, In j)
{
    _data = _alloc.allocate(j - i);

    _avail = _limit = std::uninitialized_copy(i, j, _data);

}

    
//析构函数
template <typename T, typename Alloc>
void Vector<T, Alloc>::uncreate()
{
    //先执行析构函数
    if(_data)
    {
        iterator it(_avail);
        while(it != _data)
        {
            _alloc.destroy(-- it);
        }
    }

    //释放内存
    _alloc.deallocate(_data, _limit - _data);
    _data = _avail = _limit = NULL;
}



//grow函数
template <typename T, typename Alloc>
void Vector<T, Alloc>::grow()
{
    //确定size
    size_type new_size = std::max(2 * (_limit - _data), difference_type(1));
    
    growTon(new_size);
}


//unCheckdAppend函数
template <typename T, typename Alloc>
void Vector<T, Alloc>::unCheckdAppend(const T &val)
{
    _alloc.construct(_avail ++, val);
}


//growTon函数
template <typename T, typename Alloc>
void Vector<T, Alloc>::growTon(size_type n)
{
    iterator new_data = _alloc.allocate(n);
    iterator new_avail = std::uninitialized_copy(_data, _avail, new_data);

    uncreate();

    _data = new_data;
    _avail = new_avail;
    _limit = _data + n;
}


//insert函数

template <typename T, typename Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::insert(iterator pos, const value_type &val)
{
    difference_type i = pos - _data;
    insert(pos, 1, val);
    return pos + i;
}


template <typename T, typename Alloc>
void Vector<T, Alloc>::insert(iterator pos, size_type n, const value_type &val)
{
    difference_type i = pos - _data;
    while(static_cast<size_type>(_limit - _avail) < n)
        grow();
    pos = _data + i;

    size_type left = _avail - pos;

    if(n < left)
    {
        size_type len = _avail - pos;
        size_type copyLen = len - n;
        std::uninitialized_copy(pos + copyLen, _avail, _avail);
        std::copy_backward(pos, pos + copyLen, _avail);

        std::fill_n(pos, n, val);
    }
    else if(n > left)
    {
        std::uninitialized_copy(pos, _avail, pos + n);

        std::fill_n(pos, _avail - pos, val);
        std::uninitialized_fill(_avail, pos + n, val);
    }
    else
    {
        std::uninitialized_copy(pos, _avail, _avail);
        std::fill_n(pos, n, val);
    }

    _avail = _avail + n;
}

template <typename T, typename Alloc>
template <typename InputIterator>
void Vector<T, Alloc>::insert(iterator pos, InputIterator first, InputIterator last)
{
    difference_type i = pos - _data;
    size_type n = last - first;
    while(static_cast<size_type>(_limit - _avail) < n)
        grow();
    pos = _data + i;

    size_type left = _avail - pos;
    if(n < left)
    {
        size_type len = _avail - pos;
        size_type copyLen = len - n;
        std::uninitialized_copy(pos + copyLen, _avail, _avail);
        std::copy_backward(pos, pos + copyLen, _avail);

        std::copy(first, last, pos); 
    }
    else if(n > left)
    {
        std::uninitialized_copy(pos, _avail, pos + n);
        
        std::copy(first, first + left, pos);
        std::uninitialized_copy(first + left, last, _avail);
    }
    else
    {
        std::uninitialized_copy(pos, _avail, _avail);

        std::copy(first, last, pos);
    }

    _avail = _avail + n;
}


//erase函数

template <typename T, typename Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase(iterator pos)
{
    std::copy(pos + 1, _avail, pos);
    _alloc.destroy(-- _avail);
    return pos;
}

template <typename T, typename Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase(iterator first, iterator last)
{
    difference_type left = _avail - last;
    std::copy(last, _avail, first);

    iterator it(first + left);
    while(_avail != it)
        _alloc.destroy(-- _avail);
    return first;
}


//resize函数
template <typename T, typename Alloc>
void Vector<T, Alloc>::resize(size_type n, value_type val)
{
    size_type cur_size = size();
    if(n < cur_size)
    {
        size_type diff = cur_size - n;
        while(diff --)
            _alloc.destroy(-- _avail);
    }
    else if(n > cur_size)
    {
        size_type diff = n - cur_size;
        size_type left = static_cast<size_type>(_limit - _avail);
        if(left < diff)
            growTon(n);

        while(size() < n)
            unCheckdAppend(val);
    }
}

template <typename T, typename Alloc>
void Vector<T, Alloc>::reserve(size_type n)
{
    size_type cur_cap = capacity();
    if(n > cur_cap)
        growTon(n);
}


//运算符重载
template <typename T, typename Alloc>
bool operator== (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b)
{
    return a.size() == b.size() && 
           std::equal(a.begin(), a.end(), b.begin() );
}


template <typename T, typename Alloc>
bool operator!= (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b)
{
    return !(a == b);
}


template <typename T, typename Alloc>
bool operator< (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b)
{
    typedef typename Vector<T, Alloc>::size_type size_type;
    size_type size1 = a.size();
    size_type size2 = b.size();
    size_type min =(size1 < size2) ? size1 : size2;
    size_type i = 0;
    for(; i != min; ++ i)
    {
        if(a[i] < b[i])
            return true;
        else if(a[i] > b[i])
            return false;
    }
    if(i != size2)
        return true;
    return false;
}


template <typename T, typename Alloc>
bool operator<= (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b)
{
    return !(a > b);
}


template <typename T, typename Alloc>
bool operator> (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b)
{
    return b < a;
}


template <typename T, typename Alloc>
bool operator>= (const Vector<T, Alloc> &a, const Vector<T, Alloc> &b)
{
    return !(a < b);
}


#endif  /*VECTOR_H*/
