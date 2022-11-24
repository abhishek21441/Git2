#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <sys/syscall.h>
#include <sys/types.h>      
#include <time.h>  
#include <math.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/shm.h>

int PIDS[9];
struct timespec STARTS[9];
struct timespec FINISHES[9];

void setfintimes(struct timespec et, int pid){
    for(int i=0;i<3;i++){
        if(PIDS[i]==pid){
            FINISHES[i]=et;
            return;
        }

    }
}

int main(int argc, char const *argv[])
{
    clock_t t1,t2,t3;
    static int FIFOP,RRP,checkpos=0;
    struct timespec s1,e1,s2,e2,s3,e3;
    FIFOP=40;
    RRP=80;
    for(int j=0;j<3;j++){

        clock_gettime(CLOCK_REALTIME,&s1);
        STARTS[checkpos]=s1;
        checkpos+=1;
        int pid_id1 = fork();
        t1 = clock();
        if(pid_id1==0){
            struct sched_param param1;
            param1.sched_priority = FIFOP;
            sched_setscheduler(pid_id1,SCHED_FIFO,&param1);
            //execl("/bin/sh","sh","kerncomp1.sh",NULL);
            printf("hello1");
        }
        else{
            //waitpid(pid_id1,NULL,0);
            clock_gettime(CLOCK_REALTIME,&s2);
            STARTS[checkpos]=s2;
            checkpos+=1;
            int pid_id2 = fork();
            if(pid_id2==0){
                struct sched_param param2;
                param2.sched_priority = 0;
                sched_setscheduler(pid_id2,SCHED_OTHER,&param2);
                //execl("/bin/sh","sh","kerncomp1.sh",NULL);
                printf("hello1");


            }
            else{
                //waitpid(pid_id2,NULL,0);
                clock_gettime(CLOCK_REALTIME,&s3);
                STARTS[checkpos]=s3;
                checkpos+=1;
                int pid_id3 = fork();
                if(pid_id3==0){
                    struct sched_param param3;
                    param3.sched_priority = RRP;
                    sched_setscheduler(pid_id3,SCHED_RR,&param3);
                    //execl("/bin/sh","sh","kerncomp1.sh",NULL);
                    printf("hello1");

                }
                else{
                    //waitpid(pid_id2,NULL,0);
                }

            }
        }

         int pnos=0;
         while(pnos<3){
             int temp;
             temp = waitpid(-1,NULL,0);
             if(temp!=0){
                 struct timespec e;
                 clock_gettime(CLOCK_REALTIME,&e);
                 setfintimes(e,temp);
                 pnos++;
             }
        //     if(pnos==2){
        //         FILE *ptr;
        //         ptr = fopen("newprogram2.txt","a");
        //         fprintf(ptr,"fifo with priority: %d %lf\n",FIFOP,(double)((double)FINISHES[0].tv_sec - (double)STARTS[0].tv_sec) + (double)((double)FINISHES[0].tv_nsec - (double)STARTS[0].tv_nsec)/1000000000);
        //         fprintf(ptr,"other: %lf\n",(double)((double)FINISHES[1].tv_sec - (double)STARTS[1].tv_sec) + (double)((double)FINISHES[1].tv_nsec - (double)STARTS[1].tv_nsec)/1000000000);
        //         fprintf(ptr,"rr with priority: %d %lf\n",RRP,(double)((double)FINISHES[2].tv_sec - (double)STARTS[2].tv_sec) + (double)((double)FINISHES[2].tv_nsec - (double)STARTS[2].tv_nsec)/1000000000);
        //         fclose(ptr);
        //     }

         }

        FIFOP+=12;
        RRP-=12;

    }//for ends here
    
	return 0;
}
