#include  "include/implab.h"

void buf_to_img_yuv(unsigned char *frame_buf, struct img_yuv_t *frame)
{
    int w,h;
    int total=frame->wt*frame->ht;

    for(w=0;w<frame->wt;w++)
    {
        for(h=0;h<frame->ht;h++)
        {
            frame->y[h][w]=frame_buf[h*frame->wt+w];
            frame->u[h][w]=frame_buf[(h/2)*(frame->wt/2)+(w/2)+total];
            frame->v[h][w]=frame_buf[(h/2)*(frame->wt/2)+(w/2)+total+(total/4)];
        }
    }
}
