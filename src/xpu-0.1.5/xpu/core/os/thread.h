/**
 * @file     thread.h
 * @version  0.2
 * @author   Nader KHAMMASSI
 * @contact  nader.khammassi@gmail.com
 * @date     05/02/2010
 *
 * @copyright
 *
 *
 * XPU - C++ Parallel  Programming Library for Multicore Architectures
 *
 * Copyright (C) 2014 Nader Khammassi, All Rights Reserved.
 *
 * This file is part of XPU and has been downloaded from
 * http://www.xpu-project.net/.
 *
 * XPU is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * XPU is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#ifndef __XPU_THREAD_79424B4E0A_H__
#define __XPU_THREAD_79424B4E0A_H__



#ifdef _MSC_VER
//#pragma message (__FILE__ ": include xpu/pthread.h")
#include <pthread/include/pthread.h>
#else
#include <pthread.h>
#endif

// internal components
//#pragma message (__FILE__ ": include xpu/core/os/barrier.h")
#include <xpu/core/os/barrier.h>
//#pragma message (__FILE__ ": include xpu/core/os/cpuset.h")
#include <xpu/core/os/cpuset.h>

// public components
//#pragma message (__FILE__ ": include xpu/exception.h")
#include <xpu/exception.h>
//#pragma message (__FILE__ ": include xpu/task_group.h")
#include <xpu/task_group.h>

#ifdef _MSC_VER
#pragma warning( disable : 4290 )
#endif // _MSC_VER



namespace xpu
{
   namespace core
   {
	 namespace os
	 {
	    class cpuset;
	    /**
		* @class thread
		* @brief thread support implementation for c++98 and c++0x
		*/
	    class thread
	    {
		  protected:

			typedef pthread_t __xpu_handle;
			typedef void *  (*__xpu_task)(void *);
			//typedef int task;

		  protected:

			// =========== thread attr ===========

			pthread_attr_t    m_attr;
			pthread_t         m_id;
			cpuset            m_cpuset;

			bool              m_running;

			void *            m_args;
			void *            m_exit_status;
			int               m_core;

			// ========= join th info ============

			pthread_t         m_join_id;
			void **           m_join_result;

			// ===== Synchronization tools =======

			barrier *         m_barrier;
			//vector<mutex *> __mutexes;


		  protected:

			/**
			 * execute task on witch thread is spawn.
			 * @param args arguments
			 * @return offset of task result
			 */
			static inline void * run(void * arg)
            {
                //cpu_set_t cpuset;
                //CPU_ZERO(&cpuset);
                //CPU_SET(j&cpuset);

                thread * t = (thread*)arg;
                t->m_cpuset.setup();
                t->m_task->run();
                return NULL;
            };

			task_group *             m_task;

		  public:

			// void * (*_function)(void *);

			/**
			 * constructor
			 */
              explicit inline thread(task_group *cb) :
#ifndef _MSC_VER
                  m_id(0),
                  m_join_id(0),
                  m_join_result(0),
#endif // !_MSC_VER
                  m_running(false),
                  m_core(-1), // not defined, let the kernel choose it for us... (default)
                  //m_barrier(0),
                  m_task(cb)
              {
#ifdef _MSC_VER
                  m_id.p = NULL;
                  m_id.x = 0;
                  m_join_id.p = NULL;
                  m_join_id.x = 0;
                  m_join_result = NULL;
#endif // _MSC_VER
                  pthread_attr_init(&m_attr);
                  //CPU_ZERO(&m_cpuset);
                  /*
                  for (int i=0; i<__xpu_processor__.count(); i++)
                  {
                  CPU_SET(i, &m_cpuset);
                  }
                  */
                  m_cpuset.allow_all();
              }

			/**
			 * destructor
			 */
            inline ~thread() {return;};
			inline task_group *  get_task() { return m_task; }
			inline void set_task(task_group * cb) { m_task = cb; };

			inline pthread_t  id()
            {

                if (m_running)
                    return pthread_self();
                else
#ifdef _MSC_VER   // ---------- !!!!!!!! ---------
                {
                    pthread_t null_thread;
                    null_thread.p = NULL;
                    null_thread.x = 0;
                    return null_thread;
                }
#else
		return 0;
#endif
            };

			inline pthread_attr_t get_attributes() { return m_attr; };

			inline void * get_exit_status() { return m_exit_status; };

			inline void   set_exit_status(void * status) { m_exit_status = status; };

			inline barrier * get_barrier() { return m_barrier; };

			inline void set_barrier(barrier * br) { m_barrier = br; };

			inline void remove_barrier() { m_barrier = NULL;};

			inline pthread_t  get_join_id() { return m_id; };

			inline void **    get_join_result() { return m_join_result; };

			/*
			   inline
			   void       add_mutex(mutex * m);

			   inline
			   vector<mutex *> * get_mutexes();
			   */

			/**
			 * force thread to run on core n° <cpu>
			 * @cpu core index
			 */
			inline void set_core(int core)
            {
                m_core = core;
                m_cpuset.only(core);
            };

			inline void set_cpuset(cpuset cs)
			   {
				 m_cpuset = cs;
			   }


			inline static int get_core()
			   {
				 //return sched_getcpu();
				 return 0;
			   }

			/**
			 * create thread on run function on core n° <cpu>
			 */
			inline void start() throw (xpu::exception)
            {
                if (pthread_create(&m_id, &m_attr, reinterpret_cast<__xpu_task>(&run), (void*)this) != 0)
                    throw (xpu::exception("thread::start() : pthread_create() failed ", true));

            };

			/*
			   inline
			   void stop()
			   {
			   pthread_cancel(m_id);
			   }
			   */

			/**
			 * join thread identified by <id>
			 * @id joinable thread id
			 * @join_result join task result
			 */
			inline void join(pthread_t id, void ** join_result=NULL)
            {
                m_join_id = id;
                m_join_result = join_result;
            };

			inline void join() throw (xpu::exception)
            {
                if (pthread_join(m_id, NULL) != 0)
                    throw (xpu::exception("thread::join() : pthread_join() failed ", true));
            };

#if defined(__linux) || defined(__osf__) || defined(__sun)
			inline int try_join(long timout)
            {
                struct timespec ts;
                int s;
                if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
                {  /* Handle error */
                }

                //ts.tv_sec += 5;
                ts.tv_nsec += timeout;
                s = pthread_timedjoin_np(m_id, NULL, &ts);
                return s;
            };
#endif


			// =========== static utils functions ===============

			// Applyed to calling thread ...

			//static void wait(barrier * barrier);

			// wait for all no detached threads then exit..
			static inline void wait_for_all_threads()
            {
                pthread_exit(NULL);
            };


			static inline pthread_t self() { return pthread_self(); }

			// join thread t
			static inline void join(thread *t) throw (xpu::exception)
            {
                if (pthread_join(t->m_id, t->m_join_result) != 0)
                    throw (xpu::exception("thread::join() : pthread_join() failed ", true));
            };

			// TO DO: add accessors to attributes: joinable, detached ...
	    };

	 } // namespace os
   } // namespace core
} // namespace xpu

#endif // __XPU_THREAD_79424B4E0A_H__
