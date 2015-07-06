#include <QFileDialog>
#include <QDebug>
#include "include/mainwindow.h"
#include <time.h>
#include <iostream>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // set testcases
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
    currentPath.cd("motion_estimation_v2");
    currentPath.cd("inImg_db");
    currentPath.cd("rgb");

    auto outPath = currentPath.absolutePath()+QDir::separator()+"outImg"+QDir::separator();

    qDebug() << "currentPath:" << currentPath.absolutePath();

    clock_t start = clock();

    for(auto testimage: testcase)
    {
        // test images
        auto curr_file_name = currentPath.absolutePath() + QDir::separator() + testimage + "_0_rgb.png";
        auto prev_file_name = currentPath.absolutePath() + QDir::separator() + testimage + "_1_rgb.png";

        auto curr_img_yuv = loadImageToImg_yuv(curr_file_name);
        auto prev_img_yuv = loadImageToImg_yuv(prev_file_name);
        if(curr_img_yuv==NULL || prev_img_yuv==NULL)
            return;

        auto curr_img = img_copy(curr_img_yuv->wt, curr_img_yuv->ht, curr_img_yuv->y);
        auto prev_img = img_copy(prev_img_yuv->wt, prev_img_yuv->ht, prev_img_yuv->y);
        img_yuv_destruct(curr_img_yuv);
        img_yuv_destruct(prev_img_yuv);

        auto me_block = me_block_create(curr_img, prev_img, 16, 16);
        img_destruct(curr_img);
        img_destruct(prev_img);

        std::cout << "\t" << testimage.toStdString() << std::endl;

        auto resultlist=getResults(me_block, setupSearchMethod(), setupProcessorElement());
        auto it = resultlist.begin();
        while(it!=resultlist.end())
        {
            auto r=*it;
            std::cout << r.pix_operation << "\t" << r.average_cost << std::endl;
            it++;
        }

        me_block_destruct(me_block);
    }

    std::cout << "elapsed: " << (double)(clock()-start)/CLOCKS_PER_SEC << " sec" << std::endl;

    exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
