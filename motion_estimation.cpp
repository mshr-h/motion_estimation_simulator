#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <time.h>
#include "include/windows.h"
#include "include/mainwindow.h"

extern QImage outImg;

void MainWindow::motionEstimation()
{
    int size_tb = 16;
    int range_sw = 16; // -16, ..., +16

    QStringList testcase;
    testcase.append("blue_sky");
    testcase.append("pedestrian_area");
    testcase.append("riverbed");
    testcase.append("rush_hour");
    testcase.append("station2");
    testcase.append("sunflower");
    testcase.append("tractor");

    // change current path to inImg_db directory
    QDir currentPath = QDir::currentPath();
    currentPath.cdUp();
    currentPath.cd("motion_estimation");
    currentPath.cd("inImg_db");

    qDebug() << "currentPath:" << currentPath.absolutePath();
    clock_t start = clock();

    printf("luminance\t");
    printf("8bit 1pix\t");
    printf("4bit 4pix\t");
    printf("8bit 4pix diff2 xor6\t");
    printf("8bit 4pix diff3 xor5\t");
    printf("8bit 4pix diff4 xor4\t");
    printf("8bit 4pix diff5 xor3\t");
    printf("8bit 4pix diff6 xor2\n");
    fflush(stdout);

    for(int i = 0; i < testcase.length(); i++) {
        QString currFileName = currentPath.absolutePath() + QDir::separator() + testcase.at(i) + "_0.png";
        QString prevFileName = currentPath.absolutePath() + QDir::separator() + testcase.at(i) + "_1.png";

        struct img_yuv_t *curr_img_yuv = loadImageToImg_yuv(currFileName);
        struct img_yuv_t *prev_img_yuv = loadImageToImg_yuv(prevFileName);

        struct img_t *cimg = img_copy(curr_img_yuv->wt, curr_img_yuv->ht, curr_img_yuv->y);
        struct img_t *pimg = img_copy(prev_img_yuv->wt, prev_img_yuv->ht, prev_img_yuv->y);
        img_yuv_destruct(curr_img_yuv);
        img_yuv_destruct(prev_img_yuv);

        if(pimg->ht != cimg->ht && pimg->wt != cimg->wt) {
            QMessageBox::information(this,
                                     tr("Main Viewer"),
                                     tr("Image size don't match"));
            return;
        }

        printf("%s\t", qPrintable(testcase.at(i)));

        img_motion_estimation(cimg, pimg, size_tb, range_sw);

        img_destruct(cimg);
        img_destruct(pimg);
    }

    qDebug() << "elapsed:" << (double)(clock()-start)/CLOCKS_PER_SEC << "sec";
}

struct img_yuv_t *MainWindow::loadImageToImg_yuv(QString path)
{
    struct img_rgb_t *img_rgb = NULL;

    if (!path.isEmpty()) {
        QImage Qimg(path);
        if (Qimg.isNull()) {
            QMessageBox::information(this,
                                     tr("Main Viewer"),
                                     tr("Cannot load").arg(path));
            return NULL;
        }

        img_rgb=QImage_to_img_rgb(&Qimg);
    }

    struct img_yuv_t *img_yuv = img_rgb_to_yuv(img_rgb);
    img_rgb_destruct(img_rgb);

    return img_yuv;
}
