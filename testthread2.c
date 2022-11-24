#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <sys/syscall.h>
#include <sys/types.h>      
#include <time.h>  
#include <math.h>

                                                
                   

void *thread1(void *arg)                                                
{    
   int rc1;
   long int  _MAX_ = pow(2,32); 
   struct sched_param param1;  
   param1.sched_priority = 0;
   rc1=pthread_setschedparam(pthread_self(),SCHED_OTHER,&param1); 


   clock_t t1;
   t1 = clock();
   for (long int iI = 0; iI < _MAX_; ++iI){
      //printf("%d\n", I);
   }
   t1 = clock()-t1;
   double time1 = ((double)t1)/CLOCKS_PER_SEC;

   
   printf("Time taken SCHED_OTHER is: %f\n", time1);
   FILE *ptr;
   ptr = fopen("newprogram.txt","a");
   fprintf(ptr,"other: %lf\n",time1);
   fclose(ptr);
   printf("\n"); 
                                
   pthread_exit(NULL);                                                          
} 

void *thread2(void *arg)                                                    
{                                                                               
   int rc2;
   static int priority = 40;
   struct sched_param param2;
   param2.sched_priority = priority;
   long int  _MAX_ = pow(2,32);

   rc2=pthread_setschedparam(pthread_self(),SCHED_RR,&param2);

   clock_t t2;
   t2 = clock();

   for (long int iI = 0; iI < _MAX_; ++iI){
      //printf("%d\n", iI);
   }  

   t2 = clock()-t2;
   double time2 = ((double)t2)/CLOCKS_PER_SEC;
   
   printf("Time taken by SCHED_RR is: %f\n", time2);  
   FILE *ptr;
   ptr = fopen("newprogram.txt","a");
   fprintf(ptr,"rr: %lf\n",time2);
   fclose(ptr);
   priority+=6;  
   printf("\n");                                                           
   pthread_exit(NULL);                                                          
} 

void *thread3(void *arg)                                                  
{                                                                               
   int rc3;
   static int priority = 40;
   struct sched_param param3;
   param3.sched_priority = priority;
   long int  _MAX_ = pow(2,32);
   clock_t t3;
   t3 = clock();

   rc3=pthread_setschedparam(pthread_self(),SCHED_FIFO,&param3);


   for (long int iI = 0; iI < _MAX_; ++iI){
      //printf("%d\n", iI);
   }   
   t3 = clock()-t3;
   double time3 = ((double)t3)/CLOCKS_PER_SEC;
   printf("Time taken SCHED_FIFO is: %f\n", time3); 
   FILE *ptr;
   ptr = fopen("newprogram.txt","a");
   fprintf(ptr,"fifo: %lf\n",time3);
   fclose(ptr);
   priority+=6;  
   printf("\n");                                                                                                                       
   pthread_exit(NULL);                                                          
}                                                                               
                                                                                
int main()                                                                      
{     

   //______Setting_up_initial_Conditions________________                                                                          
   int            rc1,rc2,rc3, stat1,stat2,stat3;                                                                                                          
   pthread_t      thid1,thid2,thid3;
   int i =0;

   while(i<6){

      //OTHER Thread
      rc1 = pthread_create(&thid1, NULL, thread1, NULL);

      //RR Thread
      rc2 = pthread_create(&thid2, NULL, thread2, NULL);


      //FIFO Thread
      rc3 = pthread_create(&thid3, NULL, thread3, NULL);


   //_______All_Joins___________________________

      rc1 = pthread_join(thid1, NULL);
    
      rc2 = pthread_join(thid2, NULL);
      
      rc3 = pthread_join(thid3,NULL);
     
      i++;

   }

   printf("Finished running 3 threads 6 times at different priorities\n");
   

                                                          
}                                                                               
