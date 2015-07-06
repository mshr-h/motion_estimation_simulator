#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "include/motion_estimation.h"
#include "include/processor_element.h"

struct result_t
{
    const char *pix_operation;
    const char *search_method;
    double average_cost;
};

struct search_method_t
{
    const char *name;
    void (*func)(struct me_block_t *, unsigned char (*)(unsigned char, unsigned char));
};

struct processor_element_t
{
    const char *name;
    unsigned char (*func)(unsigned char, unsigned char);
};

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
    struct img_yuv_t *loadImageToImg_yuv(QString path);
    QImage img_to_QImage(img_t *img);
    struct img_rgb_t *QImage_to_img_rgb(QImage *Qimg);
    std::list<struct search_method_t> setupSearchMethod();
    std::list<struct processor_element_t> setupProcessorElement();
    std::list<struct result_t> getResults(struct me_block_t *me_block, std::list<struct search_method_t> sm_list, std::list<struct processor_element_t> pe_list);

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
