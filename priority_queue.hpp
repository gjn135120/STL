#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <vector>
#include <algorithm>
#include <functional>

template <typename T,
		  typename Container = std::vector<T>,
		  typename Compare = std::less<typename Container::value_type> >
class PriorityQueue
{
public:
	typedef typename Container::value_type 	value_type;
	typedef typename Container::size_type 	size_type;
	typedef Container						container_type;
	typedef value_type& 					reference;
	typedef const value_type&				const_reference;

	PriorityQueue(const Compare &comp = Compare(),
	              const Container &cont = Container());



	template <typename InputIter>
	PriorityQueue(InputIter first, InputIter last,
	              const Compare &comp = Compare(),
	              const Container &cont = Container());

	void push(const value_type &val)
	{
		_cont.push_back(val);
		std::push_heap(_cont.begin(), _cont.end(), _comp);
	}

	void pop()
	{
		std::pop_heap(_cont.begin(), _cont.end(), _comp);
		_cont.pop_back();
	}

	bool empty() const { return _cont.empty(); }
	size_type size() const { return _cont.size(); }

	const_reference top() const { return _cont.front(); }

private:
	Compare _comp;
	Container _cont;

};

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::PriorityQueue(const Compare &comp,
                                                    const Container &cont)
		:_comp(comp), _cont(cont)
	{
		std::make_heap(_cont.begin(), _cont.end(), _comp);
	}


template <typename T, typename Container, typename Compare>
template <typename InputIter>
PriorityQueue<T, Container, Compare>::PriorityQueue(InputIter first, InputIter last,
                                                    const Compare &comp,
                                                    const Container &cont)
	:_comp(comp), _cont(cont)
{
	_cont.insert(_cont.end(), first, last);
	std::make_heap(_cont.begin(), _cont.end(), _comp);
}

#endif
