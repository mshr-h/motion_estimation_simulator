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

void
img_rgb_destruct(
	struct img_rgb_t *img
)
{
	free(img->r);
	free(img->g);
	free(img->b);
	free(img);
}

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
