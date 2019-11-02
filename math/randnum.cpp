#include "randnum.h"

long int LongRand(void)
{
    long int new_rand=rand();
    new_rand <<= 16;
    new_rand += rand();
    return new_rand;
}

bool UequRand(int floor, int upper, int amount, int* arr)
{
    if (floor > upper)
        return false;

    int range = upper - floor + 1;
    int* index = new int[range]();
    for (int i = 0; i < range; i++) {
        index[i] = floor + i;
    }
    for (int i = 0; i < amount; i++) {
        int r = rand() % (range-i) + i;
        arr[i] = index[r];
        index[r] = index[i];
    }
    delete[] index;

    return true;
}
