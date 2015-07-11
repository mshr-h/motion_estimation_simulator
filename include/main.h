#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <time.h>
#include <QImage>
#include <QColor>
#include <QDebug>
#include "include/implab.h"
#include "include/motion_estimation.h"
#include "include/processor_element.h"

// protptype definitions
QImage img_rgb_to_QImage(struct img_rgb_t *img_rgb);
QImage img_to_QImage(struct img_t *img);
struct img_rgb_t *QImage_to_img_rgb(QImage *inImg);

int main_video_process(int argc, char *argv[]);
int main_frame_process(int argc, char *argv[]);

#endif // MAIN_H
