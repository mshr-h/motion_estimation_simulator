#include  "include/implab.h"

int32_t  **Malloc2D_int32(int ht, int wt, int32_t init)
{
    int h, w;
    int32_t **x;

    x=(int32_t **)malloc(sizeof(int32_t)*ht);
    if(x==NULL){
        printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
        exit(-1);
    }
    x[0]=(int32_t *)malloc(sizeof(int32_t)*ht*wt);
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
