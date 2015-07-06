#include  "include/implab.h"

struct img_rgb_t *
        img_rgb_create(
        int wt,
        int ht,
        unsigned char init
        )
{
    struct img_rgb_t *new_img;

    new_img=(struct img_rgb_t *)malloc(sizeof(struct img_rgb_t));

    new_img->wt=wt;
    new_img->ht=ht;

    new_img->r=Malloc2D_uchr(new_img->wt,new_img->ht,init);
    if(new_img->r==NULL){
        printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
        exit(-1);
    }
    new_img->g=Malloc2D_uchr(new_img->wt,new_img->ht,init);
    if(new_img->g==NULL){
        printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
        exit(-1);
    }
    new_img->b=Malloc2D_uchr(new_img->wt,new_img->ht,init);
    if(new_img->b==NULL){
        printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
        exit(-1);
    }
    return new_img;
}
