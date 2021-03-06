#include <jni.h>
#include <string>
#include <android/log.h>
#include "hello.h"
#include "utils.h"

#include "libmp3lame/lame.h"


#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_learn_jni_DataProvider_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    Process * ptr = new Process();
    std:string h =  ptr->process(128);
    return env->NewStringUTF(h.c_str());
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_learn_jni_DataProvider_stringFromJNI2(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from3 C++";
    LOGD("%s","haha");
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL Java_com_learn_jni_DataProvider_sayHelloInC
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

JNIEXPORT jint JNICALL Java_com_learn_jni_DataProvider_add
        (JNIEnv * env, jobject, jint a, jint b) {
    LOGD("%s","add commond");
    return a+b;
}

/*
 * Class:     com_learn_jni_DataProvider
 * Method:    callInt
 * Signature: (II)I
 */
extern "C"
JNIEXPORT jint JNICALL Java_com_learn_jni_DataProvider_callInt
        (JNIEnv * env, jobject obj, jint a, jint b){
    char* classname = "com/learn/jni/DataProvider";
    jclass clazz;
    clazz = env->FindClass(classname);
    if(clazz == 0) {
        LOGD("Can't find class");
    }else {
        LOGD("Find class");
    }

    jmethodID java_method = env->GetMethodID(clazz,"addInt","(II)I");
    if(java_method == 0){
        LOGD("Can't find java_method");
    }else {
        LOGD("Find method");
    }

    jint result = env->CallIntMethod(obj,java_method,a,b);
    LOGD("c result %d",result);
    return result;
}

extern "C"
/*
 * Class:     com_learn_jni_DataProvider
 * Method:    getLameVersion
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_learn_jni_DataProvider_getLameVersion
        (JNIEnv * env, jobject obj){
    return env->NewStringUTF(get_lame_version());
}

char* jstringToChar(JNIEnv* env, jstring jstr) ;

extern "C"
/*
 * Class:     com_learn_jni_DataProvider
 * Method:    convertAudio
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_learn_jni_DataProvider_convertAudio
        (JNIEnv * env, jobject obj, jstring input, jstring output){
    char* inputname = jstringToChar(env,input);
    char* outputname = jstringToChar(env,output);
    LOGD("input:%s,output:%s",inputname,outputname);

    FILE * wav = fopen(inputname,"rb");
    FILE * mp3 = fopen(outputname,"wb");
    int read;
    int write;

    short int wav_buffer[8192*2];
    unsigned char mp3_buffer[8192];

    lame_t lame = lame_init();
    lame_set_in_samplerate(lame,44100);
    lame_set_num_channels(lame,2);
    lame_set_VBR(lame,vbr_default);
    lame_init_params(lame);

    LOGD("lame init finish");

    do {
        read = fread(wav_buffer,sizeof(short int)*2,8182,wav);
        if(read == 0){
            write = lame_encode_flush(lame,mp3_buffer,8192);
            fwrite(mp3_buffer,sizeof(char),write,mp3);

        }else {
            write = lame_encode_buffer_interleaved(lame,wav_buffer,read,mp3_buffer,8192);
            fwrite(mp3_buffer,sizeof(char),write,mp3);
        }
    }while(read!=0);

    LOGD("encode finish");

    lame_close(lame);
    fclose(mp3);
    fclose(wav);
    LOGD("convert complete");
}

extern "C"

JNIEXPORT jfloat JNICALL Java_com_learn_jni_DataProvider_addFloat
        (JNIEnv * env, jobject obj, jfloat a, jfloat b){
    return a;
}

extern float addFloat2(float a, float b) ;


int getPressure() {
    return rand();
}
extern "C"
JNIEXPORT jstring JNICALL Java_com_learn_jni_DataProvider_getPressure
        (JNIEnv * env, jobject obj){
    std:string str=" ";
    std::stringstream ss;
    ss << getPressure()%300;
    ss >> str;
    std::string result = "Pressure:"+ str;
    return env->NewStringUTF(result.c_str());
}
/*
 * Class:     com_learn_jni_DataProvider
 * Method:    callFromJava
 * Signature: ()V
 */
extern "C"
JNIEXPORT void JNICALL Java_com_learn_jni_DataProvider_callFromJava
        (JNIEnv * env, jobject obj){
    char* classname = "com/learn/jni/DataProvider";
    jclass clazz;
    clazz = env->FindClass(classname);
    if(clazz == 0) {
        LOGD("Can't find class");
    }else {
        LOGD("Find class");
    }

    jmethodID java_method = env->GetMethodID(clazz,"helloFromJava","()V");
    if(java_method == 0){
        LOGD("Can't find java_method");
    }else {
        LOGD("Find java_method");
    }

    env->CallVoidMethod(obj,java_method);

}

jstring charTojstring(JNIEnv* env, const char* pat) {
    //定义java String类 strClass
    jclass strClass = (env)->FindClass("Ljava/lang/String;");
    //获取String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    //建立byte数组
    jbyteArray bytes = (env)->NewByteArray(strlen(pat));
    //将char* 转换为byte数组
    (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*) pat);
    // 设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = (env)->NewStringUTF("GB2312");
    //将byte数组转换为java String,并输出
    return (jstring) (env)->NewObject(strClass, ctorID, bytes, encoding);
}

char* jstringToChar(JNIEnv* env, jstring jstr) {
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char*) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
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


