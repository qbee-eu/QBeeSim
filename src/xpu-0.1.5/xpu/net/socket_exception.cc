#ifdef _MSC_VER
#include <xpu/net/socket_exception.h>
#endif // _MSC_VER


/**
 * socket_exception implementation
 */

socket_exception::socket_exception(const std::string &message, 
                                   bool system_message)
                                   throw() : user_message(message) 
{
  if (system_message) 
  {
    user_message.append(": ");
//#ifdef _MSC_VER
    //user_message.append(strerror_s(errno));
//#else
    user_message.append(strerror(errno));
//#endif // _MSC_VER
  }
}


socket_exception::~socket_exception() throw() 
{
}

const char *socket_exception::what() const throw() 
{
  return user_message.c_str();
}

