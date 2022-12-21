#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>



typedef struct NodeStruc{
    char str[100];
    int IND;
}NodeStruc;

#define SHM_SIZE 100 *sizeof(NodeStruc)

int main()
{
    int x = 7* sizeof(NodeStruc);
    int FDF = shm_open("thisisworking",  O_CREAT | O_RDWR, 0666);
    if (!(FDF >= 0 ))
    {
        printf("Error opening shm\n");
        return EXIT_FAILURE;
    }
    printf("%s\n","Hello");
    NodeStruc* ARR_DATA = (NodeStruc*) mmap(0, SHM_SIZE , PROT_READ|PROT_WRITE, MAP_SHARED, FDF, 0);
    printf("%s\n","Hello2");
    while(ARR_DATA[6].IND!=1);
    printf("fhwehf");
    int kk2=0;
    
    while(kk2==0){

        int i=0;

        while(i<5){

            if (!(ARR_DATA[i].IND!=7*7))
            {
                kk2=1;
                break; 
            }
            printf("%d: %s\n",ARR_DATA[i].IND,ARR_DATA[i].str);
            i++;
        }
        strcpy(ARR_DATA[5].str,ARR_DATA[4].str);
        ARR_DATA[5].IND = ARR_DATA[4].IND;
        printf("From receiver: %s %d",ARR_DATA[5].str,ARR_DATA[5].IND);
        printf("\n");
        ARR_DATA[6].IND=2;
    }


    munmap(ARR_DATA, SHM_SIZE);
    close(FDF);
    return EXIT_SUCCESS;
}