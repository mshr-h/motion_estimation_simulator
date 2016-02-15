#include "include/motion_estimation.h"

struct mvec_t compare_SAD(struct mvec_t min_mvec, struct mvec_t cand_mvec)
{
    if(min_mvec.cost_sad > cand_mvec.cost_sad)
        return cand_mvec;
    return min_mvec;
}

struct mvec_t compare_SAD_matching(struct mvec_t min_mvec, struct mvec_t cand_mvec)
{
    if(min_mvec.cost_sad > cand_mvec.cost_sad)
        return cand_mvec;
    else if(min_mvec.cost_sad == cand_mvec.cost_sad)
    {
        if(min_mvec.cost_match < cand_mvec.cost_match)
            return cand_mvec;
    }
    return min_mvec;
}

struct mvec_t compare_SAD_minEdge(struct mvec_t min_mvec, struct mvec_t cand_mvec)
{
    if(min_mvec.cost_sad > cand_mvec.cost_sad)
        return cand_mvec;
    else if(min_mvec.cost_sad == cand_mvec.cost_sad)
    {
        if(min_mvec.cost_edge > cand_mvec.cost_edge)
            return cand_mvec;
    }
    return min_mvec;
}

struct mvec_t compare_SAD_maxEdge(struct mvec_t min_mvec, struct mvec_t cand_mvec)
{
    if(min_mvec.cost_sad > cand_mvec.cost_sad)
        return cand_mvec;
    else if(min_mvec.cost_sad == cand_mvec.cost_sad)
    {
        if(min_mvec.cost_edge < cand_mvec.cost_edge)
            return cand_mvec;
    }
    return min_mvec;
}
