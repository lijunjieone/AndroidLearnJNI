package com.d.ui.utils;


import androidx.lifecycle.Lifecycle;
import androidx.lifecycle.LifecycleObserver;
import androidx.lifecycle.OnLifecycleEvent;

import java.util.Observable;

/**
 * Created by su on 2019/4/9.
 */
public class AppLifecycleListener extends Observable implements LifecycleObserver {

    private static AppLifecycleListener sAppLifecycleListener = new AppLifecycleListener();

    public boolean isForeground;

    @OnLifecycleEvent(Lifecycle.Event.ON_START)
    public void onMoveToForeground() {
        isForeground = true;
        sAppLifecycleListener.notifyObservers(isForeground);
    }

    @OnLifecycleEvent(Lifecycle.Event.ON_STOP)
    public void onMoveToBackground() {
        isForeground = false;
        sAppLifecycleListener.notifyObservers(isForeground);
    }

    @Override
    public boolean hasChanged() {
        return true;
    }

    public static AppLifecycleListener getInstance() {
        return sAppLifecycleListener;
    }
}
