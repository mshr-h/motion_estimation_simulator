#include  "include/implab.h"

struct img_rgb_t *img_yuv_to_rgb(struct img_yuv_t *img_yuv)
{
    int w,h;
    int r,g,b,c,d,e;

    struct img_rgb_t *out;

    out=img_rgb_create(img_yuv->wt,img_yuv->ht,0);

    for(h=0;h<img_yuv->ht;h++)
    {
        for(w=0;w<img_yuv->wt;w++)
        {
            c=img_yuv->y[h][w]-16;
            d=img_yuv->u[h][w]-128;
            e=img_yuv->v[h][w]-128;
            r=(298*c+409*e+128)>>8;
            g=(298*c-100*d-208*e+128)>>8;
            b=(298*c+516*d+128)>>8;
            out->r[h][w]=(r>255)?255:(r<0)?0:r;
            out->g[h][w]=(g>255)?255:(g<0)?0:g;
            out->b[h][w]=(b>255)?255:(b<0)?0:b;
        }
    }

    return out;
}
