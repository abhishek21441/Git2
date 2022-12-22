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

int main(){
    mkfifo("fifor2s",0666);
    mkfifo("fifos2r",0666);

    int rfifos2r=open("fifos2r",O_RDONLY);
    int wfifor2s=open("fifor2s",O_WRONLY);


    for(int j=0; j<10; j++){
    
        for(int i=0; i<5; i++){
            char *temp_str=(char *)malloc(11*sizeof(char));
            read(rfifos2r,temp_str,11);
            printf("%s ",temp_str);
        }

        int max_idx=-1;

        printf("\n");

        for(int i=0; i<5; i++){
            int *read_int=(int *)malloc(sizeof(int));
            read(rfifos2r,read_int,sizeof(int));
            if(max_idx<*read_int){
                max_idx=*read_int;
            }
            printf("%d ",max_idx);
        }
        
        printf("\n");
        write(wfifor2s,&max_idx,sizeof(int));
    }
    close(rfifos2r);
    close(wfifor2s);
    return 0;
}