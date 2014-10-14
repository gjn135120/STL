#include "Exception.h"
#include <cxxabi.h>
#include <execinfo.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

Exception::Exception(const char *what)
	:_message(what)
{
	fillStackTrace();
}

Exception::Exception(const std::string &what)
	:_message(what)
{
	fillStackTrace();
}

Exception::~Exception() throw()
{

}

const char *Exception::what() const throw()
{
	return _message.c_str();
}

const char *Exception::stackTrace() const throw()
{
	return _stack.c_str();
}

void Exception::fillStackTrace()
{
	const int len = 200;
	void *buffer[len];
	int nptrs = ::backtrace(buffer, len);

	char **strings = ::backtrace_symbols(buffer, nptrs);

	if(strings)
	{
		for(int i = 0; i != nptrs; ++ i)
		{
			_stack.append(demangle(strings[i]));
			_stack.push_back('\n');
		}
		free(strings);
	}
}


string Exception::demangle(const char *symbol)
{
	size_t size;
	int status;
	char tmp[128];
	char *demangled;

	if(1 == sscanf(symbol, "%*[^(]%*[^_]%127[^)+]", tmp))
	{
		if(NULL != (demangled = abi::__cxa_demangle(tmp, NULL, &size, &status)))
		{
			string result(demangled);
			free(demangled);
			return result;
		}
	}

	if(1 == sscanf(symbol, "%127s", tmp))
	{
		return tmp;
	}

	return symbol;
}













