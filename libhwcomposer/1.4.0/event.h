#ifndef HWC_EVENT_H_
#define HWC_EVENT_H_

#include <utils/threads.h>
#include "worker.h"

using namespace android;

// ---------------------------------------------------------------------------

class VSyncThread : public HWCThread
{
public:
    VSyncThread(int dpy);
    virtual ~VSyncThread();

    // initialize() is used to check if hw vsync can be used
    void initialize(bool force_sw_vsync, nsecs_t refresh);

    // setEnabled() is used to notify if needing to listen vsync signal
    void setEnabled(bool enabled);

    // setLoopAgain() is used to force vsync thread loop again
    void setLoopAgain();

    // setProperty() is used for debug purpose
    void setProperty();

private:
    virtual void onFirstRef() { }
    virtual bool threadLoop();

    mutable Mutex m_lock;
    Condition m_condition;

    // m_disp_id is used to identify which display
    int m_disp_id;

    bool m_enabled;
    nsecs_t m_refresh;

    bool m_loop;

    bool m_fake_vsync;
    mutable nsecs_t m_next_fake_vsync;

    long m_max_period_io;
    long m_max_period_req;
};

class UEventThread : public HWCThread
{
public:
    UEventThread();
    virtual ~UEventThread();

    // initialize() is used to check if hw vsync can be used
    void initialize();

    // setProperty() is used for debug purpose
    void setProperty();

private:
    virtual void onFirstRef() { }
    virtual bool threadLoop();

    void handleUevents(const char *buff, int len);

    int m_socket;
    bool m_is_hotplug;

    enum DEBUG_HOTPLUG
    {
        FAKE_HDMI_NONE   = 0,
        FAKE_HDMI_PLUG   = 1,
        FAKE_HDMI_UNPLUG = 2,
    };

    int m_fake_hdmi;
    bool m_fake_hotplug;
};

#endif // HWC_EVENT_H_
