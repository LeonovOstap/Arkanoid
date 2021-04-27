#pragma once
#include <functional>
#include <iostream>
#include <ostream>
#include <thread>
#include <windows.h>


class DTimer {
public:

    static DTimer* createTimer();

    DTimer() {};
    ~DTimer() {};
    template<typename T>
    static void __stdcall timer_fired(PTP_CALLBACK_INSTANCE, PVOID context, PTP_TIMER timer)
    {
        CloseThreadpoolTimer(timer);
        std::unique_ptr<T> callable(reinterpret_cast<T*>(context));
        (*callable)();
    }

    template<typename T>
    void start(T callback, uint32_t interval, bool immediately = true, bool once = false)
    {
        auto state = std::make_unique<T>(std::move(callback));
        auto timer = CreateThreadpoolTimer(timer_fired<T>, state.get(), nullptr);
        if (!timer)
        {
            throw std::runtime_error("Timer");
        }

        ULARGE_INTEGER due;
        due.QuadPart = static_cast<ULONGLONG>(-(interval * 10000LL));

        FILETIME ft;
        ft.dwHighDateTime = due.HighPart;
        ft.dwLowDateTime = due.LowPart;

        SetThreadpoolTimer(timer, &ft, 0 /*msPeriod*/, 0 /*msWindowLength*/);
        state.release();
    }
    };
    


