#ifndef RANDNUM_H
#define RANDNUM_H
#define BRAND_MAX (RAND_MAX*0x10000+RAND_MAX)
#include <cstdlib>

long int LongRand(void);
bool UequRand(int floor, int upper, int amount, int* arr);	//在指定范围内产生若干个不相等的随机数

#endif // RANDNUM_H
