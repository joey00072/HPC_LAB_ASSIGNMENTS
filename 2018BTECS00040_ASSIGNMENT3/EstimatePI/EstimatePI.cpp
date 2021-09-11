#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include <string.h> 
#include<omp.h>

#define SEED 6565 
 
int main() 
{ 
   int niter=0; 
   int count=0; 
 
   printf("Enter the number of iterations used to estimate pi: "); 
   scanf("%d",&niter); 
 
   srand(SEED); 
   double x,y,z;
   
   #pragma omp parallel for num_threads(8)  shared(niter) reduction(+: count)
   for (int i=0; i<niter; i++) { 
      x = (double)rand()/RAND_MAX; 
      y = (double)rand()/RAND_MAX; 
      
      z = x*x+y*y; 
      
      if (z<=1) 
      count++; 
    } 
   double pi=(double)count/niter*4; 
   printf("# of trials= %d , estimate of pi is %g \n",niter,pi); 
}

