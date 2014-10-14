#ifndef STACK_H
#define STACK_H
#include "Exception.h"
#include <deque>

class EmptyStackException : public Exception
{
public:
	EmptyStackException()
		:Exception("read empty stack")
	{ }
};


template <typename T, typename Container = std::deque<T> >
class Stack
{
public:
	typedef T 								value_type;
	typedef T& 								reference;
	typedef const T& 						const_reference;
	typedef Container 						container_type;
	typedef EmptyStackException 			exception_type;
	typedef typename Container::size_type 	size_type;
	typedef Container& 						container_reference;
	typedef const Container&				const_container_reference;

	explicit Stack(const container_type &cont = container_type())
		:_cont(cont)
	{ }

	template <typename T2, typename Container2>
	Stack<T, Container>(const Stack<T2, Container2> &s);

	template <typename T2, typename Container2>
    Stack<T, Container> &operator=(const Stack<T2, Container2> &s);

	void push(const value_type &value) { _cont.push_back(value); }

	void pop()
	{
		if(_cont.empty())
			throw exception_type();
		_cont.pop_back();
	}

	reference top()
	{
		if(_cont.empty())
			throw exception_type();
		return _cont.back();
	}

	const_reference top() const
	{
		if(_cont.empty())
			throw exception_type();
		return _cont.back();
	}

	bool empty() const { return _cont.empty(); }
	size_type size() const { return _cont.size(); }

	const_container_reference get_container() const
	{ return _cont; }


	friend bool operator== (const Stack &a, const Stack &b)
	{ return a._cont = b._cont; }

	friend bool operator!= (const Stack &a, const Stack &b)
	{ return !(a == b); }

	friend bool operator< (const Stack &a, const Stack &b)
	{ return a._cont < b._cont; }

	friend bool operator<= (const Stack &a, const Stack &b)
	{ return a._cont <= b._cont; }

	friend bool operator> (const Stack &a, const Stack &b)
	{ return a._cont > b._cont; }

	friend bool operator>= (const Stack &a, const Stack &b)
	{ return a._cont >= b._cont; }

private:
	Container _cont;
};

template <typename T, typename Container>
template <typename T2, typename Container2>
Stack<T, Container>::Stack(const Stack<T2, Container2> &s)
	:_cont(s.get_container().begin(), s.get_container().end())
{ }

template <typename T, typename Container>
template <typename T2, typename Container2>
Stack<T, Container> &Stack<T, Container>::operator=(const Stack<T2, Container2> &s)
{
	if((void *)this != (void *)&s)
	{
		_cont.assign(s.get_container.begin(), s.get_container.end());
	}

	return *this;
}
#endif
