package com.d.ui.base

import android.content.DialogInterface
import android.os.Bundle
import android.view.MotionEvent
import android.widget.Toast
import androidx.annotation.LayoutRes
import androidx.appcompat.app.AppCompatActivity
import androidx.databinding.DataBindingUtil
import androidx.databinding.ViewDataBinding
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.ViewModelProviders
import com.d.ui.base.EventObserver
import com.d.ui.base.vm.BaseViewModel
import com.d.ui.utils.AppLifecycleListener
import com.d.ui.utils.ClassUtil


import java.util.*

abstract class BaseActivity<VM : AndroidViewModel, DB : ViewDataBinding> : AppCompatActivity(), Observer {

    lateinit var binding: DB
    lateinit var viewModel: VM

    @get:LayoutRes
    abstract val layoutRes: Int

    abstract fun initView()

    open fun initData() {}

    open fun initDataBinding() {}

    open fun initViewModel() {}

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        AppLifecycleListener.getInstance().addObserver(this)

        binding = DataBindingUtil.inflate(layoutInflater, layoutRes, null, false)
        binding.root.also {
            window.setContentView(it)
            binding.lifecycleOwner = this
//            binding.setVariable(BR.font, FontUtil.install)
        }

        ClassUtil.getViewModel<VM>(this).also {
            it?.also {
                viewModel = ViewModelProviders.of(this).get(it)
                obserLoadingEvent(viewModel)
            }
        }

        initViewModel()
        initDataBinding()
        initView()
        initData()
    }

    private fun obserLoadingEvent(viewModel: AndroidViewModel) {
        if (viewModel is BaseViewModel) {
            viewModel.loadingEvent.observe(this, EventObserver { handleLoadingDialog(it) })
        }
    }

    private fun handleLoadingDialog(show: Boolean) {
        if (show) {
            showLoadingDialog()
        } else {
            hideLoadingDialog()
        }
    }

    fun hideLoadingDialog() {
        Toast.makeText(this,"hide dialog",Toast.LENGTH_SHORT).show()
    }
    fun showLoadingDialog() {
        Toast.makeText(this,"show dialog",Toast.LENGTH_SHORT).show()
    }

    override fun onResume() {
        super.onResume()
    }



    override fun update(o: Observable?, arg: Any?) {
        val isForeground = arg as Boolean
    }
}
