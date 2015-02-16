#include  "include/dehaze.h"

//------------------------------------------------------------------------------------
struct img_yuv_t *
img_yuv_create(
	int wt,
	int ht,
	unsigned char init
)
{
	struct img_yuv_t *new;

	new=(struct img_yuv_t *)malloc(sizeof(struct img_yuv_t));

	new->wt=wt;
	new->ht=ht;	

	new->y=Malloc2D_uchr(new->wt,new->ht,init);
	if(new->y==NULL){
		printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
	  exit(-1);
	}
	new->u=Malloc2D_uchr(new->wt,new->ht,init);
	if(new->u==NULL){
		printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
	  exit(-1);
	}
	new->v=Malloc2D_uchr(new->wt,new->ht,init);
	if(new->v==NULL){
		printf("malloc failed (%s,%i)\n",__FILE__,__LINE__);
	  exit(-1);
	}

	return new;
}
