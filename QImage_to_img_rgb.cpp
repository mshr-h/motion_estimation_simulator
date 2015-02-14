#include "include/windows.h"

struct img_rgb_t *
QImage_to_img_rgb(
	QImage *Qimg
)
{
	int h, w;
	struct img_rgb_t *out;
	QColor c;

	out=img_rgb_create(Qimg->width(),Qimg->height(),0);

	for(h=0; h<out->ht; h++){
		for(w=0; w<out->wt; w++){
			c = QColor(Qimg->pixel(w, h));
			out->r[h][w] = c.red();
			out->g[h][w] = c.green();
			out->b[h][w] = c.blue();
		}
	}
	return out;
}
