#include "include/mainwindow.h"

std::list<struct result_t> MainWindow::getResults(struct me_block_t *me_block, std::list<struct search_method_t> sm_list, std::list<struct processor_element_t> pe_list)
{
    std::list<struct result_t> resultlist;

    auto it_sm = sm_list.begin();
    while(it_sm!=sm_list.end())
    {
        struct search_method_t sm=*it_sm;

        auto it_pe = pe_list.begin();
        while(it_pe!=pe_list.end())
        {
            struct processor_element_t pe=*it_pe;
            struct result_t rslt;
            sm.func(me_block, pe.func);
            rslt.search_method=sm.name;
            rslt.pix_operation=pe.name;
            rslt.average_cost=me_block_calc_average_cost(me_block);
            resultlist.push_back(rslt);

            it_pe++;
        }

        it_sm++;
    }

    return resultlist;
}
