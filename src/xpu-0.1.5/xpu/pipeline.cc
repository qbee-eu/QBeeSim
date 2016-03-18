/**
 * @file        pipeline.cc
 * @author	    Xiang Fu
 * @date        03-03-2016
 * @brief       pipeline implementation
 * 
 * This file is written by Xiang Fu by moving here the 
 * implementation code of the pipeline class from the 
 * original pipeline.h.
 */

#ifdef _MSC_VER

#include <xpu/pipeline.h>


pointers pipeline::get_out_data()
{
    pointers ptrs;
    ptrs += m_head.get_task()->get_out_data();
    for (unsigned int i = 0; i<m_stages.size(); i++)
        ptrs += m_stages[i].get_task()->get_out_data();
    ptrs += m_tail.get_task()->get_out_data();
    return ptrs;
}

pointers pipeline::get_in_data()
{
    pointers ptrs;
    ptrs += m_head.get_task()->get_in_data();
    for (unsigned int i = 0; i<m_stages.size(); i++)
        ptrs += m_stages[i].get_task()->get_in_data();
    ptrs += m_tail.get_task()->get_in_data();
    return ptrs;
}

void pipeline::set_shared(pointer p, lockable * l)
{
    for (unsigned int i = 0; i<m_stages.size(); i++)
        m_stages[i].get_task()->set_shared(p, l);
}

 /**
  * xpu::pipeline::pipeline implementation
  */

pipeline::pipeline(int length, task * stage1, task * stage2) : m_head(stage1, NULL, length),
m_tail(stage2, NULL, length)
{
    event * e = new xpu::event();
    m_events.push_back(e);
    m_head.set_event(e);
    m_tail.set_event(e);
}

pipeline::pipeline(int length, task * stage1, task * stage2, task * stage3) : m_head(stage1, NULL, length),
m_tail(stage3, NULL, length)
{
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_head.set_event(m_events.at(0));
    m_tail.set_event(m_events.at(1));
    m_stages.push_back(event_relay(stage2, m_events.at(0), m_events.at(1), length));
}

pipeline::pipeline(int length, task * stage1, task * stage2, task * stage3, task * stage4) : m_head(stage1, NULL, length),
m_tail(stage4, NULL, length)
{
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_head.set_event(m_events.at(0));
    m_tail.set_event(m_events.at(2));
    m_stages.push_back(event_relay(stage2, m_events.at(0), m_events.at(1), length));
    m_stages.push_back(event_relay(stage3, m_events.at(1), m_events.at(2), length));
}

pipeline::pipeline(int length, task * stage1, task * stage2, task * stage3, task * stage4, task * stage5) : m_head(stage1, NULL, length),
m_tail(stage5, NULL, length)
{
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_head.set_event(m_events.at(0));
    m_tail.set_event(m_events.at(3));
    m_stages.push_back(event_relay(stage2, m_events.at(0), m_events.at(1), length));
    m_stages.push_back(event_relay(stage3, m_events.at(1), m_events.at(2), length));
    m_stages.push_back(event_relay(stage4, m_events.at(2), m_events.at(3), length));
}

pipeline::pipeline(int length, task * stage1, task * stage2, task * stage3, task * stage4, task * stage5, task * stage6) : m_head(stage1, NULL, length),
m_tail(stage6, NULL, length)
{
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_head.set_event(m_events.at(0));
    m_tail.set_event(m_events.at(4));
    m_stages.push_back(event_relay(stage2, m_events.at(0), m_events.at(1), length));
    m_stages.push_back(event_relay(stage3, m_events.at(1), m_events.at(2), length));
    m_stages.push_back(event_relay(stage4, m_events.at(2), m_events.at(3), length));
    m_stages.push_back(event_relay(stage5, m_events.at(3), m_events.at(4), length));
}

pipeline::pipeline(int length, task * stage1, task * stage2, task * stage3, task * stage4, task * stage5, task * stage6, task * stage7) : m_head(stage1, NULL, length),
m_tail(stage7, NULL, length)
{
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_head.set_event(m_events.at(0));
    m_tail.set_event(m_events.at(5));
    m_stages.push_back(event_relay(stage2, m_events.at(0), m_events.at(1), length));
    m_stages.push_back(event_relay(stage3, m_events.at(1), m_events.at(2), length));
    m_stages.push_back(event_relay(stage4, m_events.at(2), m_events.at(3), length));
    m_stages.push_back(event_relay(stage5, m_events.at(3), m_events.at(4), length));
    m_stages.push_back(event_relay(stage6, m_events.at(4), m_events.at(5), length));
}

pipeline::pipeline(int length, task * stage1, task * stage2, task * stage3, task * stage4, task * stage5, task * stage6, task * stage7, task * stage8) : m_head(stage1, NULL, length),
m_tail(stage8, NULL, length)
{
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_head.set_event(m_events.at(0));
    m_tail.set_event(m_events.at(6));
    m_stages.push_back(event_relay(stage2, m_events.at(0), m_events.at(1), length));
    m_stages.push_back(event_relay(stage3, m_events.at(1), m_events.at(2), length));
    m_stages.push_back(event_relay(stage4, m_events.at(2), m_events.at(3), length));
    m_stages.push_back(event_relay(stage5, m_events.at(3), m_events.at(4), length));
    m_stages.push_back(event_relay(stage6, m_events.at(4), m_events.at(5), length));
    m_stages.push_back(event_relay(stage7, m_events.at(5), m_events.at(6), length));
}

pipeline::pipeline(int length, task * stage1, task * stage2, task * stage3, task * stage4, task * stage5, task * stage6, task * stage7, task * stage8, task * stage9) : m_head(stage1, NULL, length),
m_tail(stage9, NULL, length)
{
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_head.set_event(m_events.at(0));
    m_tail.set_event(m_events.at(7));
    m_stages.push_back(event_relay(stage2, m_events.at(0), m_events.at(1), length));
    m_stages.push_back(event_relay(stage3, m_events.at(1), m_events.at(2), length));
    m_stages.push_back(event_relay(stage4, m_events.at(2), m_events.at(3), length));
    m_stages.push_back(event_relay(stage5, m_events.at(3), m_events.at(4), length));
    m_stages.push_back(event_relay(stage6, m_events.at(4), m_events.at(5), length));
    m_stages.push_back(event_relay(stage7, m_events.at(5), m_events.at(6), length));
    m_stages.push_back(event_relay(stage8, m_events.at(6), m_events.at(7), length));
}

pipeline::pipeline(int length, task * stage1, task * stage2, task * stage3, task * stage4, task * stage5, task * stage6, task * stage7, task * stage8, task * stage9, task * stage10) : m_head(stage1, NULL, length),
m_tail(stage10, NULL, length)
{
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_head.set_event(m_events.at(0));
    m_tail.set_event(m_events.at(8));
    m_stages.push_back(event_relay(stage2, m_events.at(0), m_events.at(1), length));
    m_stages.push_back(event_relay(stage3, m_events.at(1), m_events.at(2), length));
    m_stages.push_back(event_relay(stage4, m_events.at(2), m_events.at(3), length));
    m_stages.push_back(event_relay(stage5, m_events.at(3), m_events.at(4), length));
    m_stages.push_back(event_relay(stage6, m_events.at(4), m_events.at(5), length));
    m_stages.push_back(event_relay(stage7, m_events.at(5), m_events.at(6), length));
    m_stages.push_back(event_relay(stage8, m_events.at(6), m_events.at(7), length));
    m_stages.push_back(event_relay(stage9, m_events.at(7), m_events.at(8), length));
}

pipeline::pipeline(int length, task * stage1, task * stage2, task * stage3, task * stage4, task * stage5, task * stage6, task * stage7, task * stage8, task * stage9, task * stage10, task * stage11) : m_head(stage1, NULL, length),
m_tail(stage11, NULL, length)
{
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_head.set_event(m_events.at(0));
    m_tail.set_event(m_events.at(9));
    m_stages.push_back(event_relay(stage2, m_events.at(0), m_events.at(1), length));
    m_stages.push_back(event_relay(stage3, m_events.at(1), m_events.at(2), length));
    m_stages.push_back(event_relay(stage4, m_events.at(2), m_events.at(3), length));
    m_stages.push_back(event_relay(stage5, m_events.at(3), m_events.at(4), length));
    m_stages.push_back(event_relay(stage6, m_events.at(4), m_events.at(5), length));
    m_stages.push_back(event_relay(stage7, m_events.at(5), m_events.at(6), length));
    m_stages.push_back(event_relay(stage8, m_events.at(6), m_events.at(7), length));
    m_stages.push_back(event_relay(stage9, m_events.at(7), m_events.at(8), length));
    m_stages.push_back(event_relay(stage10, m_events.at(8), m_events.at(9), length));
}

pipeline::pipeline(int length, task * stage1, task * stage2, task * stage3, task * stage4, task * stage5, task * stage6, task * stage7, task * stage8, task * stage9, task * stage10, task * stage11, task * stage12) : m_head(stage1, NULL, length),
m_tail(stage12, NULL, length)
{
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_head.set_event(m_events.at(0));
    m_tail.set_event(m_events.at(10));
    m_stages.push_back(event_relay(stage2, m_events.at(0), m_events.at(1), length));
    m_stages.push_back(event_relay(stage3, m_events.at(1), m_events.at(2), length));
    m_stages.push_back(event_relay(stage4, m_events.at(2), m_events.at(3), length));
    m_stages.push_back(event_relay(stage5, m_events.at(3), m_events.at(4), length));
    m_stages.push_back(event_relay(stage6, m_events.at(4), m_events.at(5), length));
    m_stages.push_back(event_relay(stage7, m_events.at(5), m_events.at(6), length));
    m_stages.push_back(event_relay(stage8, m_events.at(6), m_events.at(7), length));
    m_stages.push_back(event_relay(stage9, m_events.at(7), m_events.at(8), length));
    m_stages.push_back(event_relay(stage10, m_events.at(8), m_events.at(9), length));
    m_stages.push_back(event_relay(stage11, m_events.at(9), m_events.at(10), length));
}

pipeline::pipeline(int length, task * stage1, task * stage2, task * stage3, task * stage4, task * stage5, task * stage6, task * stage7, task * stage8, task * stage9, task * stage10, task * stage11, task * stage12, task * stage13) : m_head(stage1, NULL, length),
m_tail(stage13, NULL, length)
{
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_events.push_back(new xpu::event());
    m_head.set_event(m_events.at(0));
    m_tail.set_event(m_events.at(11));
    m_stages.push_back(event_relay(stage2, m_events.at(0), m_events.at(1), length));
    m_stages.push_back(event_relay(stage3, m_events.at(1), m_events.at(2), length));
    m_stages.push_back(event_relay(stage4, m_events.at(2), m_events.at(3), length));
    m_stages.push_back(event_relay(stage5, m_events.at(3), m_events.at(4), length));
    m_stages.push_back(event_relay(stage6, m_events.at(4), m_events.at(5), length));
    m_stages.push_back(event_relay(stage7, m_events.at(5), m_events.at(6), length));
    m_stages.push_back(event_relay(stage8, m_events.at(6), m_events.at(7), length));
    m_stages.push_back(event_relay(stage9, m_events.at(7), m_events.at(8), length));
    m_stages.push_back(event_relay(stage10, m_events.at(8), m_events.at(9), length));
    m_stages.push_back(event_relay(stage11, m_events.at(9), m_events.at(10), length));
    m_stages.push_back(event_relay(stage12, m_events.at(10), m_events.at(11), length));
}



void
pipeline::run(range& r)
{
    m_tail.start();
    for (unsigned int i = 0; i < m_stages.size(); i++)
    {
        m_stages[i].start();
    }
    m_head.start();
    m_head.join();
    m_tail.join();
}

void
pipeline::run(int i)
{
    m_tail.start();
    for (unsigned int i = 0; i < m_stages.size(); i++)
    {
        m_stages[i].start();
    }
    m_head.start();
    m_head.join();
    m_tail.join();
}

void
pipeline::run()
{
    m_tail.start();
    for (unsigned int i = 0; i < m_stages.size(); i++)
    {
        m_stages[i].start();
    }
    m_head.start();
    m_head.join();
    m_tail.join();
}

pipeline::~pipeline()
{
    for (unsigned int i = 0; i < m_events.size(); i++)
    {
        delete m_events[i];
    }
}

#endif // _MSC_VER