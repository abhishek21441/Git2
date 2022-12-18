#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char * StringList[50];

void genwords(int len){
    for(int i=0; i<50; i++){
        StringList[i] = (char*) malloc(len*(sizeof(char)));
        char string[len+1];

        for(int i=0; i<len;i++){
        
            int asciino;
            asciino = (rand()%26)+65;
            string[i] = (char)asciino;
        }
        string[len]='\0';
        StringList[i] = string;

        printf("%s\n", StringList[i]);
    }
}

int main()
{


    //index for StringList
    static int index=0;
    int fds_s2r,fds_r2s;

    // FIFO file path
    char * myfifos2r = "/tmp/myfifos2r";
    char * myfifor2s = "/tmp/myfifor2s";


    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifos2r, 0666);
    mkfifo(myfifor2s, 0666);

    // Open FIFO for write only
    fds_s2r = open(myfifos2r, O_WRONLY);

    // Open FIFO for Read only
    fds_r2s = open(myfifor2s, O_RDONLY);


    //for loop running 10 times

    for (int j = 0; j < 10; ++j)
    {
        

        for (int i = 0; i < 5; ++i)
        {
            write(fds_s2r, StringList[index], strlen(StringList[index]));
            write(fds_s2r, &index, sizeof(int));
            index++;    
        }


        //Integer that is Index of StringList
        int retindex;

        // Read from FIFO
        read(fds_r2s, retindex, sizeof(int));
        // Print the read message
        printf("User2: %d %s\n", retindex,StringList[retindex]);
        
    }


    close(fds_s2r);
    close(fds_r2s);

    

    return 0;
}