#include "JAigoUELooper.h"
#include "main.h"

jclass CJAigoUELooper::_jclass = 0;

jmethodID CJAigoUELooper::_initId = 0;

CJAigoUELooper::CJAigoUELooper(JNIEnv* env, jobject object):CJObject(env,object)
{
}

CJAigoUELooper::~CJAigoUELooper(void)
{
}

void CJAigoUELooper::_Init(JNIEnv* env,CJPathClassLoader* oPathLoader){
	if (_jclass != 0) return;
	LOG_WRITE("===>CJAigoUELooper::_Init");

	_jclass = (jclass)env->NewGlobalRef((jobject)oPathLoader->findClass("auto/aigato/aigor/AigoMain$AigoUELooper"));
	_initId = env->GetMethodID(_jclass,"<init>","(Lauto/aigato/aigor/AigoMain;)V");

	//LOG_WRITE(" + [%p] CJAigoUELooper::_jclass",_jclass);
	//LOG_WRITE(" + [%p] CJAigoUELooper::init()",_initId);

	JNINativeMethod m[1];
	m[0].fnPtr = (void*)CUEThread::_Runtime;//		_UITimer;
	m[0].name = "UETimer";
	m[0].signature = "()V";
	int ret = env->RegisterNatives(_jclass, m, 1);
	LOG_WRITE(" CJAigoUELooper::_Init => RegisterNatives(): %d",ret);

}
void CJAigoUELooper::_Exit(JNIEnv* env){
	if (_jclass == 0) return;	
	env->DeleteGlobalRef((jobject)_jclass); _jclass = 0;	
}
