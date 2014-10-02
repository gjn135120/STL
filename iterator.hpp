#ifndef ITERATOR_H
#define ITERATOR_H 
#include <iterator>

template <typename Container>
class Iterator : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
    explicit Iterator(Container &c)
        :_container(c)
    { }

    Iterator<Container> &operator= (const typename Container::value_type &value)
    {
        _container.insert(value);
        return *this;
    }

    Iterator<Container> operator* ()
    { return *this; }

    Iterator<Container> &operator++ ()
    { return *this; }

    Iterator<Container> &operator++ (int)
    { return *this; }

protected:
    Container &_container;
};

template <typename Container>
Iterator<Container> MyInsert(Container &c)
{
    return Iterator<Container>(c);
}

#endif  /*ITERATOR_H*/
