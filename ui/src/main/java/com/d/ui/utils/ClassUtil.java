package com.d.ui.utils;



import androidx.lifecycle.AndroidViewModel;

import com.d.ui.base.vm.NoViewModel;

import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;


public class ClassUtil {

    /**
     * 获取泛型ViewModel的class对象
     */
    public static <T> Class<T> getViewModel(Object obj) {
        Class<?> currentClass = obj.getClass();
        Class<T> tClass = getGenericClass(currentClass);
        if (tClass == null || tClass == AndroidViewModel.class || tClass == NoViewModel.class) {
            return null;
        }
        return tClass;
    }

    private static <T> Class<T> getGenericClass(Class<?> klass) {
        Type type = klass.getGenericSuperclass();
        if (!(type instanceof ParameterizedType)) return null;
        ParameterizedType parameterizedType = (ParameterizedType) type;
        Type[] types = parameterizedType.getActualTypeArguments();
        for (Type t : types) {
            Class<T> tClass = (Class<T>) t;
            if (AndroidViewModel.class.isAssignableFrom(tClass)) {
                return tClass;
            }
        }
        return null;
    }
}
