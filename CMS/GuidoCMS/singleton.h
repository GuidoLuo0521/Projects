#ifndef SINGLETON_H
#define SINGLETON_H
#include <QMutex>
#include <QMutexLocker>

#pragma once

template<class T>
class Singleton
{
public:
    Singleton():m_Instance(nullptr)  {   }
    virtual ~Singleton() {   }

    static T* SetInstance(T* p)
    {
        T* t = GetInstance();
        sm_Singleton->m_Instance = p;
        return t;
    }

    static T* GetInstance()
    {
        QMutexLocker locker(&sm_Mutex);
        if (sm_Singleton == nullptr)
        {
            sm_Singleton = new Singleton<T>();
        }

        return  sm_Singleton->m_Instance;
    }

    static void CleanUp()
    {
        sm_Singleton->cleanup_i();
    }
private:
    void cleanup_i()
    {
        delete this;
    }

private:
    T*			m_Instance;

    static Singleton<T>*	sm_Singleton;
    static QMutex sm_Mutex;
};

template<class T>
Singleton<T> * Singleton<T>::sm_Singleton = 0;

template<class T>
QMutex Singleton<T>::sm_Mutex;

#endif // SINGLETON_H
