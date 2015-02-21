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
	free(img->r[0]); free(img->r);
	free(img->g[0]); free(img->g);
	free(img->b[0]); free(img->b);
	free(img);
}

struct img_yuv_t *
img_rgb_to_yuv(
	struct img_rgb_t *img_rgb
)
{
	int w,h;

	struct img_yuv_t *out;

	out=img_yuv_create(img_rgb->wt,img_rgb->ht,0);

	for(h=0;h<img_rgb->ht;h++){
		for(w=0;w<img_rgb->wt;w++){
			out->y[h][w]=( ( 66*img_rgb->r[h][w]+129*img_rgb->g[h][w]+25*img_rgb->b[h][w]+128)>>8 )+16;
			out->u[h][w]=( (-38*img_rgb->r[h][w]-74*img_rgb->g[h][w]+112*img_rgb->b[h][w]+128)>>8 )+128;
			out->v[h][w]=( (112*img_rgb->r[h][w]-94*img_rgb->g[h][w]-18*img_rgb->b[h][w]+128)>>8 )+128;
		}
	}

	return out;
}

struct img_yuv_t *
img_yuv_create(
	int wt,
	int ht,
	unsigned char init
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

void
img_yuv_destruct(
	struct img_yuv_t *img
)
{
	free(img->y[0]); free(img->y);
	free(img->u[0]); free(img->u);
	free(img->v[0]); free(img->v);
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
