/*****************************************************************************
 * Copyright (C) 2018 by Zach Farmer
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for
 * any misuse of this material.
 *
*****************************************************************************/
/**
 * @file main.c
 * @brief User-level calls to custom written syscall for problem 3
 *
 * This is a short sample program to call and demonstrate the system call 
 * implemented in problem 3. It also times the system call.
 *
 * @author Zach Farmer
 * @date February 3 2018
 * @version 1.0
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 256

int main()
{
    //create input (ptr1) and output (ptr2) arrays
    srand(time(0));
    int32_t *ptr1 = (int32_t *) malloc(SIZE * sizeof (int32_t));
    int32_t *ptr2 = (int32_t *) malloc(SIZE * sizeof (int32_t));

    //fill input array (ptr1) with random numbers smaller than 1000
    int32_t i;
    for(i=0;i<SIZE;i++)
    {
        *(ptr1+i) = (rand()%1000);
    }
    //clock the system call
    clock_t start = clock(), diff;
    syscall(333, ptr1, ptr2, SIZE);
    diff = clock() - start;

    printf("Presort\tPostsort\n");

    for(i=0;i<SIZE;i++)
    {
        printf("%d\t%d\n",*(ptr1+i),*(ptr2+i));
    }

    //print timing of system call
    int msec = diff * 1000000 / CLOCKS_PER_SEC;
    printf("Time taken %d seconds %d milliseconds", msec/1000000, msec%1000000);

    return 0;
}
