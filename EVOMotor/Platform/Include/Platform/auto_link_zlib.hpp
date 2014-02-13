#pragma once
#define ZLIB_LIB_NAME "zlib"

#if defined(zlib_LIB_DYNAMIC)
#  define ZLIB_LIB_PREFIX
#elif defined(_WIN32)
#  define ZLIB_LIB_PREFIX "lib"
#endif

#if defined(_WIN64)
#  define ZLIB_LIB_PLATFORM "-x64"
#elif defined(_WIN32)
#  define ZLIB_LIB_PLATFORM "-x86"
#endif

#ifdef _DLL
#  if defined(_DEBUG)
// MDd
#    define ZLIB_LIB_RT_OPT "-gd"
#  else
// MD
#    define ZLIB_LIB_RT_OPT
#  endif
#else
#  if defined(_DEBUG)
// MTd
#    define ZLIB_LIB_RT_OPT "-sgd"
#  else
// MT
#    define ZLIB_LIB_RT_OPT "-s"
#  endif
#endif

#  pragma comment(lib, ZLIB_LIB_PREFIX ZLIB_LIB_NAME ZLIB_LIB_RT_OPT ZLIB_LIB_PLATFORM ".lib")
// static MDd x86 : libzlib-gd-x86.lib
// static MD x86 :  libzlib-x86.lib
// static MTd x86 : libzlib-sgd-x86.lib
// static MT x86 :  libzlib-s-x86.lib
//#  pragma comment(lib, ZLIB_LIB_PREFIX ZLIB_LIB_NAME "zlib" ZLIB_LIB_RT_OPT ZLIB_LIB_PLATFORM ".lib")
// dll MDd x86 : zlib-gd-x86.lib
// dll MD x86 :  zlib-x86.lib
// dll MTd x86 : zlib-sgd-x86.lib
// dll MT x86 :  zlib-s-x86.lib
