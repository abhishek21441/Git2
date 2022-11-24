#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define SYS_kernel_2d_memcpy 451

int main(int argc, char **argv)
{
  int row = 2;
  int column = 2;

  float usrmat[row][column];
  float genmat[row][column];
  printf("The user matrix is:\n");
  for(int i = 0; i < row; i++){
    for(int j = 0; j < column; j++)
    {
      usrmat[i][j] = i+j;
//      printf("row: %d column: %d value: %f\n", i, j, usrmat[i][j]);
      printf("%f ",usrmat[i][j]);	
    }
    printf("\n");
  }

  int out = syscall(SYS_kernel_2d_memcpy,genmat,usrmat,row,column);

  printf("The generated matrix is:\n");
  for(int i = 0; i < row; i++){
    for(int j = 0; j < column; j++)
    {
      printf("%f ",genmat[i][j]);
    }
    printf("\n");
  }
  return 0;
  }
