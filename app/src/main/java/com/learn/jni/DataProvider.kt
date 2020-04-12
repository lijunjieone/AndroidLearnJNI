package com.learn.jni

import android.util.Log

class DataProvider {

    fun helloFromJava(){
        Log.e("TAG","helloFromJava")

    }

    fun addInt(a:Int,b:Int):Int {
        return a+b
    }

    external fun stringFromJNI(): String
    external fun stringFromJNI2(): String
    external fun add(a:Int,b:Int):Int
    external fun sayHelloInC(s:String):String

    external fun callInt(a:Int,b:Int):Int
    external fun callFromJava()

    external fun getPressure():String

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}