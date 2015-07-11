#include <stdlib.h>
#include <time.h>
#include "include/implab.h"
#include "include/motion_estimation.h"
#include "include/processor_element.h"

int main_video_process(int argc, char *argv[]);
int main_frame_process(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    return main_video_process(argc, argv);
}
