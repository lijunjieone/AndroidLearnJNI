package com.d.ui.base

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.annotation.LayoutRes
import androidx.databinding.DataBindingUtil
import androidx.databinding.ViewDataBinding
import androidx.fragment.app.Fragment
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.Lifecycle
import androidx.lifecycle.LifecycleRegistry
import androidx.lifecycle.ViewModelProviders
import com.d.ui.base.EventObserver
import com.d.ui.base.vm.BaseViewModel
import com.d.ui.utils.AppLifecycleListener
import com.d.ui.utils.ClassUtil
import java.util.*

abstract class BaseFragment<VM : AndroidViewModel, DB : ViewDataBinding> : Fragment(),
     Observer {

    private var oneTimeData = true

    lateinit var binding: DB
    // Fragment
    lateinit var viewModelPart: VM
    // Activity
    lateinit var viewModelMain: VM

    @get:LayoutRes
    abstract val layoutRes: Int

    abstract fun initView()
    open fun initData() {}
    open fun userVisibleData() {}

    open fun initDataBinding() {}

    open fun initViewModel() {}
    open fun paymentDialogClick() {}
    open fun feeDialogClick() {}

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        AppLifecycleListener.getInstance().addObserver(this)

        ClassUtil.getViewModel<VM>(this).also {
            it?.also {
                viewModelPart = ViewModelProviders.of(this).get(it)
                viewModelMain = ViewModelProviders.of(requireActivity()).get(it)

                obserLoadingEvent(viewModelMain)
                obserLoadingEvent(viewModelPart)
            }
            initViewModel()
        }
    }

    private fun obserLoadingEvent(viewModel: AndroidViewModel) {
        if (viewModel is BaseViewModel) {
//            val activity = requireActivity() as? BaseActivity ?: return
//            viewModel.loadingEvent.observe(activity, EventObserver {
//                if (it) {
//                    activity.showLoadingDialog()
//                } else {
//                    activity.hideLoadingDialog()
//                }
//            })
        }
    }


    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        binding = DataBindingUtil.inflate(inflater, layoutRes, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        initDataBinding()
        initView()
    }

    override fun setUserVisibleHint(isVisibleToUser: Boolean) {
        super.setUserVisibleHint(isVisibleToUser)
        visibleData()
    }

    private fun visibleData() {
        if (userVisibleHint && oneTimeData && lifecycle.currentState.isAtLeast(Lifecycle.State.CREATED)) {
            oneTimeData = false
            userVisibleData()
        }
    }

    override fun onActivityCreated(savedInstanceState: Bundle?) {
        super.onActivityCreated(savedInstanceState)
        binding.lifecycleOwner = this
        initData()
        visibleData()
    }

    override fun onDestroy() {
        super.onDestroy()
        AppLifecycleListener.getInstance().deleteObserver(this)
    }



    //切前台
    fun onMoveToForeground() {}

    //切后台
    fun onMoveToBackground() {}

    override fun update(o: Observable, arg: Any) {
        val isForeground = arg as Boolean
        if (isForeground) {
            onMoveToForeground()
        } else {
            onMoveToBackground()
        }
    }


    /**
     * Fragment 切换方式为hide/show时 自己手动下发生命周期
     */
    override fun onHiddenChanged(hidden: Boolean) {
        super.onHiddenChanged(hidden)
        if (activity == null) return

        val lifecycleRegistry = (lifecycle as LifecycleRegistry)
        if (hidden) {
            lifecycleRegistry.markState(Lifecycle.State.STARTED)
            onPause()
            lifecycleRegistry.markState(Lifecycle.State.CREATED)
            onStop()
        } else {
            lifecycleRegistry.markState(Lifecycle.State.RESUMED)
            onResume()
        }
    }

}
