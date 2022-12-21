# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <fcntl.h>
# include <limits.h>
# include <time.h>
# include <stdio.h>
# include <sys/stat.h>

#define str1 "ONE"
#define str2 "TWO"

int main(){
    mkfifo(str1,0666);
    mkfifo(str2,0666);

    int ws=open(str1,O_WRONLY);
    int rr=open(str2,O_RDONLY);

    int j=0;
    while( j<10){
        for(int i=5;i>0;i--){
            char *dd=(char *)malloc((10+1)*sizeof(char));
            read(rr,dd,(10+1));
            printf("%s ",dd);
        }

        int mx=-1;

        printf("\n");

        int i=5;
        while(i>0){
            int *ir=(int *)malloc(sizeof(int));
            read(rr,ir,sizeof(int));
            if(mx<*ir){
                mx=*ir;
            }
            printf("%d ",mx);
            i--;
        }
        printf("\n");
        write(ws,&mx,sizeof(int));
        j++;
    }
    close(ws);
    close(rr);
}