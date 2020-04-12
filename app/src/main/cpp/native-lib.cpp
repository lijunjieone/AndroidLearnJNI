#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_learn_jni_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_learn_jni_MainActivity_stringFromJNI2(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from3 C++";
    LOGD("%s","haha");
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL Java_com_learn_jni_MainActivity_sayHelloInC
        (JNIEnv * env, jobject, jstring jStr) {
    LOGD("%s",jStr);
    if (!jStr)
        return env->NewStringUTF("");

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    std::string say_hello ="say hello for "+ret;
    return env->NewStringUTF(say_hello.c_str());



}

extern "C"

JNIEXPORT jint JNICALL Java_com_learn_jni_MainActivity_add
        (JNIEnv * env, jobject, jint a, jint b) {
    LOGD("%s","add commond");
    return a+b;
}

std::string jstring2string(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}


