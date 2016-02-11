#include  "include/implab.h"

int mirror(int x, int min, int max){
    while(x < min || x >= max){
        if(x < min) x = min + (min - x - 1);
        if(x >= max) x = max + (max - x - 1);
    }

    return x;
}

float SQR(float x){
    return x * x;
}

double img_ssim(struct img_t *img1, struct img_t *img2)
{
    float c1 = SQR(0.01f * 255.0f);
    float c2 = SQR(0.03f * 255.0f);

    int m = 16;

    float Sum = 0.0f;

    int mx, my;
    int y, x;
    int dy, dx;

    int height=img1->ht;
    int width=img1->wt;

    if(img1->ht != img2->ht || img1->wt != img2->wt)

    {
        printf("image size unmatched\n");
        fflush(stdout);
        return -1;
    }

    for(y=0;y<height;y++){
        for(x=0;x<width;x++){

            float ave1 = 0.0f, ave2 = 0.0f; // 平均
            float var1 = 0.0f, var2 = 0.0f; // 分散
            float cov = 0.0f; // 共分散

            for(dy=-m;dy<=m;dy++){
                for(dx=-m;dx<=m;dx++){
                    mx = mirror(x + dx, 0, width);
                    my = mirror(y + dy, 0, height);

                    ave1 += img1->data[my][mx];
                    ave2 += img2->data[my][mx];
                }
            }
            ave1 /= SQR(m * 2.0f + 1.0f);
            ave2 /= SQR(m * 2.0f + 1.0f);

            for(dy=-m;dy<=m;dy++){
                for(dx=-m;dx<=m;dx++){
                    mx = mirror(x + dx, 0, width);
                    my = mirror(y + dy, 0, height);

                    var1 += SQR(img1->data[my][mx] - ave1);
                    var2 += SQR(img2->data[my][mx] - ave2);
                    cov += (img1->data[my][mx] - ave1) * (img2->data[my][mx] - ave2);
                }
            }
            var1 /= SQR(m * 2.0f + 1.0f);
            var2 /= SQR(m * 2.0f + 1.0f);
            cov /= SQR(m * 2.0f + 1.0f);

            Sum += ((2.0f * ave1 * ave2 + c1) * (2.0f * cov + c2)) / ((SQR(ave1) + SQR(ave2) + c1) * (var1 + var2 + c2));
        }
    }

    return Sum / (width * height);
}
