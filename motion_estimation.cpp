
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <time.h>
#include "include/windows.h"
#include "include/mainwindow.h"

extern QImage outImg;

void MainWindow::motionEstimation()
{
	struct img_rgb_t *curr_img_rgb=NULL;
	struct img_rgb_t *prev_img_rgb=NULL;
	struct img_yuv_t *curr_img_yuv=NULL;
	struct img_yuv_t *prev_img_yuv=NULL;

	int tb_size = 16;
	int sw_size = 48;
	clock_t start;
	QStringList testcase;

	testcase.append("blue_sky");
	testcase.append("pedestrian_area");
	testcase.append("riverbed");
	testcase.append("rush_hour");
	testcase.append("station2");
	testcase.append("sunflower");
	testcase.append("tractor");

	QDir currentPath = QDir::currentPath();
	currentPath.cdUp();
	currentPath.cd("motion_estimation");
	currentPath.cd("inImg_db");
	currentPath.cd("rgb");

	qDebug() << "currentPath:" << currentPath.absolutePath();
	start = clock();
	for(int i = 0; i < testcase.length(); i++) {
		QString currFileName = currentPath.absolutePath() + QDir::separator() + testcase.at(i) + "_0_rgb.png";
		QString prevFileName = currentPath.absolutePath() + QDir::separator() + testcase.at(i) + "_1_rgb.png";

		curr_img_rgb = loadImageToImg_rgb_t(currFileName);
		prev_img_rgb = loadImageToImg_rgb_t(prevFileName);

		curr_img_yuv = img_rgb_to_yuv(curr_img_rgb);
		prev_img_yuv = img_rgb_to_yuv(prev_img_rgb);

		if(curr_img_rgb == NULL || prev_img_rgb == NULL) {
			return;
		}

		if(prev_img_rgb->ht != curr_img_rgb->ht && prev_img_rgb->wt != curr_img_rgb->wt) {
			QMessageBox::information(this,
									 tr("Main Viewer"),
									 tr("Image size don't match"));
			return;
		}

		printf("Case %d: %s\n", i, qPrintable(testcase.at(i)));
		img_motion_estimation(curr_img_yuv, prev_img_yuv, tb_size, sw_size);

		img_rgb_destruct(curr_img_rgb);
		img_rgb_destruct(prev_img_rgb);
		img_yuv_destruct(curr_img_yuv);
		img_yuv_destruct(prev_img_yuv);
	}

	qDebug() << "elapsed:" << (double)(clock()-start)/CLOCKS_PER_SEC << "sec";
}

struct img_rgb_t *MainWindow::loadImageToImg_rgb_t(QString path)
{
	struct img_rgb_t *img = NULL;

	if (!path.isEmpty()) {
		QImage Qimg(path);
		if (Qimg.isNull()) {
			QMessageBox::information(this,
									 tr("Main Viewer"),
									 tr("Cannot load").arg(path));
			return NULL;
		}

		img=QImage_to_img_rgb(&Qimg);
	}

	return img;
}
