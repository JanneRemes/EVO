/* Window.h
** Directs include file depending
** on the operating system.
**
*/

#if defined(WIN32) //If program is opened with windows system, include this file
#include <Platform/Win/Window.h>

#elif __ANDROID__ //If program is opened with android system, include this file
#include <Platform/Android/Window.h>

#endif