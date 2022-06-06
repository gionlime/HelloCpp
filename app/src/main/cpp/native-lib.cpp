#include <jni.h>
#include <string>
#include <android/log.h>

#include "people/People.h"  //尖括号从搜索路径搜索  双引号从相对路径搜索


#define  LOGI(...) __android_log_print(ANDROID_LOG_INFO, "WELLEE", __VA_ARGS__)

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, "WELLEE", __VA_ARGS__)

#define  LOGD(...)  __android_log_print(ANDROID_LOG_INFO, "WELLEE", __VA_ARGS__)


//静态注册
//extern "C" JNIEXPORT jstring JNICALL
//Java_com_wellee_hellocpp_MainActivity_stringFromJNI(
//        JNIEnv *env,
//        jobject /* this */) {
//    std::string hello = "Hello from C++";
//
//    People people;
//    return env->NewStringUTF(people.getString().c_str());
//}

/**
 * 调用java的方法
 */
void callJava(JNIEnv *env, jobject obj, const char *name, const char *method, const char *sig) {
    jclass mainActivity = env->FindClass(name);
    jmethodID getNameID = env->GetMethodID(mainActivity, method, sig);
    env->CallVoidMethod(obj, getNameID);
}

#define JAVA_CLASS "com/wellee/hellocpp/MainActivity"
#define JAVA_METHOD "tip"
#define JAVA_SIG "()V"

/**
 * 映射java中对应stringFromJNI方法 参数类型必须一致
 */
jstring native_hello(JNIEnv *env, jobject object) {
    callJava(env, object, JAVA_CLASS, JAVA_METHOD, JAVA_SIG);
    return env->NewStringUTF("Hello from C++");
}

/**
 * 映射java中对应sum方法 参数类型必须一致
 */
jint native_sum(JNIEnv *env, jobject object, int x, int y) {
    return x + y;
}

JNINativeMethod methods[] = {{"stringFromJNI", "()Ljava/lang/String;", (void *) native_hello},
                             {"sum",           "(II)I",                (void *) native_sum}};

//动态注册
jint registerNativeMethod(JNIEnv *env, const char *name, JNINativeMethod *methods, jint nMethods) {
    jclass cl = env->FindClass(name);
    if (cl == nullptr) {
        return JNI_FALSE;
    }
    if ((env->RegisterNatives(cl, methods, nMethods)) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6)) {
        return JNI_FALSE;
    }
    registerNativeMethod(env, JAVA_CLASS, methods, 2);
    return JNI_VERSION_1_6;
}

/**
 * 接收java的String 转化为C的字符串
 */
extern "C" JNIEXPORT jstring JNICALL
Java_com_wellee_hellocpp_MainActivity_callNativeString(
        JNIEnv *env,
        jobject /* this */, jstring jstr) {
    const char *str = env->GetStringUTFChars(jstr, 0);
    LOGD("callNativeString————%s", str);
    env->ReleaseStringUTFChars(jstr, str);
    return env->NewStringUTF("this is C style string");
}
