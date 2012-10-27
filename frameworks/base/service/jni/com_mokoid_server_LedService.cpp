#define LOG_TAG "MokoidPlatform"
#include "utils/Log.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <jni.h>
#include <mokoid/led.h>

struct led_control_device_t *sLedDevice = NULL;

static jboolean
mokoid_init(JNIEnv *env, jclass clazz)
{
    led_module_t* module;

    LOGI("LedService JNI: mokoid_init() is invoked.");

    if (hw_get_module(LED_HARDWARE_MODULE_ID, (const hw_module_t**)&module) == 0) {
        LOGI("LedService JNI: LED Stub found.");
        if (led_control_open(&module->common, &sLedDevice) == 0) {
    	    LOGI("LedService JNI: Got Stub operations.");
            return 0;
        }
    }

    LOGE("LedService JNI: Get Stub operations failed.");
    return -1;
}
//前面两个参数是虚拟机规定的，
static jboolean mokoid_setOn(JNIEnv* env, jobject thiz, jstring mesg)
{
    LOGI("LedService JNI: mokoid_setOn() is invoked.");

    if (sLedDevice == NULL) {
        LOGI("LedService JNI: sLedDevice was not fetched correctly.");
        return -1;
    } else {
        return sLedDevice->set_on(sLedDevice, led);
    }

    return 0;
}

static jboolean mokoid_setOff(JNIEnv* env, jobject thiz, jint led, jfloat x,
				jobject str)//jintarray c
{
    LOGI("LedService JNI: mokoid_setOff() is invoked.");

    if (sLedDevice == NULL) {
        LOGI("LedService JNI: sLedDevice was not fetched correctly.");
        return -1;
    } else {
        return sLedDevice->set_off(sLedDevice, led);
    }

    return 0;
}
static jboolean mokoid_gethello(JNIEnv* env, jobject thiz,jstring x,
				jobject str)
{
    LOGI("LedService JNI: mokoid_setOff() is invoked.");

    if (sLedDevice == NULL) {
        LOGI("LedService JNI: sLedDevice was not fetched correctly.");
        return -1;
    } else {
        return sLedDevice->set_off(sLedDevice, led);
    }

    return 0;
}




static const JNINativeMethod gMethods[] = {
    {"_init",	  	"()Z",
			(void*)mokoid_init},
    { "_set_on",          "(ILjavalang/String;)Z",
                        (void*)mokoid_setOn },
    { "_set_off",          "(I[I)Z",
                        (void*)mokoid_setOff },
    { "_get_hello",          "(Ljava/lang/string;)Z",
                        (void*)mokoid_gethello },
};

int registerMethods(JNIEnv* env) {
    static const char* const kClassName =
        "com/mokoid/server/LedService";
    jclass clazz;

    /* look up the class */
    clazz = env->FindClass(kClassName);
    if (clazz == NULL) {
        LOGE("Can't find class %s\n", kClassName);
        return -1;
    }

    /* register all the methods */
    if (env->RegisterNatives(clazz, gMethods,
            sizeof(gMethods) / sizeof(gMethods[0])) != JNI_OK)
    {
        LOGE("Failed registering methods for %s\n", kClassName);
        return -1;
    }

    /* fill out the rest of the ID cache */
    return 0;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("ERROR: GetEnv failed\n");
	goto bail;
    }
    assert(env != NULL);

    registerMethods(env);

    /* success -- return valid version number */
    result = JNI_VERSION_1_4;

bail:
    return result;
}
