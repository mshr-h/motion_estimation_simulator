#include  "include/implab.h"

void img_yuv_to_buf(struct img_yuv_t *frame, unsigned char *frame_buf)
{
    int w,h;
    int total=frame->wt*frame->ht;

    for(w=0;w<frame->wt;w++)
    {
        for(h=0;h<frame->ht;h++)
        {
            frame_buf[h*frame->wt+w]=frame->y[h][w];
            frame_buf[(h/2)*(frame->wt/2)+(w/2)+total]=frame->u[h][w];
            frame_buf[(h/2)*(frame->wt/2)+(w/2)+total+(total/4)]=frame->v[h][w];
        }
    }
}
