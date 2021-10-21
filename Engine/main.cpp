#include "main.h"

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0
#define VERSION_BUILD 1
const char CONST_VERSION[5] AIGO_SECTION = {VERSION_MAJOR,VERSION_MINOR,VERSION_PATCH,VERSION_BUILD,0}; 
CStdString AIGO_VERSION(CONST_VERSION);


CMainHook*		_theApp			= NULL;		//Running in thread of Hook
int				_fdMemShared	= -1;
MEMORYSHARED*	_pShared		= NULL;
DWORD			_dwModule		= 0;
void*			_hModule		= NULL;
JavaVM*			_jvm			= NULL;


void _InitParametes(){
	Dl_info dlInfo;
	dladdr((void*)CMainHook::_UnloadLibrary,&dlInfo);
	_dwModule = (DWORD)dlInfo.dli_fbase;
	_hModule = dlopen(dlInfo.dli_fname, RTLD_NOLOAD);	

	_fdMemShared = open(ASHMEM_NAME_DEF, O_RDWR);	
	DWORD dwMemID = _dwModule ^ getpid();
	CStdString szName;
	szName.Fmt("aigo_%X",dwMemID);

	int iSize = sizeof(MEMORYSHARED);
	ioctl(_fdMemShared, ASHMEM_SET_NAME, szName.c_str());
	ioctl(_fdMemShared, ASHMEM_SET_SIZE, iSize);
	_pShared = (MEMORYSHARED*)mmap(NULL, iSize, PROT_READ | PROT_WRITE, MAP_SHARED, _fdMemShared, 0);		

	//LOG_WRITE(" [%p]SHARED [%p]MODULE [%p]INSTANCE\n",_pShared,_dwModule,_hModule);
}

void _ExitParametes(){
	static BOOL _Called = FALSE;
	if (_Called) return;
	_Called = TRUE;

	if (_pShared){
		munmap(_pShared,sizeof(MEMORYSHARED));
		_pShared = NULL;	
	}
	if (_fdMemShared){
		close(_fdMemShared);
		_fdMemShared = -1;
	}
	_jvm = NULL;

	//clean aigo.dex
	CModuleTable modTable;
	modTable.Update("/data/local/tmp/aigo/aigor.dex",NULL);
	MODULE_TABLE* pMods = modTable.Get();
	for (UINT u = 0; u < pMods->uNumEntries; ++u)
	{
		MODULE_INFO* pTable = &pMods->table[u];
		munmap((void*)pTable->dwModule,pTable->dwSize);	
	}	
}

void __attribute__((constructor)) InitInstance(){
	LOG_WRITE("===== HOOK - InitInstance =====");
	_InitParametes();
}
void __attribute__((destructor)) ExitInstance(){
	CMainHook::_UnloadLibrary();	
	LOG_WRITE("***** HOOK - ExitInstance *****");
}

void* _InitMain(void* lpData){
	if (!_theApp) return NULL;
	_theApp->Start();
	return NULL;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved){
	LOG_WRITE(" HOOK - JNI_OnLoad() [%p]...",vm);
	if (vm == NULL || _theApp) {
		LOG_WRITE(" HOOK - JNI_OnLoad() 1");
		return JNI_VERSION_1_6;	
	}
	_jvm = vm;	


	LOG_WRITE(" HOOK - JNI_OnLoad() 2");
	_theApp = new CMainHook();
	pthread_t uTid;
	pthread_create(&uTid,NULL,_InitMain,NULL);	

	LOG_WRITE(" HOOK - JNI_OnLoad() 3");
	return JNI_VERSION_1_6;
}
