#ifndef ANDROIDWINDOW_H_
#define ANDROIDWINDOW_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <android/sensor.h>
//#include <android/_native_app_glue.h>

class AndroidWindow
{
public:
	AndroidWindow(int width, int height, const char* title);
	~AndroidWindow();
	bool isOpen();
	void pollEvents();
	void close();

	static int getKey(int key);

	struct saved_state
	{
		float angle;
		int x;
		int y; //vaihda "int32_t" jos ei toimi
	};
private:

	void init();

	int _width;
	int _height;
	const char* _title;

	struct android_app* app;

	ASensorManager* sensorManager;
	const ASensor* accelerometerSensor;
	ASensorEventQueue* sensorEventQueue;

	int animating;
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	struct saved_state state;
};

#endif