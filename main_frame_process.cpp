
#include "include/main.h"

int main_frame_process(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("./motion_estimation current_frame.png reference_frame.png output.csv\n");
        exit(1);
    }

    clock_t start=clock();

    QImage prev_qimg(argv[2]);
    if(prev_qimg.isNull())
    {
        printf("couldn't open %s\n", argv[2]);
        exit(1);
    }

    QImage curr_qimg(argv[2]);
    if(curr_qimg.isNull())
    {
        printf("couldn't open %s\n", argv[1]);
        exit(1);
    }

    auto curr_img_rgb=QImage_to_img_rgb(&curr_qimg);
    auto prev_img_rgb=QImage_to_img_rgb(&prev_qimg);

    auto curr_img_yuv=img_rgb_to_yuv(curr_img_rgb);
    auto prev_img_yuv=img_rgb_to_yuv(prev_img_rgb);
    img_rgb_destruct(curr_img_rgb);
    img_rgb_destruct(prev_img_rgb);

    auto curr_img=img_copy(curr_img_yuv->wt,curr_img_yuv->ht,curr_img_yuv->y);
    auto prev_img=img_copy(prev_img_yuv->wt,prev_img_yuv->ht,prev_img_yuv->y);
    img_yuv_destruct(curr_img_yuv);
    img_yuv_destruct(prev_img_yuv);

    auto me_block_1bit_diff=me_block_create(curr_img, prev_img, 16, 16);
    auto me_block_2bit_diff=me_block_create(curr_img, prev_img, 16, 16);
    auto me_block_3bit_diff=me_block_create(curr_img, prev_img, 16, 16);
    auto me_block_4bit_diff=me_block_create(curr_img, prev_img, 16, 16);
    auto me_block_5bit_diff=me_block_create(curr_img, prev_img, 16, 16);
    auto me_block_6bit_diff=me_block_create(curr_img, prev_img, 16, 16);
    auto me_block_7bit_diff=me_block_create(curr_img, prev_img, 16, 16);
    auto me_block_8bit_diff=me_block_create(curr_img, prev_img, 16, 16);
    auto me_block_2bit_diff_6bit_exor=me_block_create(curr_img, prev_img, 16, 16);
    auto me_block_3bit_diff_5bit_exor=me_block_create(curr_img, prev_img, 16, 16);
    auto me_block_4bit_diff_4bit_exor=me_block_create(curr_img, prev_img, 16, 16);
    auto me_block_5bit_diff_3bit_exor=me_block_create(curr_img, prev_img, 16, 16);
    auto me_block_6bit_diff_2bit_exor=me_block_create(curr_img, prev_img, 16, 16);
    img_destruct(curr_img);
    img_destruct(prev_img);

    fullsearch(me_block_1bit_diff,pe_1bit_diff                     );
    fullsearch(me_block_2bit_diff,pe_2bit_diff                     );
    fullsearch(me_block_3bit_diff,pe_3bit_diff                     );
    fullsearch(me_block_4bit_diff,pe_4bit_diff                     );
    fullsearch(me_block_5bit_diff,pe_5bit_diff                     );
    fullsearch(me_block_6bit_diff,pe_6bit_diff                     );
    fullsearch(me_block_7bit_diff,pe_7bit_diff                     );
    fullsearch(me_block_8bit_diff,pe_8bit_diff                     );
    fullsearch(me_block_2bit_diff_6bit_exor,pe_2bit_diff_6bit_exor );
    fullsearch(me_block_3bit_diff_5bit_exor,pe_3bit_diff_5bit_exor );
    fullsearch(me_block_4bit_diff_4bit_exor,pe_4bit_diff_4bit_exor );
    fullsearch(me_block_5bit_diff_3bit_exor,pe_5bit_diff_3bit_exor );
    fullsearch(me_block_6bit_diff_2bit_exor,pe_6bit_diff_2bit_exor );
    auto ave_pe_1bit_diff          =me_block_calc_average_cost(me_block_1bit_diff           );
    auto ave_pe_2bit_diff          =me_block_calc_average_cost(me_block_2bit_diff           );
    auto ave_pe_3bit_diff          =me_block_calc_average_cost(me_block_3bit_diff           );
    auto ave_pe_4bit_diff          =me_block_calc_average_cost(me_block_4bit_diff           );
    auto ave_pe_5bit_diff          =me_block_calc_average_cost(me_block_5bit_diff           );
    auto ave_pe_6bit_diff          =me_block_calc_average_cost(me_block_6bit_diff           );
    auto ave_pe_7bit_diff          =me_block_calc_average_cost(me_block_7bit_diff           );
    auto ave_pe_8bit_diff          =me_block_calc_average_cost(me_block_8bit_diff           );
    auto ave_pe_2bit_diff_6bit_exor=me_block_calc_average_cost(me_block_2bit_diff_6bit_exor );
    auto ave_pe_3bit_diff_5bit_exor=me_block_calc_average_cost(me_block_3bit_diff_5bit_exor );
    auto ave_pe_4bit_diff_4bit_exor=me_block_calc_average_cost(me_block_4bit_diff_4bit_exor );
    auto ave_pe_5bit_diff_3bit_exor=me_block_calc_average_cost(me_block_5bit_diff_3bit_exor );
    auto ave_pe_6bit_diff_2bit_exor=me_block_calc_average_cost(me_block_6bit_diff_2bit_exor );

    FILE *fp_out_csv=fopen(argv[3], "w");
    if(NULL==fp_out_csv)
    {
        fprintf(stderr, "%s:%d cannot open %s\n", __FILE__, __LINE__ , argv[3]);
        exit(1);
    }

    fprintf(fp_out_csv, "%s,%.1f sec\n", argv[1], (double)(clock()-start)/CLOCKS_PER_SEC);
    fprintf(fp_out_csv, ",1bit_diff,%f,,2bit_diff,%f,,3bit_diff,%f,,4bit_diff,%f,,5bit_diff,%f,,6bit_diff,%f,,7bit_diff,%f,,8bit_diff,%f,,2bit_diff_6bit_exor,%f,,3bit_diff_5bit_exor,%f,,4bit_diff_4bit_exor,%f,,5bit_diff_3bit_exor,%f,,6bit_diff_2bit_exor,%f,\n",
            ave_pe_1bit_diff, ave_pe_2bit_diff, ave_pe_3bit_diff, ave_pe_4bit_diff, ave_pe_5bit_diff, ave_pe_6bit_diff, ave_pe_7bit_diff, ave_pe_8bit_diff,
            ave_pe_2bit_diff_6bit_exor, ave_pe_3bit_diff_5bit_exor, ave_pe_4bit_diff_4bit_exor, ave_pe_5bit_diff_3bit_exor, ave_pe_6bit_diff_2bit_exor);
    fprintf(fp_out_csv, "\"(w,h)\",mv_w,mv_h,mv_cost,mv_w,mv_h,mv_cost,mv_w,mv_h,mv_cost,mv_w,mv_h,mv_cost,mv_w,mv_h,mv_cost,mv_w,mv_h,mv_cost,mv_w,mv_h,mv_cost,mv_w,mv_h,mv_cost,mv_w,mv_h,mv_cost,mv_w,mv_h,mv_cost,mv_w,mv_h,mv_cost,mv_w,mv_h,mv_cost,mv_w,mv_h,mv_cost,\n");

    for(int h=0;h<me_block_1bit_diff->mvec_table->ht;h++)
    {
        for(int w=0;w<me_block_1bit_diff->mvec_table->wt;w++)
        {
            fprintf(fp_out_csv, "\"(%d, %d)\",",w,h);
            fprintf(fp_out_csv, "%d,%d,%d,",me_block_1bit_diff->mvec_table->data[h][w].w,          me_block_1bit_diff->mvec_table->data[h][w].h          ,me_block_1bit_diff->mvec_table->data[h][w].cost          );
            fprintf(fp_out_csv, "%d,%d,%d,",me_block_2bit_diff->mvec_table->data[h][w].w,          me_block_2bit_diff->mvec_table->data[h][w].h          ,me_block_2bit_diff->mvec_table->data[h][w].cost          );
            fprintf(fp_out_csv, "%d,%d,%d,",me_block_3bit_diff->mvec_table->data[h][w].w,          me_block_3bit_diff->mvec_table->data[h][w].h          ,me_block_3bit_diff->mvec_table->data[h][w].cost          );
            fprintf(fp_out_csv, "%d,%d,%d,",me_block_4bit_diff->mvec_table->data[h][w].w,          me_block_4bit_diff->mvec_table->data[h][w].h          ,me_block_4bit_diff->mvec_table->data[h][w].cost          );
            fprintf(fp_out_csv, "%d,%d,%d,",me_block_5bit_diff->mvec_table->data[h][w].w,          me_block_5bit_diff->mvec_table->data[h][w].h          ,me_block_5bit_diff->mvec_table->data[h][w].cost          );
            fprintf(fp_out_csv, "%d,%d,%d,",me_block_6bit_diff->mvec_table->data[h][w].w,          me_block_6bit_diff->mvec_table->data[h][w].h          ,me_block_6bit_diff->mvec_table->data[h][w].cost          );
            fprintf(fp_out_csv, "%d,%d,%d,",me_block_7bit_diff->mvec_table->data[h][w].w,          me_block_7bit_diff->mvec_table->data[h][w].h          ,me_block_7bit_diff->mvec_table->data[h][w].cost          );
            fprintf(fp_out_csv, "%d,%d,%d,",me_block_8bit_diff->mvec_table->data[h][w].w,          me_block_8bit_diff->mvec_table->data[h][w].h          ,me_block_8bit_diff->mvec_table->data[h][w].cost          );
            fprintf(fp_out_csv, "%d,%d,%d,",me_block_2bit_diff_6bit_exor->mvec_table->data[h][w].w,me_block_2bit_diff_6bit_exor->mvec_table->data[h][w].h,me_block_2bit_diff_6bit_exor->mvec_table->data[h][w].cost);
            fprintf(fp_out_csv, "%d,%d,%d,",me_block_3bit_diff_5bit_exor->mvec_table->data[h][w].w,me_block_3bit_diff_5bit_exor->mvec_table->data[h][w].h,me_block_3bit_diff_5bit_exor->mvec_table->data[h][w].cost);
            fprintf(fp_out_csv, "%d,%d,%d,",me_block_4bit_diff_4bit_exor->mvec_table->data[h][w].w,me_block_4bit_diff_4bit_exor->mvec_table->data[h][w].h,me_block_4bit_diff_4bit_exor->mvec_table->data[h][w].cost);
            fprintf(fp_out_csv, "%d,%d,%d,",me_block_5bit_diff_3bit_exor->mvec_table->data[h][w].w,me_block_5bit_diff_3bit_exor->mvec_table->data[h][w].h,me_block_5bit_diff_3bit_exor->mvec_table->data[h][w].cost);
            fprintf(fp_out_csv, "%d,%d,%d,",me_block_6bit_diff_2bit_exor->mvec_table->data[h][w].w,me_block_6bit_diff_2bit_exor->mvec_table->data[h][w].h,me_block_6bit_diff_2bit_exor->mvec_table->data[h][w].cost);
            fprintf(fp_out_csv, "\n");
        }
    }

    fclose(fp_out_csv);

    me_block_destruct(me_block_1bit_diff);
    me_block_destruct(me_block_2bit_diff);
    me_block_destruct(me_block_3bit_diff);
    me_block_destruct(me_block_4bit_diff);
    me_block_destruct(me_block_5bit_diff);
    me_block_destruct(me_block_6bit_diff);
    me_block_destruct(me_block_7bit_diff);
    me_block_destruct(me_block_8bit_diff);
    me_block_destruct(me_block_2bit_diff_6bit_exor);
    me_block_destruct(me_block_3bit_diff_5bit_exor);
    me_block_destruct(me_block_4bit_diff_4bit_exor);
    me_block_destruct(me_block_5bit_diff_3bit_exor);
    me_block_destruct(me_block_6bit_diff_2bit_exor);

    return 0;
}
