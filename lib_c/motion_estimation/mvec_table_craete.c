#include "include/motion_estimation.h"

struct mvec_table_t *mvec_table_craete(int ht, int wt)
{
    int h,w;
    struct mvec_table_t *new_table;
    new_table=(struct mvec_table_t *)malloc(sizeof(struct mvec_table_t));

    new_table->ht=ht;
    new_table->wt=wt;

    new_table->data=(struct mvec_t **)malloc(sizeof(struct mvec_t *)*ht);
    new_table->data[0]=(struct mvec_t *)malloc(sizeof(struct mvec_t)*ht*wt);

    for(h=1;h<ht;h++)
    {
        new_table->data[h]=new_table->data[h-1]+wt;
    }

    for(h=0;h<ht;h++)
    {
        for(w=0;w<wt;w++)
        {
            new_table->data[h][w].h=0;
            new_table->data[h][w].w=0;
            new_table->data[h][w].cost=-1;
            new_table->data[h][w].cost_match=-1;
            new_table->data[h][w].cost_edge=-1;
        }
    }

    return new_table;
}
