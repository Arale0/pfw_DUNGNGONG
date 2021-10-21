#include "JAigoUILooper.h"
#include "main.h"

jclass CJAigoUILooper::_jclass = 0;

jmethodID CJAigoUILooper::_initId = 0;

CJAigoUILooper::CJAigoUILooper(JNIEnv* env, jobject object):CJObject(env,object)
{
}

CJAigoUILooper::~CJAigoUILooper(void)
{
}

void CJAigoUILooper::_Init(JNIEnv* env,CJPathClassLoader* oPathLoader){
	if (_jclass != 0) return;
	LOG_WRITE("===>CJAigoUILooper::_Init");

	_jclass = (jclass)env->NewGlobalRef((jobject)oPathLoader->findClass("auto/aigato/aigor/AigoMain$AigoUILooper"));
	_initId = env->GetMethodID(_jclass,"<init>","(Lauto/aigato/aigor/AigoMain;)V");

	//LOG_WRITE(" + [%p] CJAigoUILooper::_jclass",_jclass);
	//LOG_WRITE(" + [%p] CJAigoUILooper::init()",_initId);

	JNINativeMethod m[1];
	m[0].fnPtr = (void*)CUIThread::_Runtime;
	m[0].name = "UITimer";
	m[0].signature = "()V";
	int ret = env->RegisterNatives(_jclass, m, 1);
	LOG_WRITE(" CJAigoUILooper::_Init => RegisterNatives(): %d",ret);

}
void CJAigoUILooper::_Exit(JNIEnv* env){
	if (_jclass == 0) return;	
	env->DeleteGlobalRef((jobject)_jclass); _jclass = 0;	
}
