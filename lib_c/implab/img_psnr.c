#include  "include/implab.h"

double img_psnr(struct img_t *img1, struct img_t *img2)
{
    int h, w;
    double MSE;
    double psnr;

    if(img1->ht != img2->ht || img1->wt != img2->wt)
    {
        printf("image size unmatched\n");
        fflush(stdout);
        return -1;
    }

    MSE=0;
    for(h=0; h<img1->ht; h++)
    {
        for(w=0; w<img1->wt; w++)
        {
            MSE += (img1->data[h][w]-img2->data[h][w])*(img1->data[h][w]-img2->data[h][w]);
        }
    }

    MSE /= img1->ht*img1->wt;

    if(MSE==0.0)
        return 99.0;

    psnr=10*log10(255*255/MSE);

    return psnr;
}
