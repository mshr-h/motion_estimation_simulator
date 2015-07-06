#include  "include/implab.h"

struct img_t *img_copy(int wt, int ht, unsigned char **data)
{
    struct img_t *new_img = img_create(wt, ht, 0);
    int h, w;
    for(h=0; h<ht; h++){
        for(w=0; w<wt; w++){
            new_img->data[h][w] = data[h][w];
        }
    }
    return new_img;
}
