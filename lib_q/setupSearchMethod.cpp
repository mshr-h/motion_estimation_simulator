#include "include/mainwindow.h"

std::list<struct search_method_t> MainWindow::setupSearchMethod()
{
    std::list<struct search_method_t> sm_list;

    struct search_method_t sm;

    sm.func=fullsearch;
    sm.name="fullsearch";
    sm_list.push_back(sm);

    /*sm.func=fullsearch_4pix;
    sm.name="fullsearch_4pix";
    sm_list.push_back(sm);*/

    return sm_list;
}

