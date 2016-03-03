#include  "include/implab.h"

struct img_yuv_t *
        img_yuv_create(
        int wt,
        int ht,
        uint8_t init
        )
{
    struct img_yuv_t *img;

    img=(struct img_yuv_t *)malloc(sizeof(struct img_yuv_t));

    img->wt=wt;
    img->ht=ht;

    img->y=Malloc2D_uchr(img->wt,img->ht,init);
    if(img->y==NULL){
        printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
        exit(-1);
    }
    img->u=Malloc2D_uchr(img->wt,img->ht,init);
    if(img->u==NULL){
        printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
        exit(-1);
    }
    img->v=Malloc2D_uchr(img->wt,img->ht,init);
    if(img->v==NULL){
        printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
        exit(-1);
    }

    return img;
}
