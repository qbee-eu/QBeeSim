/**
 * @file		linalg.h
 * @author	Nader KHAMMASSI - nader.khammassi@gmail.com 
 * @date		02-10-15
 * @brief		linear algebra utils
 */

#ifndef QX_LINALG_H
#define QX_LINALG_H


#ifndef __BUILTIN_LINALG__
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#endif 

#include <core/matrix.h>

#include <iostream>
#include <cstdint>
#include <vector>
#include <bitset>

#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif // !_MSC_VER

#define println(x) std::cout << x << std::endl
#define print(x) std::cout << x 

#define MAX_QB_N 64

#ifndef __BUILTIN_LINALG__ 
using namespace boost::numeric;
#endif

#ifdef _MSC_VER
typedef std::complex<double>      complex_t;
#endif

namespace qx
{
   namespace linalg
   { 
#ifndef _MSC_VER
     typedef std::complex<double>      complex_t;
#endif // _MSC_VER
#ifndef __BUILTIN_LINALG__
	 typedef ublas::vector<complex_t>  cvector_t;
	 typedef ublas::matrix<complex_t>  cmatrix_t;
	 typedef ublas::identity_matrix<complex_t> cidentity_t;
#else
	 typedef std::vector<complex_t>  cvector_t;
	 typedef qx::linalg::matrix<complex_t>  cmatrix_t;
	 typedef qx::linalg::identity_matrix<complex_t> cidentity_t;
#endif // __BUILTIN_LINALG__

	 typedef std::vector<std::pair<uint32_t,uint32_t> > perm_t;

	 
	 /**
	  * \brief tensor product of vectors
	  */
     cvector_t tensor(cvector_t v1, cvector_t v2);

	 /**
	  * \brief tensor product of matrices
	  */
     cmatrix_t tensor(cmatrix_t m1, cmatrix_t m2);

	 /**
	  * \brief tensor product of matrices (result in m)
	  */
     uint32_t tensor(cmatrix_t& m1, cmatrix_t& m2, cmatrix_t& m);

	 /**
	  * \brief nth tensor
	  */
	  /*
	 cmatrix_t tensor(cmatrix_t m, uint32_t n);
	 */

	 /**
	  * \brief matrix vector product
	  */
     cvector_t mxv(cmatrix_t m, cvector_t v);

	 /**
	  * \brief matrix matrix product
	  */
     cmatrix_t mxm(cmatrix_t m1, cmatrix_t m2);

	 /**
	  * \brief verify if the matrices m1 and m2 are equals
	  */
     bool equals(cmatrix_t m1, cmatrix_t m2, double epsilon = 10e-14);

     inline uint32_t pow2(uint32_t x)
     {
         return (1 << x);
     }
      
	 /**
	  * inc
	  */
     std::bitset<MAX_QB_N> inc(std::bitset<MAX_QB_N> in);


      /**
	  * perms
	  */
	 // std::vector<std::pair<uint32_t,uint32_t> > 
     perm_t perms(uint32_t n, uint32_t c, uint32_t t);
     void perms(uint32_t n, uint32_t c, uint32_t t, cvector_t& amp);
     perm_t perms(uint32_t n, uint32_t c1, uint32_t c2, uint32_t t);

	 /**
	  * dump matrix
	  */
     void dump_matrix(cmatrix_t& m, bool complex_format = false);

   }
}


#ifndef _MSC_VER
#include "linalg.cc"   // ------ !!!!!!!!!!! -----
#endif


#endif // QX_LINALG_H

