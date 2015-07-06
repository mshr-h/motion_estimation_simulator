#include <stdlib.h>
#include <time.h>
#include "include/implab.h"
#include "include/motion_estimation.h"
#include "include/processor_element.h"

int main(int argc, char *argv[])
{
    if(argc < 4)
    {
        printf("./me movie.yuv 1920 1080\n");
        exit(1);
    }

    int width=atoi(argv[2]);
    int height=atoi(argv[3]);
    int total=width*height;
    size_t frame_bytes=total+total/4+total/4;

    FILE *fp_in=fopen(argv[1], "rb");
    if(NULL==fp_in)
    {
        fprintf(stderr, "cant open %s\n", argv[1]);
        exit(1);
    }

    fseek(fp_in, 0, 2);
    long filesize = ftell(fp_in);
    fseek(fp_in, 0, 0);

    struct img_yuv_t *frame_prev=img_yuv_create(width, height, 0);
    struct img_yuv_t *frame=img_yuv_create(width, height, 0);
    struct img_yuv_t *tmp;

    clock_t start=clock();

    unsigned char *frame_buf=(unsigned char *)malloc(sizeof(unsigned char)*frame_bytes);
    fread(frame_buf, 1, frame_bytes, fp_in);
    buf_to_img_yuv(frame_buf,frame_prev);

    printf("%s\n",argv[1]);
    printf("5bit_diff\n");

    while(frame_bytes==fread(frame_buf, 1, frame_bytes, fp_in))
    {
        buf_to_img_yuv(frame_buf,frame);

        // some process start
        struct img_t *img_curr=img_copy(width,height,frame->y);
        struct img_t *img_prev=img_copy(width,height,frame_prev->y);
        auto me_block=me_block_create(img_curr,img_prev,16,16);
        fullsearch(me_block,pe_5bit_diff);
        auto ave=me_block_calc_average_cost(me_block);
        me_block_destruct(me_block);
        img_destruct(img_prev);
        img_destruct(img_curr);
        // some process end

        img_yuv_to_buf(frame,frame_buf);

        printf("%f\n",ave);
        fflush(stdout);

        tmp=frame;
        frame=frame_prev;
        frame_prev=tmp;
    }

    printf("elapsed: %.1f\n", (double)(clock()-start)/CLOCKS_PER_SEC);

    fclose(fp_in);
    free(frame_buf);
    img_yuv_destruct(frame_prev);
    img_yuv_destruct(frame);

    return 0;
}
