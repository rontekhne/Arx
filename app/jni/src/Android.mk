LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

# Add your application source files here...
LOCAL_SRC_FILES := main.c  draw.c init.c input.c stage.c util.c sound.c text.c background.c highscores.c menu.c drops.c volume.c
LOCAL_SRC_FILES += main.h common.h defs.h init.h input.h stage.h structs.h util.h sound.h text.h background.h highscores.h menu.h drops.h volume.h databaseManager.h

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -lOpenSLES -llog -landroid

include $(BUILD_SHARED_LIBRARY)