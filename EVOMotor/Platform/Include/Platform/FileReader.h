//I made dis
//Kommentointi is DONE

#if defined(WIN32)
	#include "Platform/Win/FileReader.h"
#elif __ANDROID__
	#include "Platform/Android/FileReader.h"
#endif