#include  "include/implab.h"

uint8_t **
Malloc2D_uchr(
        int wt,
        int ht,
        uint8_t init
        )
{
    int h,w;
    uint8_t **x;

    x=(uint8_t **)malloc(sizeof(void *)*ht);
    if(x==NULL){
        printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
        exit(-1);
    }
    x[0]=(uint8_t *)malloc(sizeof(uint8_t)*ht*wt);
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
