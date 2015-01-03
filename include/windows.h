#ifndef WINDOWS_H
#define WINDOWS_H

#include <QImage>
#include <QColor>
#include "implab.h"

// C++ functions
struct img_rgb_t *
QImage_to_img_rgb(
	QImage *inImg
);
#endif // WINDOWS_H
