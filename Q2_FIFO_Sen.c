# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <time.h>
# include <pthread.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

char StringList[50][11];
// int string_idx[50];

int main(){
    mkfifo("fifor2s",0666);
    mkfifo("fifos2r",0666);
    int wfifos2r=open("fifos2r",O_WRONLY);
    int rfifor2s=open("fifor2s",O_RDONLY);

    clock_t time = clock();
    for(int j=0; j<10; j++){
        for(int i=0; i<5; i++){
            char str[11];
            for(int j=0; j<10; j++){
                str[j]=(char)((rand()%26)+65);
            }
            str[10]='\0';
            strcpy(StringList[i],str);
        }


        int string_idx[50];

        for(int i=0; i<5; i++){
            write(wfifos2r,StringList[i],11);
        }

        for(int i=0+5*j; i<5+5*j; i++){
            write(wfifos2r,&i,sizeof(int));
        }

        
        int* max_idx=(int*)malloc(sizeof(int));
        read(rfifor2s,max_idx,sizeof(int));
        printf("Max index & Max word: ");
        printf("%d %s\n",*max_idx,StringList[*max_idx]);

    }

    time = clock()-time;

    printf("TIme: %d",(int)time);
    close(wfifos2r);
    close(rfifor2s);

    return 0;
}
