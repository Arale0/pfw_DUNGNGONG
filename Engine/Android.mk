LOCAL_PATH := $(call my-dir)
MY_AIGO_INC := $(LOCAL_PATH)/../../__AIGGlobal/Androids/inc
MY_AIGO_LIB := $(LOCAL_PATH)/../../__AIGGlobal/Androids/lib
MY_AIGO_SRC := $(LOCAL_PATH)/../../__AIGGlobal/Androids/src
########################
# prepare main_aigo
include $(CLEAR_VARS)
LOCAL_MODULE    := main_aigo
LOCAL_SRC_FILES := $(MY_AIGO_LIB)/$(TARGET_ARCH_ABI)/libmain_aigo.a
include $(PREBUILT_STATIC_LIBRARY)
########################

########################
# prepare crypto_aigo
include $(CLEAR_VARS)
LOCAL_MODULE    := crypto_aigo
LOCAL_SRC_FILES := $(MY_AIGO_LIB)/$(TARGET_ARCH_ABI)/libcrypto_aigo.a
include $(PREBUILT_STATIC_LIBRARY)
########################

########################
# prepare crypto
include $(CLEAR_VARS)
LOCAL_MODULE    := crypto
LOCAL_SRC_FILES := $(MY_AIGO_LIB)/$(TARGET_ARCH_ABI)/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)
########################

include $(CLEAR_VARS)
LOCAL_MODULE     := aigo_c
LOCAL_SRC_FILES  := $(wildcard $(LOCAL_PATH)/*.cpp)
LOCAL_SRC_FILES  += $(wildcard $(MY_AIGO_SRC)/AI2/*.cpp)

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(MY_AIGO_INC)
LOCAL_C_INCLUDES += $(MY_AIGO_INC)/Main
LOCAL_C_INCLUDES += $(MY_AIGO_INC)/Crypto
LOCAL_C_INCLUDES += $(MY_AIGO_SRC)/AI2

LOCAL_CFLAGS     := -Wall -Wextra -Wno-sentinel -Wno-unused-parameter -fvisibility=hidden -Wno-implicit-function-declaration \
					-Wno-int-conversion -Wno-unused-variable -Wno-format -Wno-format-extra-args -Wno-integer-overflow \
					-DUNITY_IL2CPP
					
LOCAL_STATIC_LIBRARIES	+= main_aigo crypto_aigo crypto
LOCAL_CONLYFLAGS := -std=c++11
LOCAL_LDLIBS     := -llog
include $(BUILD_SHARED_LIBRARY)
