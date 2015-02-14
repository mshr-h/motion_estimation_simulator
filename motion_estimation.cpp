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
	QStringList testcase;

	testcase.append(tr("blue_sky"));
	testcase.append(tr("pedestrian_area"));
	testcase.append(tr("riverbed"));
	testcase.append(tr("rush_hour"));
	testcase.append(tr("station2"));
	testcase.append(tr("sunflower"));
	testcase.append(tr("tractor"));

	QString currentPath = QDir::currentPath() + "\\..\\motion_estimation\\inImg_db\\";

	qDebug() << "currentPath:" << currentPath;
	start = clock();
	for(int i = 0; i < testcase.length(); i++) {
		QString currFileName = currentPath + testcase.at(i) + "_0.png";
		QString prevFileName = currentPath + testcase.at(i) + "_1.png";

		curr_img = loadImageToImg_rgb_t(currFileName);
		prev_img = loadImageToImg_rgb_t(prevFileName);

		if(curr_img == NULL || prev_img == NULL) {
			return;
		}

		if(prev_img->ht != curr_img->ht && prev_img->wt != curr_img->wt) {
			QMessageBox::information(this,
									 tr("Main Viewer"),
									 tr("Image size don't match"));
			return;
		}

		printf("Case %d: %s\n", i, testcase.at(i).toStdString());
		img_motion_estimation(curr_img, prev_img, tb_size, sw_size);
		img_rgb_destruct(curr_img);
		img_rgb_destruct(prev_img);
	}
	end   = clock();
	qDebug() << "elapsed:" << (double)(end-start)/CLOCKS_PER_SEC << "sec";
}

struct img_rgb_t *MainWindow::loadImageToImg_rgb_t(QString path)
{
	struct img_rgb_t *img;

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
