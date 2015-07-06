#include  "include/implab.h"

struct img_t *img_diff(struct img_t *img1, struct img_t *img2)
{
    int h, w;
    struct img_t *new_img;

    if(img1->ht != img2->ht || img1->wt != img2->wt)
    {
        printf("image size unmatched\n");
        fflush(stdout);
        return NULL;
    }

    new_img = img_create(img1->wt, img1->ht, 0);

    for(h=0; h<img1->ht; h++)
    {
        for(w=0; w<img1->wt; w++)
        {
            new_img->data[h][w] = abs(img1->data[h][w]-img2->data[h][w]);
        }
    }

    return new_img;
}
