package com.learn.jni

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val provider = DataProvider()
        // Example of a call to a native method
        sample_text.text = provider.getPressure()
//        sample_text.text = provider.stringFromJNI()
//        sample_text.text = provider.sayHelloInC("lijunjie")
        sample_text.setOnClickListener {
            Toast.makeText(baseContext,"call",Toast.LENGTH_SHORT).show()
            provider.callFromJava()
        }
        sample_text.setOnLongClickListener {

            provider.addInt(10,30);
            true
        }
//        sample_text.text = "${add(10,20) }"
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */



}
