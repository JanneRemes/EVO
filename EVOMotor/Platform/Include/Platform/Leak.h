#ifndef LEAK_H_
#define LEAK_H_
//fix name later
#include <map>

class Leak
{
public:
	Leak();
	~Leak();

	static void addPointer(void* pointer, const char* file, const unsigned int line);
	static void removePointer(void* pointer);

private:

	struct PointerInfo
	{
		const char* file;
		unsigned int line;
	};

	typedef std::map<void*, PointerInfo> Pointers;

	static Leak* _instance;

	Pointers _pointers;

	Leak(const Leak& leak);
	Leak& operator =(const Leak& leak);


};

#endif