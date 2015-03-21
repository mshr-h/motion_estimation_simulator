#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <time.h>
#include "include/windows.h"
#include "include/mainwindow.h"

extern QImage outImg;

void MainWindow::motionEstimation()
{
	int tb_size = 16;
	int sw_range = 16; // -16, ..., +16

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

	qDebug() << "currentPath:" << currentPath.absolutePath();
	clock_t start = clock();

	printf("grayscale\t");
	printf("Fullsearch 8bit\t");
	printf("Fullsearch 4bit 4pix\t");
	printf("Fullsearch 4bit 4pix dynamic\t");
	printf("Fullsearch 4bit 4pix proposed 1\t");
	printf("Fullsearch 1bit 4pix xor\t");
	printf("Fullsearch 2bit 4pix xor\t");
	printf("Fullsearch 3bit 4pix xor\t");
	printf("Fullsearch 4bit 4pix xor\t");
	printf("Fullsearch 5bit 4pix xor\t");
	printf("Fullsearch 6bit 4pix xor\t");
	printf("Fullsearch 7bit 4pix xor\t");
	printf("Fullsearch 8bit 4pix xor\n");
	fflush(stdout);

	for(int i = 0; i < testcase.length(); i++) {
		QString currFileName = currentPath.absolutePath() + QDir::separator() + testcase.at(i) + "_0.png";
		QString prevFileName = currentPath.absolutePath() + QDir::separator() + testcase.at(i) + "_1.png";

		struct img_rgb_t *curr_img_rgb = loadImageToImg_rgb(currFileName);
		struct img_rgb_t *prev_img_rgb = loadImageToImg_rgb(prevFileName);

		struct img_yuv_t *curr_img_yuv = img_rgb_to_yuv(curr_img_rgb);
		struct img_yuv_t *prev_img_yuv = img_rgb_to_yuv(prev_img_rgb);

		struct img_t *cimg = img_copy(curr_img_rgb->wt, curr_img_rgb->ht, curr_img_rgb->r);
		struct img_t *pimg = img_copy(prev_img_rgb->wt, prev_img_rgb->ht, prev_img_rgb->r);

		if(prev_img_rgb->ht != curr_img_rgb->ht && prev_img_rgb->wt != curr_img_rgb->wt) {
			QMessageBox::information(this,
									 tr("Main Viewer"),
									 tr("Image size don't match"));
			return;
		}

		printf("%s\t", qPrintable(testcase.at(i)));

		img_motion_estimation(cimg, pimg, tb_size, sw_range);

		img_destruct(cimg);
		img_destruct(pimg);
		img_rgb_destruct(curr_img_rgb);
		img_rgb_destruct(prev_img_rgb);
		img_yuv_destruct(curr_img_yuv);
		img_yuv_destruct(prev_img_yuv);
	}

	currentPath.cd("rgb");
	qDebug() << "currentPath:" << currentPath.absolutePath();
	printf("lumina channel\t");
	printf("Fullsearch 8bit\t");
	printf("Fullsearch 8bit xor\t");
	printf("Fullsearch 4bit 4pix\t");
	printf("Fullsearch 4bit 4pix dynamic\t");
	printf("Fullsearch 4bit 4pix proposed 1\t");
	printf("Fullsearch 4bit 4pix proposed 2\t");
	printf("Fullsearch 1bit 4pix xor\t");
	printf("Fullsearch 2bit 4pix xor\t");
	printf("Fullsearch 3bit 4pix xor\t");
	printf("Fullsearch 4bit 4pix xor\t");
	printf("Fullsearch 5bit 4pix xor\t");
	printf("Fullsearch 6bit 4pix xor\t");
	printf("Fullsearch 7bit 4pix xor\t");
	printf("Fullsearch 8bit 4pix xor\n");
	fflush(stdout);

	for(int i = 0; i < testcase.length(); i++) {
		QString currFileName = currentPath.absolutePath() + QDir::separator() + testcase.at(i) + "_0_rgb.png";
		QString prevFileName = currentPath.absolutePath() + QDir::separator() + testcase.at(i) + "_1_rgb.png";

		struct img_rgb_t *curr_img_rgb = loadImageToImg_rgb(currFileName);
		struct img_rgb_t *prev_img_rgb = loadImageToImg_rgb(prevFileName);

		struct img_yuv_t *curr_img_yuv = img_rgb_to_yuv(curr_img_rgb);
		struct img_yuv_t *prev_img_yuv = img_rgb_to_yuv(prev_img_rgb);

		struct img_t *cimg = img_copy(curr_img_yuv->wt, curr_img_yuv->ht, curr_img_yuv->y);
		struct img_t *pimg = img_copy(prev_img_yuv->wt, prev_img_yuv->ht, prev_img_yuv->y);

		if(prev_img_rgb->ht != curr_img_rgb->ht && prev_img_rgb->wt != curr_img_rgb->wt) {
			QMessageBox::information(this,
									 tr("Main Viewer"),
									 tr("Image size don't match"));
			return;
		}

		printf("%s\t", qPrintable(testcase.at(i)));

		img_motion_estimation(cimg, pimg, tb_size, sw_range);

		img_destruct(cimg);
		img_destruct(pimg);
		img_rgb_destruct(curr_img_rgb);
		img_rgb_destruct(prev_img_rgb);
		img_yuv_destruct(curr_img_yuv);
		img_yuv_destruct(prev_img_yuv);
	}

	qDebug() << "elapsed:" << (double)(clock()-start)/CLOCKS_PER_SEC << "sec";
}

struct img_rgb_t *MainWindow::loadImageToImg_rgb(QString path)
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
