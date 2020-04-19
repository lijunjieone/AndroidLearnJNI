package com.d.ui.base.vm

import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.MutableLiveData
import com.d.ui.base.Event

/**
 */
open class BaseViewModel(application: Application) : AndroidViewModel(application) {

    var position: Long = 0
    var isFirst = true

    /**
     */
    val loadingEvent = MutableLiveData<Event<Boolean>>()

    val showError = MutableLiveData<Event<Unit>>()
    var showAlert = MutableLiveData<Event<String>>()

    val loadingQueue = mutableListOf<Boolean>()


    fun postLoadingEvent(loading: Boolean) {
        loadingEvent.value = Event(loading)
    }

    fun postLoadingQueueEvent(loading: Boolean) {
        if (loading) {
            loadingQueue.add(loading)
            loadingEvent.value = Event(loading)
        } else {
            if (loadingQueue.isNotEmpty()) loadingQueue.removeAt(loadingQueue.size - 1)
            if (loadingQueue.isEmpty()) loadingEvent.value = Event(loading)
        }
    }

    fun postShowError() {
        showError.value = Event(Unit)
    }


}