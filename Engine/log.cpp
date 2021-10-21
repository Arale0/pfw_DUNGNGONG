#include "log.h"
#include <android/log.h> 

CLog::CLog(){}
CLog::~CLog(){}

void CLog::LogWrite(const char *fmt, ...){
#ifdef ENABLE_DEBUG
#define LOG_TAG "AIGOTEAM" 
	va_list ap;
	va_start(ap, fmt);
	__android_log_vprint(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ap);
	va_end(ap);
#endif	
}