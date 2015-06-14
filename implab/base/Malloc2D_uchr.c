#include  "include/implab.h"

unsigned char **
Malloc2D_uchr(
        int wt,
        int ht,
        unsigned char init
        )
{
    int h,w;
    unsigned char **x;

    x=(unsigned char **)malloc(sizeof(void *)*ht);
    if(x==NULL){
        printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
        exit(-1);
    }
    x[0]=(unsigned char *)malloc(sizeof(unsigned char)*ht*wt);
    if(x[0]==NULL){
        printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
        exit(-1);
    }

    for(h=1;h<ht;h++){
        x[h]=x[h-1]+wt;
    }
    for(h=0;h<ht;h++){
        for(w=0;w<wt;w++){
            x[h][w]=init;
        }
    }
    return x;
}
