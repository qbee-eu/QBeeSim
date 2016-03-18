/**
 * @file    exception.h
 * @author  Nader KHAMMASSI
 * @contact nader.khammassi@gmail.com
 * @date    15/03/2010
 * @brief   xpu exception
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


#ifndef __XPU_EXCEPTION_H__
#define __XPU_EXCEPTION_H__

#include <string>            // for string
#include <cstring>           // for strerror
#include <exception>         // for exception 
#include <cerrno>            // for errno

namespace xpu
{
   class exception : public std::exception 
   {

	 public:
	   /**
	    *   construct a exception with a explanatory message.
	    *   
	    *   @param message         explanatory message
	    *   @param system_message  true if system message (from strerror(errno))
	    *                          should be postfixed to the user provided message
	    */
#ifndef _MSC_VER
         inline exception(const std::string &message, bool system_message = false) throw();
#else
         inline exception(const std::string &message, bool system_message = false) throw() : user_message(message)
         {
             if (system_message)
             {
                 user_message.append(": ");
                 char buff[256];
                 strerror_s(buff, 100, errno);
                 user_message.append(buff);
             }
         }
#endif // !_MSC_VER



	   /**
	    *   provided just to guarantee that no exceptions are thrown.
	    */
#ifndef _MSC_VER
         inline ~exception() throw();
#else
         inline ~exception() throw() {};
#endif // !_MSC_VER

	   /**
	    *   get the exception message
	    *   @return exception message
	    */
#ifndef _MSC_VER
         inline const char *what() const throw();
#else
         inline const char *what() const throw()
         {
             return user_message.c_str();
         };

#endif // !_MSC_VER

	 private:
	   
	   std::string user_message;  // exception message

   }; // class exception
#ifndef _MSC_VER
    #include "exception.cc"
#endif // !_MSC_VER

} // namespace xpu

#endif // __XPU_EXCEPTION_H__


