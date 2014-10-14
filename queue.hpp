#ifndef QUEUE_H
#define QUEUE_H
#include "Exception.h"
#include <deque>

class EmptyQueueException : public Exception
{
public:
	EmptyQueueException()
		:Exception("read empty queue")
	{ }
};

template <typename T, typename Container = std::deque<T> >
class Queue
{
public:

	typedef T 								value_type;
	typedef T&								reference;
	typedef const T&						const_reference;
	typedef Container 						container_type;
	typedef Container&						container_reference;
	typedef const Container&				const_container_reference;
	typedef EmptyQueueException 			exception_type;
	typedef typename Container::size_type 	size_type;


	explicit Queue(const_container_reference cont = container_type())
		:_cont(cont)
	{ }

	template <typename T2, typename Container2>
	Queue<T, Container>(const Queue<T2, Container2> &s);

	template <typename T2, typename Container2>
	Queue<T, Container> &operator=(const Queue<T2, Container2> &s);

	void push(const value_type &val) { _cont.push_back(val); }

	void pop()
	{
		if(_cont.empty())
			throw exception_type();
		_cont.pop_front();
	}

	reference front()
	{
		if(_cont.empty())
			throw exception_type();
		return _cont.front();
	}

	const_reference front() const
	{
		if(_cont.empty())
			throw exception_type();
		return _cont.front();
	}

	reference back()
	{
		if(_cont.empty())
			throw exception_type();
		return _cont.back();
	}

	const_reference back() const
	{
		if(_cont.empty())
			throw exception_type();
		return _cont.back();
	}

	bool empty() const { return _cont.empty(); }
	size_type size() const { return _cont.size(); }

	const_container_reference get_container() const
	{ return _cont; }

	friend bool operator== (const Queue &a, const Queue &b)
	{ return a._cont == b._cont; }

	friend bool operator!= (const Queue &a, const Queue &b)
	{ return a._cont != b._cont; }

	friend bool operator>= (const Queue &a, const Queue &b)
	{ return a._cont >= b._cont; }

	friend bool operator<= (const Queue &a, const Queue &b)
	{ return a._cont <= b._cont; }

	friend bool operator> (const Queue &a, const Queue &b)
	{ return a._cont > b._cont; }

	friend bool operator< (const Queue &a, const Queue &b)
	{ return a._cont < b._cont; }
private:
	container_type _cont;
};

template <typename T, typename Container>
template <typename T2, typename Container2>
Queue<T, Container>::Queue(const Queue<T2, Container2> &s)
	:_cont(s.get_container().begin(), s.get_container().end())
{ }

template <typename T, typename Container>
template <typename T2, typename Container2>
Queue<T, Container> &Queue<T, Container>::operator= (const Queue<T2, Container2> &s)
{
	if((void *)this != (void *)&s)
	{
		_cont.assign(s.get_container().begin(), s.get_container().end());
	}
	return *this;
}
#endif
