#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
    //index for StringList
    static int pindex=0;
    int fdr_s2r,fdr_r2s;

    // FIFO file path
    char * myfifos2r = "/tmp/myfifos2r";
    char * myfifor2s = "/tmp/myfifor2s";


    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifos2r, 0666);
    mkfifo(myfifor2s, 0666);

    // Open FIFO for write only
    fdr_s2r = open(myfifos2r, O_RDONLY);

    // Open FIFO for Read only
    fdr_r2s = open(myfifor2s, O_WRONLY);



    //perma string and index read
    char pstr1[10];
    static int pstrindex=-1;

    for (int j = 0; j < 10; ++j)
    {
        // First open in read only and read
        for (int i = 0; i < 5; ++i)
        {
            //temp string and index read
            char* str1 = (char*) malloc (sizeof(char)*11);
            int strindex;
            read(fdr_s2r, str1, sizeof(str1));
            read(fdr_s2r, &strindex, sizeof(int));
            if(strindex>pstrindex){
                pstrindex = strindex;
                strcpy(pstr1,*str1);
            }

        }



        // Print the read string and close
        printf("User1: %s %d\n", pstr1,pstrindex);
        

        // Now open in write mode and write
        // string taken from user.
        write(fdr_r2s, &pstr1, sizeof(int));
        
        
    }
    close(fdr_s2r);
    close(fdr_r2s);
 
    return 0;
}