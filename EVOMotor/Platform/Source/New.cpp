#include <cstdlib>
#include "Platform/New.h"
#include "Platform/Leak.h"
#include "Platform/debug.h"



void* operator new(const unsigned int size)
{
	//writeLog("NEW %i\n", size);

	void* object = malloc(size);
	//TODO check errors

	return object;
}

void* operator new[](const unsigned int size)
{
	return ::operator new(size);
}

void* operator new(const unsigned int size, const char* file, const unsigned int line)
{
	void* object = ::operator new(size);
	Leak::addPointer(object, file, line);

	return object;
}

void* operator new[](const unsigned int size, const char* file, const unsigned int line)
{
	return ::operator new(size, file, line);
}

void operator delete(void* object)
{
	//writeLog("DELETE\n");

	if(object != NULL)
		Leak::removePointer(object);

	free(object);
}

void operator delete[](void* object)
{
	::operator delete(object);
}

void operator delete(void* object, const char*, const unsigned int)
{
	//file;
	//line;
	::operator delete(object);
}

void operator delete[](void* object, const char*, const unsigned int)
{
	//file;
	//line;
	::operator delete(object);
}
