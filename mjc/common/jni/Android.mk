ifneq ($(strip $(MTK_EMULATOR_SUPPORT)),yes)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
        mjc_jni.cpp

LOCAL_C_INCLUDES := $(JNI_H_INCLUDE)

LOCAL_C_INCLUDES += \
        $(TOP)/frameworks/base/include \

LOCAL_SHARED_LIBRARIES := \
        liblog \
        libcutils \
        libutils \

LOCAL_PRELINK_MODULE := false

LOCAL_MODULE := libMJCjni
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk

LOCAL_MODULE_TAGS := optional

include $(MTK_SHARED_LIBRARY)

endif
