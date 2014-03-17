#ifndef NEW_H_
#define NEW_H_

#ifdef NDEBUG
	#define EVO_NEW new
#else
	#define EVO_NEW new (__FILE__, __LINE__)
#endif

void* operator new(const unsigned int size);
void* operator new[](const unsigned int size);
void* operator new(const unsigned int size, const char* file, const unsigned int line);
void* operator new[](const unsigned int size, const char* file, const unsigned int line);

void operator delete(void* object);
void operator delete[](void* object);
void operator delete(void* object, const char* file, const unsigned int line);
void operator delete[](void* object, const char* file, const unsigned int line);

#endif