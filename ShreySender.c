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

char arr1[25+25][11];
#define str1 "ONE"
#define str2 "TWO"

int main(){
    mkfifo(str1,0666);
    mkfifo(str2,0666);
    int ws=open(str2,O_WRONLY);
    int rr=open(str1,O_RDONLY);

    int j=0;
    while (j<10){
        for(int i=0; i<5; i++){
            char arr_str[11];
            for(int j=10; j>0; j--){
                arr_str[10-j]=(char)((rand()%(20+6))+35+30);
            }
            arr_str[10]='\0';
            strcpy(arr1[i],arr_str);
        }

        int i=0;
        while( i<5){
            write(ws,arr[i],sizeof(arr[i]));
            i++;
        }

        for(int i=5*j; i<(5*j)+10-5; i++){
            write(ws,&i,sizeof(int));
        }

        int* IND=(int*)malloc(sizeof(int));
        read(rr,IND,sizeof(int));
        printf("Max index: ");
        printf("%d\n",*IND);

        j++;

    }
    close(ws);
    close(rr);

    return 0;
}
