#ifndef LOGGING_H
#define LOGGING_H

#ifdef ANDROID_NDK

#include <log.h>

#define ORBSLAM3_LOG_FATAL(...)
#define ORBSLAM3_LOG_ERROR(...)
#define ORBSLAM3_LOG_WARN(...)
#define ORBSLAM3_LOG_INFO(...)
#define ORBSLAM3_LOG_DEBUG(...)
#define ORBSLAM3_LOG_VERBOSE(...)

#endif // ANDROID_NDK

#endif // LOGGING_H
