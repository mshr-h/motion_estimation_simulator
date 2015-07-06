#include <QMessageBox>
#include "include/mainwindow.h"
#include "include/implab.h"

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
