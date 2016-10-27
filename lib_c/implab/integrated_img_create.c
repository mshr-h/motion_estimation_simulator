#include  "include/implab.h"

struct integrated_img_t *integrated_img_create(int wt, int ht, uint64_t init)
{
    struct integrated_img_t *new_img;

    new_img=(struct integrated_img_t *)malloc(sizeof(struct integrated_img_t));

    new_img->wt=wt;
    new_img->ht=ht;

    new_img->data=Malloc2D_int32(new_img->wt,new_img->ht,init);
    if(new_img->data==NULL){
        printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
        exit(-1);
    }

    return new_img;
}
