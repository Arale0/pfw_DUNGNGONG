#pragma once

#define ENABLE_DEBUG 1

#define LOG_WRITE CLog::LogWrite

class CLog{
public:
	CLog();
	~CLog();
	static void LogWrite(const char *fmt, ...);
};


