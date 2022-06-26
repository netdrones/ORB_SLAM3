// Copyright 2022 NetDrones Inc. All rights reserved.
#ifndef ORB_SLAM3_ORB_LOG_H
#define ORB_SLAM3_ORB_LOG_H

#ifdef ANDROID

#include <android/log.h>

//#ifdef NDEBUG
//
//#define  LOGV(...)
//#define  LOGD(...)
//#define  LOGI(...)
//#define  LOGW(...)
//#define  LOGE(...)
//
//#else

#define ANDROID_LOG_TAG "ORB_SLAM3"

#define  LOGV(format, ...)  __android_log_print(ANDROID_LOG_VERBOSE, ANDROID_LOG_TAG , "[%s:%d/%s] " format, basename(__FILE__), __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define  LOGD(format, ...)  __android_log_print(ANDROID_LOG_DEBUG, ANDROID_LOG_TAG , "[%s:%d/%s] " format, basename(__FILE__), __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define  LOGI(format, ...)  __android_log_print(ANDROID_LOG_INFO, ANDROID_LOG_TAG , "[%s:%d/%s] " format, basename(__FILE__), __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define  LOGW(format, ...)  __android_log_print(ANDROID_LOG_WARN, ANDROID_LOG_TAG , "[%s:%d/%s] " format, basename(__FILE__), __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define  LOGE(format, ...)  __android_log_print(ANDROID_LOG_ERROR, ANDROID_LOG_TAG , "[%s:%d/%s] " format, basename(__FILE__), __LINE__, __FUNCTION__, ##__VA_ARGS__)

//#endif // NDEBUG

#else // ANDROID

#define  LOGV(format, ...) fprintf(stderr, format "\n", ##__VA_ARGS__)
#define  LOGD(format, ...) fprintf(stderr, format "\n", ##__VA_ARGS__)
#define  LOGI(format, ...) fprintf(stderr, format "\n", ##__VA_ARGS__)
#define  LOGW(format, ...) fprintf(stderr, format "\n", ##__VA_ARGS__)
#define  LOGE(format, ...) fprintf(stderr, format "\n", ##__VA_ARGS__)

#endif // ANDROID

#endif // ORB_SLAM3_ORB_LOG_H