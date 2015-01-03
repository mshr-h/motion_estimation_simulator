#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <time.h>
#include "include/windows.h"
#include "include/mainwindow.h"

extern QImage outImg;

void MainWindow::motionEstimation()
{
	struct img_rgb_t *curr_img=NULL;
	struct img_rgb_t *prev_img=NULL;
	int tb_size = 16;
	int sw_size = 48;
	clock_t start, end;

	QString curr_fileName = QFileDialog::getOpenFileName(this,
														 tr("Open Current Image"),
														 QDir::currentPath());
	QString prev_fileName = QFileDialog::getOpenFileName(this,
														 tr("Open Previous Image"),
														 QDir::currentPath());

	if (!curr_fileName.isEmpty()) {
		QImage Qimg(curr_fileName);
		if (Qimg.isNull()) {
			QMessageBox::information(this,
									 tr("Main Viewer"),
									 tr("Cannot load").arg(curr_fileName));
			return;
		}

		curr_img=QImage_to_img_rgb(&Qimg);
	}

	if (!prev_fileName.isEmpty()) {
		QImage Qimg(prev_fileName);
		if (Qimg.isNull()) {
			QMessageBox::information(this,
									 tr("Main Viewer"),
									 tr("Cannot load").arg(prev_fileName));
			return;
		}

		prev_img=QImage_to_img_rgb(&Qimg);
	}

	if(curr_img == NULL || prev_img == NULL) {
		return;
	}

	if(prev_img->ht != curr_img->ht && prev_img->wt != curr_img->wt) {
		QMessageBox::information(this,
								 tr("Main Viewer"),
								 tr("Image size don't match"));
		return;
	}

	qDebug() << "current  frame:" << curr_fileName;
	qDebug() << "previous frame:" << prev_fileName;
	qDebug() << "tb size:" << tb_size << "sw size:" << sw_size;
	qDebug() << "curr ht:" << curr_img->ht << "wt:" << curr_img->wt;
	qDebug() << "prev ht:" << prev_img->ht << "wt:" << prev_img->wt;

	start = clock();
	img_motion_estimation(curr_img, prev_img, tb_size, sw_size);
	end   = clock();
	qDebug() << "elapsed:" << (double)(end-start)/CLOCKS_PER_SEC << "sec";
}
