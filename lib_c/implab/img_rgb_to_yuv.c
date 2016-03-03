#include  "include/implab.h"

struct img_yuv_t *img_rgb_to_yuv(struct img_rgb_t *img)
{
    int w,h;

    struct img_yuv_t *out;

    out=img_yuv_create(img->wt,img->ht,0);

    for(h=0;h<img->ht;h++){
        for(w=0;w<img->wt;w++){
            out->y[h][w]=(uint8_t)( 0.299*img->r[h][w]+0.587*img->g[h][w]+0.114*img->b[h][w]);
            out->u[h][w]=(uint8_t)(-0.169*img->r[h][w]-0.331*img->g[h][w]+0.500*img->b[h][w])-128;
            out->v[h][w]=(uint8_t)( 0.500*img->r[h][w]-0.419*img->g[h][w]-0.081*img->b[h][w])-128;
        }
    }

    return out;
}
