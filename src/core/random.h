/**
 *
 *
 *
 */

#ifndef QX_RANDOM_H
#define QX_RANDOM_H

#include <xpu/timer.h>

#include <random>

#define __limit__ 0.99999999999999f

namespace qx
{

   /**
    * \brief random number generator
    */
   class uniform_random_number_generator
   {
      public:

	 /**
	  * \brief ctor
	  */
	 uniform_random_number_generator(double min=0.0f, double max=1.0f) : min(min), max(max), distribution(min,max), generator(xpu::timer().current()*rd())
	 {
	 }

	 /**
	  * \brief generate random number
	  */
	 double next()
	 {
	    return distribution(generator);
	 }

      private:

         double  min;
	 double  max;

	 std::random_device                     rd;
	 std::default_random_engine             generator;
	 std::uniform_real_distribution<double> distribution;
   };


   /**
    * \brief random number generator
    */
   class normal_random_number_generator
   {
      public:

	 /**
	  * \brief ctor
	  */
	 normal_random_number_generator(double mean=0.0f, double deviation=1.0f) : mean(mean), deviation(deviation), generator(xpu::timer().current()*rd()), distribution(mean,deviation)
	 {
	 }

	 /**
	  * \brief generate random number
	  */
	 double next()
	 {
	    return distribution(generator);
	 }



      private:

         double  mean;
	 double  deviation;

	 std::random_device               rd;
	 std::mt19937                     generator;
	 std::normal_distribution<double> distribution;
   };

}

#endif // QX_RANDOM_H

