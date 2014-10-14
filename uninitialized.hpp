#ifndef UNINIT_H
#define UNINIT_H
#include <iterator>

template <typename ForwIter, typename T>
void uninitialized_fill(ForwIter first, ForwIter last, const T &value)
{
	typedef typename std::iterator_traits<ForwIter>::value_type VT;
	ForwIter save(first);
	try
	{
		for( ; first != end; ++ first)
			new(static_cast<void *>(&*first))VT(value);
	}

	catch(...)
	{
		for( ; save != first; ++ save)
			save->~VT();
		throw();
	}
}

template <typename ForwIter, typename Size, typename T>
void uninitialized_fill_n(ForwIter first, Size n, const T &value)
{
	typedef typename std::iterator_traits<ForwIter>::value_type VT;
	ForwIter save(first);
	try
	{
		for( ; -- n; ++ first)
			new(static_cast<void *>(&*first))VT(value);
	}
	catch(...)
	{
		for( ; save != first; ++ save)
			save->~VT();
		throw();
	}

}

template <typename InputIter, typename ForwIter>
void uninitialized_copy(InputIter first, InputIter last; ForwIter dest)
{
	typedef typename std::iterator_traits<ForwIter>::value_type VT;
	ForwIter save(dest);
	try
	{
		for( ; first != last; ++ first, ++ dest)
			new(static_cast<void *>(&*dest))VT(*first);
	}
	catch(...)
	{
		for( ; save != dest; ++ save)
			save->~VT();
		throw();
	}

}

#endif
