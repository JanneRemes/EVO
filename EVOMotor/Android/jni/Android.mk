LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := freetype
LOCAL_SRC_FILES := ../../depencies/incl/freetype-gl-a/libfreetype.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libfreetypegl_static
LOCAL_SRC_FILES := ../../depencies/incl/freetype-gl-a/libfreetypegl_static.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := evoplatform
LOCAL_CFLAGS := -D GLM_FORCE_RADIANS
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Platform/Include \
					$(LOCAL_PATH)/../../depencies \
					$(LOCAL_PATH)/../../depencies/incl/freetype

PLATFORM_PATH := ../../Platform/Source

LOCAL_SRC_FILES := \
	$(PLATFORM_PATH)/Camera.cpp \
	$(PLATFORM_PATH)/Graphics.cpp \
	$(PLATFORM_PATH)/IndexData.cpp \
	$(PLATFORM_PATH)/Leak.cpp \
	$(PLATFORM_PATH)/New.cpp \
	$(PLATFORM_PATH)/Object.cpp \
	$(PLATFORM_PATH)/Rectangle.cpp \
	$(PLATFORM_PATH)/Shader.cpp \
	$(PLATFORM_PATH)/SpriteBatch.cpp \
	$(PLATFORM_PATH)/SpriteObject.cpp \
	$(PLATFORM_PATH)/SpriteSheetObject.cpp \
	$(PLATFORM_PATH)/Text.cpp \
	$(PLATFORM_PATH)/Texture.cpp \
	$(PLATFORM_PATH)/VertexData.cpp \
	$(PLATFORM_PATH)/Viewport.cpp \
	$(PLATFORM_PATH)/Android/FileReader.cpp \
	$(PLATFORM_PATH)/Android/Input.cpp \
	$(PLATFORM_PATH)/Android/Window.cpp \
	

include $(BUILD_STATIC_LIBRARY)

 



include $(CLEAR_VARS)

LOCAL_MODULE := evoandroid
LOCAL_CFLAGS := -D GLM_FORCE_RADIANS
GAME_PATH := $(LOCAL_PATH)/../../EVOMotor
PLATFORM_PATH := ../../Platform/Source

LOCAL_STATIC_LIBRARIES := evoplatform libfreetypegl_static freetype

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Platform/Include \
					$(LOCAL_PATH)/../../depencies \
					$(GAME_PATH)/ 


LOCAL_SRC_FILES := \
					../../EVOMotor/Source/Engine.cpp\
					../../EVOMotor/Source/Background.cpp\
					../../EVOMotor/Source/Fireball.cpp\
					$(PLATFORM_PATH)/Android/android_native_app_glue.c \
					$(PLATFORM_PATH)/Android/Android.cpp
	 

LOCAL_LDLIBS := -landroid -lEGL -lGLESv2 -llog 


include $(BUILD_SHARED_LIBRARY)
 
 
