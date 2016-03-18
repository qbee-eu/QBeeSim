/**
* @file		srand.h
* @author	FU Xiang gtaifu@gmail.com
* @date		2016-03-15
* @brief    Header file for windows implementation of srand function
*/

#ifdef _MSC_VER


#ifndef _SRAND_H_
#define _SRAND_H_

#define RAND48_SEED_0   (0x330e)
#define RAND48_SEED_1 (0xabcd)
#define RAND48_SEED_2 (0x1234)
#define RAND48_MULT_0 (0xe66d)
#define RAND48_MULT_1 (0xdeec)
#define RAND48_MULT_2 (0x0005)
#define RAND48_ADD (0x000b)


double drand48();
void srand48(long seed);

#endif // !_SRAND_H_

#endif // !_MSC_VER
