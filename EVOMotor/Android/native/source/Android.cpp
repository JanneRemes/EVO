#include <android/input.h>
#include <android/log.h>
#include <android/looper.h>

#include <Platform/Android/android_native_app_glu.h>
#include "Platform/FileReader.h"

#define LOG(message, ...) __android_log_print(ANDROID_LOG_DEBUG, "EvoAndroid", message, ## __VA_ARGS__)

static void processMessage (android_app* application, int32_t message);
static int32_t processInput (android_app* application, AInputEvent* event);

void android_main(android_app* application)
{
	application->onAppCmd = processMessage;
	application->onInputEvent = processInput;
	
	bool isRunning = true;
	android_poll_source* source;
	
	while(isRunning)
	{
		while(ALooper_pollAll(0, NULL, NULL, reinterpret_cast<void**>(&source)) >= 0)
		{
			if(source != NULL)
				source->process(application, source);
			
			if(application->destroyRequested != 0)
				isRunning = false;
		}
	}
}

static void processMessage(android_app* application, int32_t message)
{
	switch(message)
	{
		case APP_CMD_INIT_WINDOW:
			LOG("Window created");
			FileReader::manager = application->activity->assetManager;
			break;
			
		case APP_CMD_TERM_WINDOW:
			LOG("Window destroy");
			break;
	}
	
}

static int32_t processInput (android_app* application, AInputEvent* event)
{
	return 0;
}








