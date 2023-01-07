#ifndef PHYSICS_LOG
#define PHYSICS_LOG
#include <stdio.h>
extern FILE *fp_error;                           // general error file
extern char error_filename[80];                  // error file name

// error functions
int Open_Error_File(char *filename, FILE *fp_override=NULL);
int Close_Error_File(void);
int Write_Error(char *string, ...);

#endif