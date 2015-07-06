#include "include/mainwindow.h"
#include "include/implab.h"

QImage MainWindow::img_to_QImage(struct img_t *img)
{
    int h,w;

    QImage outImg(img->wt,img->ht,QImage::Format_RGB888);

    for(h=0; h<img->ht; h++){
        for(w=0;w<img->wt;w++){
            outImg.setPixel(w,h,qRgb((int)img->data[h][w],
                                     (int)img->data[h][w],
                                     (int)img->data[h][w]) );
        }
    }

    return outImg;
}
