/*
* Licensed under the MIT License (MIT)
*
* Copyright (c) 2016 AudioScience Inc.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
* the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
* notification_acmp_imp.h
*
* ACMP Notification implementation class
*/

#pragma once

#include "avdecc_lib_os.h"
#include <stdint.h>
#include "notification_acmp.h"

namespace avdecc_lib
{
class notification_acmp_imp : public virtual notification_acmp
{
public:
    notification_acmp_imp();

    virtual ~notification_acmp_imp();

private:
    enum notification_events
    {
        NOTIFICATION_EVENT,
        KILL_EVENT
    };

    LPTHREAD_START_ROUTINE thread;
    HANDLE h_thread;
    DWORD thread_id;
    HANDLE poll_events[2];

    ///
    /// Create and initialize notification thread, event, and semaphore.
    ///
    int notification_thread_init();

    ///
    /// Start of the notification thread used for generating notification messages.
    ///
    static DWORD WINAPI proc_notification_thread(LPVOID lpParam);

    ///
    /// A member function called to start the notification thread processing.
    ///
    int proc_notification_thread_callback();

    ///
    /// Release sempahore so that notification callback function is called.
    ///
    void post_acmp_notification_event();
};

extern notification_acmp_imp * notification_acmp_imp_ref;
}
