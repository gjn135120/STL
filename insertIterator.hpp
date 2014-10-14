#ifndef ITERATOR_H
#define ITERATOR_H
#include <iterator>

//BackInsertIterator
template <typename Container>
class InsertIterator
{
public:
	typedef typename Container::value_type value_type;
	typedef typename Container::iterator   iterator;

	explicit InsertIterator(Container &cont, iterator iter)
		:_cont(cont), _iter(iter)
	{ }

	InsertIterator<Container> &operator= (const value_type &val)
	{
		_cont.insert(_iter, val);
		++ _iter;
		return *this;
	}

	InsertIterator<Container> &operator*()
	{ return *this; }

	InsertIterator<Container> &operator++()
	{ return *this; }

	InsertIterator<Container> &operator++(int)
	{ return *this; }
private:
	Container &_cont;
	iterator _iter;
};

template <typename Container>
InsertIterator<Container> inserter(Container &c)
{ return InsertIterator<Container>(c); }



#endif
