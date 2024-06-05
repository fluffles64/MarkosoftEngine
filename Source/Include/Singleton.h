#pragma once
#include <string>

/// <summary>
/// Singleton class
/// Base class to create singletons controlling construction and destruction of singleton
/// </summary>

template <class T>
class Singleton
{
public:
    // Constructor
    Singleton(void) {}

    // Destructor
    ~Singleton(void) {}

    // Singleton creation
    inline void static CreateSingleton(void)
    {
        // Create singleton. Assert if singleton already exists
        if (!mSingleton) {
            mSingleton = new T();
        }
        else {
            ShowAssertForSingleton("Singleton already created. FIX IMMEDIATELY");
        }
    }

    // Singleton destruction
    inline void static DestroySingleton(void)
    {
        // Destroy singleton. Assert if singleton is already destroyed or never created
        if (mSingleton) {
            // Inline safe delete
            delete mSingleton;
            mSingleton = NULL;
        }
        else {
            ShowAssertForSingleton("Singleton already destroyed or never created. FIX IMMEDIATELY");
        }
    }

    //Returns a reference to the singleton
    inline static T &GetInstance(void)
    {
        return *mSingleton;
    }

    // Returns a pointer to the singleton
    inline static T *GetInstancePtr(void)
    {
        return mSingleton;
    }

private:
    //Shows and assert for an error found in assert management
    //This function should be reimplemented for every platform with the desired assert behaviour
    inline static void ShowAssertForSingleton(const std::string &windowMessage)
    {
        printf("ERROR!");
        //MessageBox(NULL, windowMessage.c_str(), "Assertion failed in Singleton", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
    }

    // Singleton instance
    static T *mSingleton;
};

template <class T>
T *Singleton<T>::mSingleton = NULL;