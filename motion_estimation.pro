CONFIG += c++11

HEADERS += \
    include/implab.h \
    include/motion_estimation.h \
    include/processor_element.h

SOURCES += \
    main.cpp \
    main_frame_process.cpp \
    main_video_process.cpp \
    lib_c/implab/img_copy.c \
    lib_c/implab/img_create.c \
    lib_c/implab/img_destruct.c \
    lib_c/implab/img_diff.c \
    lib_c/implab/img_rgb_create.c \
    lib_c/implab/img_rgb_destruct.c \
    lib_c/implab/img_rgb_to_yuv.c \
    lib_c/implab/img_yuv_create.c \
    lib_c/implab/img_yuv_destruct.c \
    lib_c/implab/Malloc2D_uchr.c \
    lib_c/implab/buf_to_img_yuv.c \
    lib_c/implab/img_yuv_to_buf.c \
    lib_c/implab/img_yuv_to_rgb.c \
    lib_c/motion_estimation/processor_element/pe_diff.c \
    lib_c/motion_estimation/processor_element/pe_diff_exor.c \
    lib_c/motion_estimation/fullsearch.c \
    lib_c/motion_estimation/fullsearch_4pix_only.c \
    lib_c/motion_estimation/me_block_calc_average_cost.c \
    lib_c/motion_estimation/me_block_create.c \
    lib_c/motion_estimation/me_block_destruct.c \
    lib_c/motion_estimation/me_block_reconstruct.c \
    lib_c/motion_estimation/mvec_table_craete.c \
    lib_c/motion_estimation/mvec_table_destruct.c
