#if defined(WIN32)
	#include <incl/GL/glew.h>
	#include <incl/GLFW/glfw3.h>

#elif __ANDROID__
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>


#endif
