#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <ifaddrs.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <linux/ashmem.h>
#include <jni.h>
#include <pthread.h>

#include <AigoApi.h>
#include <ModuleTable.h>
#include <ByteBuffer.h>
#include <Checksum.h>
#include <XOR.h>

#include "../Common/global_android.h"
#include "log.h"
#include "MainHook.h"
#include <math.h>

void	_ExitParametes();

extern "C" {
	extern  CMainHook*		_theApp; 	
	extern	int				_fdMemShared;
	extern  MEMORYSHARED*	_pShared;
	extern  DWORD			_dwModule;
	extern  void*			_hModule;
	extern	JavaVM*			_jvm;

}

