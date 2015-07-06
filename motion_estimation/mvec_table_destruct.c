#include "include/motion_estimation.h"

void mvec_table_destruct(struct mvec_table_t *mv_table)
{
    free(mv_table->data[0]);
    free(mv_table->data);
    free(mv_table);
}
