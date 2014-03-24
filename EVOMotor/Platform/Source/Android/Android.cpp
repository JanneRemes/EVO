#include <android/input.h>
#include <android/log.h>
#include <android/looper.h>

#include <Platform/Android/android_native_app_glue.h>
#include "../../../EVOMotor/Include/Engine.h"
#include "Platform/FileReader.h"
#include "Platform/debug.h"
#include <EGL/egl.h>
#include "Platform/OpenGL.hpp"

static void processMessage (android_app* application, int32_t message);
static int32_t processInput (android_app* application, AInputEvent* event);

struct android_engine
{
	android_app* application;
	EGLSurface surface;
	EGLContext context;
	EGLDisplay display;
	
	Engine* engine;
};

void android_main(android_app* application)
{
	app_dummy();
	application->onAppCmd = processMessage;
	application->onInputEvent = processInput;
	
	
	Engine* engine;
	engine = new Engine();
	FileReader::manager = application->activity->assetManager;

	android_engine androidEngine;
	androidEngine.application = application;
	androidEngine.engine = engine;
	application->userData = &androidEngine;

	//EGLContext context;
	//engine->init();
	
	bool isRunning = true;
	android_poll_source* source;
	
	while(isRunning)
	{
		while(ALooper_pollAll(0, NULL, NULL, reinterpret_cast<void**>(&source)) >= 0)
		{
			if(source != NULL)
				source->process(application, source);

			if(application->destroyRequested != 0)
			{
				isRunning = false;
				engine->deInit();
			}
		}
		
		
		/////INSERT UPDATE FUNCTIONS HERE
		if(engine->isInit())
		{
			engine->update();
			engine->draw();
			eglSwapBuffers(androidEngine.display, androidEngine.surface);
		}
		
		/////UPDATE FUNCTIONS ENDS HERE
	}
}

static void processMessage(android_app* application, int32_t message)
{
	android_engine* androidEngine = (android_engine*)application->userData;
	
	switch(message)
	{
		case APP_CMD_INIT_WINDOW:
		{
			writeLog("Window created");

			const EGLint attribs[] = 
			{
				EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
				EGL_BLUE_SIZE, 8,
				EGL_GREEN_SIZE, 8,
				EGL_RED_SIZE, 8,
				EGL_ALPHA_SIZE, 8,
				EGL_NONE
			};
			CheckEGLError("attribs");
			const EGLint contextAttribs[] =
			{
				EGL_CONTEXT_CLIENT_VERSION, 2,
				EGL_NONE
			};
			CheckEGLError("contextAttribs");
			EGLint w, h, dummy, format;
			CheckEGLError("eglint");
			EGLint numConfigs;
			CheckEGLError("numConfigs");
			EGLConfig config;
			CheckEGLError("config");
			
			//EGLSurface surface;
			//EGLContext context;

			/*EGLDisplay*/ androidEngine->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
			CheckEGLError("eglGetDisplay");
				writeLog("display %d", (int)androidEngine->display);
			if(androidEngine->display == EGL_NO_DISPLAY)
			{
				writeLog("display nodisplay");
			}
			
			eglInitialize(androidEngine->display, 0, 0);
			CheckEGLError("eglInitialize");
				writeLog("initialize");
			eglChooseConfig(androidEngine->display, attribs, &config, 1, &numConfigs);
			CheckEGLError("eglsChooseConfig");
				writeLog("eglChooseConfig");
			eglGetConfigAttrib(androidEngine->display, config, EGL_NATIVE_VISUAL_ID, &format);
			CheckEGLError("eglGetConfigAttrib");
				writeLog("eglGetConfigAttrib");
			//ANativeWindow_setBuffersGeometry(androidEngine->application->window, 0, 0, format);
			//CheckEGLError("ANativeWindow_setBuffersGeometry");
			androidEngine->surface = eglCreateWindowSurface(androidEngine->display, config, androidEngine->application->window, NULL);
			CheckEGLError("eglCreateWindowSurface");
			androidEngine->context = eglCreateContext(androidEngine->display, config, NULL, contextAttribs);
			CheckEGLError("eglCreateContext");
			if (eglMakeCurrent (androidEngine->display, androidEngine->surface, androidEngine->surface, androidEngine->context) == EGL_FALSE)
			{
				writeLog("Unable to eglMakeCurrent");
				return;
			}
			CheckEGLError("eglMakeCurrent");
				writeLog("eglMakeCurrent");
			eglQuerySurface(androidEngine->display, androidEngine->surface, EGL_WIDTH, &w);
			CheckEGLError("eglQuerySurface");
				writeLog("eglQuerySurface");
			eglQuerySurface(androidEngine->display, androidEngine->surface, EGL_HEIGHT, &h);
			CheckEGLError("eglQuerySurface");
				writeLog("eglQuerySurface");
				
			androidEngine->engine->init();
		}
			break;
			
		case APP_CMD_TERM_WINDOW:
			writeLog("Window destroy");
			androidEngine->engine->deInit();
			break;
	}
}

static int32_t processKeyInput(AInputEvent* event)
{
	const int32_t keyCode = AKeyEvent_getKeyCode(event);
	const int32_t keyState = AKeyEvent_getAction(event);
	return 0;
}

static int32_t processTouchInput(AInputEvent* event)
{
	float x;
	float y;
	const int32_t action = AMotionEvent_getAction(event);
	int32_t index;
	
	switch(action & AMOTION_EVENT_ACTION_MASK)
	{
	case AMOTION_EVENT_ACTION_DOWN:
	case AMOTION_EVENT_ACTION_POINTER_DOWN:
		index = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
			>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
		x = AMotionEvent_getX(event, index);
		y = AMotionEvent_getY(event, index);
		writeLog("TOUCH DOWN: [%f, %f]",x,y);
		
		break;

	case AMOTION_EVENT_ACTION_MOVE:
		{
			const int32_t touchCount = AMotionEvent_getPointerCount(event);
			for(int32_t i = 0; i < touchCount; ++i)
			{
				x = AMotionEvent_getX(event, i);
				y = AMotionEvent_getY(event, i);
				writeLog("TOUCH MOVE: [%f, %f]",x,y);
			}


		}
		break;

	case AMOTION_EVENT_ACTION_UP:
		index = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
			>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
		x = AMotionEvent_getX(event, index);
		y = AMotionEvent_getY(event, index);
		writeLog("TOUCH UP: [%f, %f]",x,y);
		break;

	default:
		break;
	}

	return 1;
}

static int32_t processInput (android_app* application, AInputEvent* event)
{
	switch(AInputEvent_getType(event))
	{
	case AINPUT_EVENT_TYPE_KEY:
		return processKeyInput(event);

	case AINPUT_EVENT_TYPE_MOTION:
		return processTouchInput(event);

	default:
		return 0;
	}
}
