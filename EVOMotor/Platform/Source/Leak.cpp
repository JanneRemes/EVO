#include "Platform/Leak.h"
#include "Platform/debug.h"

using namespace std;

//Public

Leak::Leak()
{
	if(_instance == NULL)
		_instance = this;

	//TODO erroer handling
}

Leak::~Leak()
{

	Pointers::const_iterator end = _pointers.end();

	for(Pointers::const_iterator i = _pointers.begin(); i != end; ++i)
		writeLog("MEMORY LEAK DETECTED @ %s line %u\n", i->second.file, i->second.line);

	_instance = NULL;
}

//Static

void Leak::addPointer(void* pointer, const char* file, const unsigned int line)
{
	if(_instance != NULL)
	{
		PointerInfo info;
		info.file = file;
		info.line = line;

		Pointers::value_type pair(pointer, info);
		_instance->_pointers.insert(pair);
	}

}

void Leak::removePointer(void* pointer)
{
	if(_instance != NULL)
		_instance->_pointers.erase(pointer);
}

//Private

Leak* Leak::_instance = NULL;