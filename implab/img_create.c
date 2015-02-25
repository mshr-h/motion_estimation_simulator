#include  "include/implab.h"

struct img_t *
img_create(
	int wt,
	int ht,
	unsigned char init
)
{
	struct img_t *new_img;

	new_img=(struct img_t *)malloc(sizeof(struct img_t));

	new_img->wt=wt;
	new_img->ht=ht;

	new_img->data=Malloc2D_uchr(new_img->wt,new_img->ht,init);
	if(new_img->data==NULL){
		printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
		exit(-1);
	}

	return new_img;
}
