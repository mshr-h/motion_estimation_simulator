#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void motionEstimation();
	struct img_rgb_t *loadImageToImg_rgb_t(QString path);

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
