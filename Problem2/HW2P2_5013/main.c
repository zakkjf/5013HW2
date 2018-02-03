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
 * @brief Track system calls and library calls with File IO
 *
 * This is a short sample program to provide system calls 
 * and library calls with File IO for tracking
 *
 * @author Zach Farmer
 * @date February 3 2018
 * @version 1.0
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FILEPATH "test.txt"
#define PERMISSIONS (S_IRUSR|S_IWUSR)   //enable r/w by owner
int main(int argc, char *argv[])
{
    //Print to standard out an interesting string using printf
    printf("I'm sorry Dave, I'm afraid I can't do that.\n");

    //Create a file
    FILE * fp1;
    fp1 = fopen (FILEPATH, "w");
    fclose(fp1);

    //Modify the permissions of the file to be read/write
    chmod(FILEPATH, PERMISSIONS);

    //Open the file (for writing)
    FILE * fp2;
    fp2 = fopen (FILEPATH, "w");

    //Write a character to the file
    fprintf(fp2, "Q");
    //Close the file
    fclose(fp2);

    //Open the file (in append mode)
    FILE * fp3;
    fp3 = fopen (FILEPATH, "a");
    //Dynamically allocate an array of memory
    char *ptr = (char *) malloc(10 * sizeof (char));
    //Read and input string from the command line and write to the string
    char * cmd_arg = argv[1];
    //Write the string to the file
    fprintf(fp3, cmd_arg);
    //Flush file output
    fflush(fp3);
    //Close the file
    fclose(fp3);

    //Open the file (for reading)
    FILE * fp4;
    fp4 = fopen (FILEPATH, "r");
    //Read a single character (getc)
    char chr = getc(fp4);
    //Read a string of characters (gets)
    gets(ptr);

    //Close the file
    fclose(fp4);

    //Free the memory
    free(ptr);

    return 0;
}
