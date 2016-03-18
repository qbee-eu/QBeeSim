/**
* @file         parallel_tasks.cc
* @author	    Xiang Fu
* @date         03-03-2016
* @brief        parallel_tasks implementation
*
* This file is written by Xiang Fu by moving here the
* implementation code of the parallel_tasks class from the
* original parallel_tasks.h.
*/
#ifdef _MSC_VER

#include <xpu/parallel_tasks.h>
#include <xpu.h>

template <int N>
xpu::parallel_tasks<N>::parallel_tasks(task_group ** tasks)
{
    for (int i = 0; i<N; i++)
    {
        m_tasks[i] = tasks[i];
        m_threads[i] = new thread((task*)tasks[i]);
        m_works[i] = new basic_work((task*)tasks[i]);
    }
#ifndef XPU_DISABLE_AUTOMATIC_SHARED_MEMORY_DETECTION
    detect_shared();
#endif // XPU_DISABLE_AUTOMATIC_SHARED_MEMORY_DETECTION
}

template <int N>
xpu::parallel_tasks<N>::~parallel_tasks()
{
    for (int i = 0; i<N; i++)
        delete  m_threads[i];
}

template <int N>
void xpu::parallel_tasks<N>::run(range& r)
{
    run();
}

template <int N>
void xpu::parallel_tasks<N>::run(int i)
{
    run();
}

template <int N>
void xpu::parallel_tasks<N>::run()
{
    /*
    for (int i=0; i<N; i++)
    m_threads[i]->start();
    for (int i=0; i<N; i++)
    m_threads[i]->join();
    */
    for (int i = 0; i<N; i++)
        core::dynamic_work_queue.push(m_works[i]);
    for (int i = 0; i<N; i++)
        m_works[i]->wait();

}

template <int N>
void xpu::parallel_tasks<N>::detect_shared()
{
    for (int i = 0; i<N - 1; i++)
    {
        // check in data
        //__debug(" parallel_tasks: checking for shared data...");
        pointers in_ptrs1 = m_tasks[i]->get_in_data();
        for (int j = i + 1; j<N; j++)
        {
            pointers ptrs2 = m_tasks[j]->get_out_data();
            pointers shared = in_ptrs1 * ptrs2;
            if (!shared.empty())
            {
                for (pointers::iterator it = shared.begin(); it != shared.end(); it++)
                {
                    //__debug(" parallel_tasks: shared data detected: " << (void*)(*it));
                    std::cout << "[+] xpu::parallel_tasks : shared data detected: " << (void*)(*it) << std::endl;
                    lockable * l = xpu::core::lockable_factory::instance()->getlockable(*it);
                    //__debug(" parallel_tasks: automatic resource protection: pointer=" << (void*)(*it) << " , lockable=" << (void*)l);
                    std::cout << "[+] xpu::parallel_tasks: automatic memory protection: pointer=" << (void*)(*it) << " , lockable=" << (void*)l << std::endl;
                    m_tasks[i]->set_shared(*it, l);
                    m_tasks[j]->set_shared(*it, l);
                }
            }
        }
        pointers out_ptrs1 = m_tasks[i]->get_out_data();
        for (int j = i + 1; j<N; j++)
        {
            pointers ptrs2 = m_tasks[j]->get_in_data();
            ptrs2 += m_tasks[j]->get_out_data();
            pointers shared = out_ptrs1 * ptrs2;
            if (!shared.empty())
            {
                for (pointers::iterator it = shared.begin(); it != shared.end(); it++)
                {
                    __debug(" parallel_tasks: shared data detected: " << (void*)(*it));
                    lockable * l = xpu::core::lockable_factory::instance()->getlockable(*it);
                    __debug(" parallel_tasks: automatic resource protection: pointer=" << (void*)(*it) << " , lockable=" << (void*)l);
                    m_tasks[i]->set_shared(*it, l);
                    m_tasks[j]->set_shared(*it, l);
                }
            }
        }

    }
}

template <int N>
pointers xpu::parallel_tasks<N>::get_in_data()
{
    pointers ptrs;
    #pragma loop(ivdep)
    for (int j = 0; j<N; j++)
        ptrs += m_tasks[j]->get_in_data();
    return ptrs;
}

template <int N>
pointers xpu::parallel_tasks<N>::get_out_data()
{
    pointers ptrs;
    #pragma loop(ivdep)
    for (int j = 0; j<N; j++)
        ptrs += m_tasks[j]->get_out_data();
    return ptrs;
}

template <int N>
void xpu::parallel_tasks<N>::set_shared(pointer p, lockable * l)
{
    #pragma loop(ivdep)
    for (int i = 0; i<N; i++)
        m_tasks[i]->set_shared(p, l);
}

template <int N>
pointers xpu::parallel_tasks<N>::get_pointers()
{
    pointers ptrs;
    #pragma loop(ivdep)
    for (int i = 0; i<N; i++)
        ptrs += m_tasks[i]->get_pointers();
    return ptrs;
}

 /**
  * parallel tasks builders
  */
task_group * xpu::parallel(task_group * t1, task_group * t2)
{
    task_group * tgs[2];
    tgs[0] = t1;
    tgs[1] = t2;
    return new parallel_tasks<2>(tgs);
}

task_group * xpu::parallel(task_group * t1, task_group * t2, task_group * t3)
{
    task_group * tgs[3];
    tgs[0] = t1;
    tgs[1] = t2;
    tgs[2] = t3;
    return new parallel_tasks<3>(tgs);
}

task_group * xpu::parallel(task_group * t1, task_group * t2, task_group * t3, task_group * t4)
{
    task_group * tgs[4];
    tgs[0] = t1;
    tgs[1] = t2;
    tgs[2] = t3;
    tgs[3] = t4;
    return new parallel_tasks<4>(tgs);
}

task_group * xpu::parallel(task_group * t1, task_group * t2, task_group * t3, task_group * t4, task_group * t5)
{
    task_group * tgs[5];
    tgs[0] = t1;
    tgs[1] = t2;
    tgs[2] = t3;
    tgs[3] = t4;
    tgs[4] = t5;
    return new parallel_tasks<5>(tgs);
}

task_group * xpu::parallel(task_group * t1, task_group * t2, task_group * t3, task_group * t4, task_group * t5, task_group * t6)
{
    task_group * tgs[6];
    tgs[0] = t1;
    tgs[1] = t2;
    tgs[2] = t3;
    tgs[3] = t4;
    tgs[4] = t5;
    tgs[5] = t6;
    return new parallel_tasks<6>(tgs);
}

task_group * xpu::parallel(task_group * t1, task_group * t2, task_group * t3, task_group * t4, task_group * t5, task_group * t6, task_group * t7)
{
    task_group * tgs[7];
    tgs[0] = t1;
    tgs[1] = t2;
    tgs[2] = t3;
    tgs[3] = t4;
    tgs[4] = t5;
    tgs[5] = t6;
    tgs[6] = t7;
    return new parallel_tasks<7>(tgs);
}

task_group * xpu::parallel(task_group * t1, task_group * t2, task_group * t3, task_group * t4, task_group * t5, task_group * t6, task_group * t7, task_group * t8)
{
    task_group * tgs[8];
    tgs[0] = t1;
    tgs[1] = t2;
    tgs[2] = t3;
    tgs[3] = t4;
    tgs[4] = t5;
    tgs[5] = t6;
    tgs[6] = t7;
    tgs[7] = t8;
    return new parallel_tasks<8>(tgs);
}

task_group * xpu::parallel(task_group * t1, task_group * t2, task_group * t3, task_group * t4, task_group * t5, task_group * t6, task_group * t7, task_group * t8, task_group * t9)
{
    task_group * tgs[9];
    tgs[0] = t1;
    tgs[1] = t2;
    tgs[2] = t3;
    tgs[3] = t4;
    tgs[4] = t5;
    tgs[5] = t6;
    tgs[6] = t7;
    tgs[7] = t8;
    tgs[8] = t9;
    return new parallel_tasks<9>(tgs);
}

task_group * xpu::parallel(task_group * t1, task_group * t2, task_group * t3, task_group * t4, task_group * t5, task_group * t6, task_group * t7, task_group * t8, task_group * t9, task_group * t10)
{
    task_group * tgs[10];
    tgs[0] = t1;
    tgs[1] = t2;
    tgs[2] = t3;
    tgs[3] = t4;
    tgs[4] = t5;
    tgs[5] = t6;
    tgs[6] = t7;
    tgs[7] = t8;
    tgs[8] = t9;
    tgs[9] = t10;
    return new parallel_tasks<10>(tgs);
}

#endif // _MSC_VER
