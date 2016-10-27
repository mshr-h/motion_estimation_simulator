#include  "include/implab.h"

struct integrated_img_t *img_to_integrated(struct img_t *img)
{
    int w, h;
    struct integrated_img_t *tmp;
    struct integrated_img_t *out;

    tmp = integrated_img_create(img->wt+1, img->ht+1, 0);
    out = integrated_img_create(img->wt, img->ht, 0);

    for(h=1;h<tmp->ht;h++)
    {
        for(w=1;w<tmp->wt;w++)
        {
            tmp->data[h][w]
                    =img->data[h-1][w-1]
                    +tmp->data[h-1][w  ]
                    +tmp->data[h  ][w-1]
                    -tmp->data[h-1][w-1];
        }
    }
    return tmp;

    for(h=0;h<out->ht;h++)
    {
        for(w=0;w<out->wt;w++)
        {
            out->data[h][w]=tmp->data[h+1][w+1];
        }
    }

    integrated_img_destruct(tmp);

    return out;
}
