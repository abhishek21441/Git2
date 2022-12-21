#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

typedef struct NodeStruc{
    char str[100];
    int IND;
}NodeStruc;

char LST_STR[50][10];

#define SHM_SIZE 100 * sizeof(NodeStruc)


int kk=0;

int main()
{
    static int INDEX=0;
    int i = 0;
    while(i<50){
        LST_STR[i];
        char string[10];
        int i=0;
        while(i<9){
            int num_as;
            num_as = (rand()%(26))+97;
            string[i] = (char)num_as;
            i++;
        }
        string[9]='\0';
        strcpy(LST_STR[i],string);

        i++;
    }
    int FDF = shm_open("thisisworking", O_CREAT | O_RDWR, 0600);
    if (FDF < 0) {
        printf("Error creating shm object\n");
        return EXIT_FAILURE;
    }

    ftruncate(FDF, SHM_SIZE);
    //printf("%s\n","Shello1" );
    NodeStruc* ARR_DATA = (NodeStruc*) mmap(0, SHM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, FDF, 0);
    ARR_DATA[6].IND=0;
    //printf("%s\n","Shello2" );


    while(kk==0){
        while(ARR_DATA[6].IND!=0);
        int ITERATOR=0;
        while ( ITERATOR<5){

            strcpy(ARR_DATA[ITERATOR].str,LST_STR[INDEX]);
            ARR_DATA[ITERATOR].IND=INDEX;
            if(!(INDEX!=49)){
                kk=1;
                break;
            }
            INDEX++;
            ITERATOR++;
        }

        ARR_DATA[6].IND=1;        

        while(ARR_DATA[6].IND!=2);

        printf("From Sender: %s %d\n",ARR_DATA[5].str,ARR_DATA[4].IND);

        INDEX = ARR_DATA[5].IND;
        ARR_DATA[6].IND=0;
    }
    
    munmap(ARR_DATA,SHM_SIZE);
    close(FDF);
    return EXIT_SUCCESS;
}