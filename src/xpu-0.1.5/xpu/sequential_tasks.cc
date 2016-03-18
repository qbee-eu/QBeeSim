/**
* @file        sequential_tasks.cc
* @author	   Xiang Fu
* @date        04-03-2016
* @brief       sequential_tasks implementation
*
* This file is written by Xiang Fu by moving here the
* implementation code of the sequential_tasks class from the
* original sequential_tasks.h.
*/

#ifdef _MSC_VER

#include <xpu/sequential_tasks.h>

namespace xpu
{
    template <int N>
    sequential_tasks<N>::sequential_tasks(task_group ** tasks)
    {
        for (int i = 0; i<N; i++)
            m_tasks[i] = tasks[i];
        detect_shared();
    }

    template <int N>
    sequential_tasks<N>::~sequential_tasks()
    {
    }

    template <int N>
    void sequential_tasks<N>::run(range& r)
    {
        run();
    }

    template <int N>
    void sequential_tasks<N>::run(int i)
    {
        run();
    }

    template <int N>
    void sequential_tasks<N>::run()
    {
        for (int i = 0; i<N; i++)
            m_tasks[i]->run();
    }

    template <int N>
    void sequential_tasks<N>::detect_shared()
    {
        for (int i = 0; i<N; i++)
            m_tasks[i]->detect_shared();
    }

    template <int N>
    pointers sequential_tasks<N>::get_in_data()
    {
        pointers ptrs;
        #pragma loop(ivdep)
        for (int j = 0; j<N; j++)
            ptrs += m_tasks[j]->get_in_data();
        return ptrs;
    }

    template <int N>
    pointers sequential_tasks<N>::get_out_data()
    {
        pointers ptrs;
        #pragma loop(ivdep)
        for (int j = 0; j<N; j++)
            ptrs += m_tasks[j]->get_out_data();
        return ptrs;
    }

    template <int N>
    void sequential_tasks<N>::set_shared(pointer p, lockable * l)
    {
        #pragma loop(ivdep)
        for (int i = 0; i<N; i++)
            m_tasks[i]->set_shared(p, l);
    }

    template <int N>
    pointers sequential_tasks<N>::get_pointers()
    {
        pointers ptrs;
        #pragma loop(ivdep)
        for (int i = 0; i<N; i++)
            ptrs += m_tasks[i]->get_pointers();
        return ptrs;
    }

   /**
    * sequential tasks builders
    */
   task_group * sequential(task_group * t1, task_group * t2)
   {
	 task_group * tgs[2];
	 tgs[0] = t1;
	 tgs[1] = t2;
	 return new sequential_tasks<2>(tgs);
   }

   task_group * sequential(task_group * t1, task_group * t2, task_group * t3)
   {
	 task_group * tgs[3];
	 tgs[0] = t1;
	 tgs[1] = t2;
	 tgs[2] = t3;
	 return new sequential_tasks<3>(tgs);
   }

   task_group * sequential(task_group * t1, task_group * t2, task_group * t3, task_group * t4)
   {
	 task_group * tgs[4];
	 tgs[0] = t1;
	 tgs[1] = t2;
	 tgs[2] = t3;
	 tgs[3] = t4;
	 return new sequential_tasks<4>(tgs);
   }

   task_group * sequential(task_group * t1, task_group * t2, task_group * t3, task_group * t4, task_group * t5)
   {
	 task_group * tgs[5];
	 tgs[0] = t1;
	 tgs[1] = t2;
	 tgs[2] = t3;
	 tgs[3] = t4;
	 tgs[4] = t5;
	 return new sequential_tasks<5>(tgs);
   }

   task_group * sequential(task_group * t1, task_group * t2, task_group * t3, task_group * t4, task_group * t5, task_group * t6)
   {
	 task_group * tgs[6];
	 tgs[0] = t1;
	 tgs[1] = t2;
	 tgs[2] = t3;
	 tgs[3] = t4;
	 tgs[4] = t5;
	 tgs[5] = t6;
	 return new sequential_tasks<6>(tgs);
   }

   task_group * sequential(task_group * t1, task_group * t2, task_group * t3, task_group * t4, task_group * t5, task_group * t6, task_group * t7)
   {
	 task_group * tgs[7];
	 tgs[0] = t1;
	 tgs[1] = t2;
	 tgs[2] = t3;
	 tgs[3] = t4;
	 tgs[4] = t5;
	 tgs[5] = t6;
	 tgs[6] = t7;
	 return new sequential_tasks<7>(tgs);
   }

   task_group * sequential(task_group * t1, task_group * t2, task_group * t3, task_group * t4, task_group * t5, task_group * t6, task_group * t7, task_group * t8)
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
	 return new sequential_tasks<8>(tgs);
   }

   task_group * sequential(task_group * t1, task_group * t2, task_group * t3, task_group * t4, task_group * t5, task_group * t6, task_group * t7, task_group * t8, task_group * t9)
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
	 return new sequential_tasks<9>(tgs);
   }

   task_group * sequential(task_group * t1, task_group * t2, task_group * t3, task_group * t4, task_group * t5, task_group * t6, task_group * t7, task_group * t8, task_group * t9, task_group * t10)
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
	 return new sequential_tasks<10>(tgs);
   }




}
#endif // _MSC_VER
