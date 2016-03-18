/**
 * @file mutex.h
 * @version 0.1
 * @author Nader KHAMMASSI
 * @date 08/02/2010
 * @description mutex encapsulation
 *
 * @copyright
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
 *
 */




#ifndef __XPU_MUTEX_79424B4E0A_H__
#define __XPU_MUTEX_79424B4E0A_H__

#include <xpu/lockable.h>

namespace xpu
{
   namespace core
   {
	 namespace os
	 {

	    class mutex : public lockable
	    {
		private:
		    pthread_mutex_t 	    m_mutex;
		    pthread_t 		    m_owner;
		    pthread_mutexattr_t  m_attr;

		public:

#ifndef _MSC_VER
            inline mutex(void) :m_owner(0)
#else
            inline mutex(void)
#endif // !_MSC_VER
            {
#ifdef _MSC_VER
                m_owner.p = NULL;
                m_owner.x = 0;
#endif // _MSC_VER
                pthread_mutexattr_init(&m_attr);
                pthread_mutex_init(&m_mutex, &m_attr);
            }

		    inline ~mutex(void)
            {
                pthread_mutex_lock(&m_mutex);
                pthread_mutex_unlock(&m_mutex);
                pthread_mutex_destroy(&m_mutex);
            };

		    inline void lock()
            {
                pthread_t id = pthread_self();
                try {
                    if (pthread_equal(id, m_owner))
                        throw " thread cannot lock same mutex twice !";
                    pthread_mutex_lock(&m_mutex);
                    m_owner = id;
                }
                catch (char const * e)
                {
                    //cerr << " (x) " <<__FILE__ << ":" << __LINE__ << ":" << __func__ << ": fatal exception : " << e << endl;
                    //throw e;
                }
            };
		    inline void unlock()
            {
                pthread_t id = pthread_self();
                try {
                    if (!pthread_equal(id, m_owner))
                        throw "only thread witch locked the mutex can release it !";
#ifndef _MSC_VER
                    m_owner = 0;
#else
                    m_owner.p = NULL;
                    m_owner.x = 0;
#endif // !_MSC_VER


                    pthread_mutex_unlock(&m_mutex);
                }
                catch (char const * e)
                {
                    // cerr << " (x) " << __FILE__ << ":" << __LINE__ << ":" << __func__ << ": fatal exception : " << e << endl;
                }
            };
	    };
	 } // namespace os
   } // namespace core
} // namespace xpu

#endif // __XPU_MUTEX_79424B4E0A_H__

