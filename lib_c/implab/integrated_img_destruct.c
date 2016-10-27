#include  "include/implab.h"

void integrated_img_destruct(struct integrated_img_t *img)
{
    free(img->data[0]); free(img->data);
    free(img);
}
