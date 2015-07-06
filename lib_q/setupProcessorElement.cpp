#include "include/mainwindow.h"

std::list<struct processor_element_t> MainWindow::setupProcessorElement()
{
    std::list<struct processor_element_t> pe_list;

    struct processor_element_t pe;

    pe.func=pe_1bit_diff;
    pe.name="1bit_diff";
    pe_list.push_back(pe);

    pe.func=pe_2bit_diff;
    pe.name="2bit_diff";
    pe_list.push_back(pe);

    pe.func=pe_3bit_diff;
    pe.name="3bit_diff";
    pe_list.push_back(pe);

    pe.func=pe_4bit_diff;
    pe.name="4bit_diff";
    pe_list.push_back(pe);

    pe.func=pe_5bit_diff;
    pe.name="5bit_diff";
    pe_list.push_back(pe);

    pe.func=pe_6bit_diff;
    pe.name="6bit_diff";
    pe_list.push_back(pe);

    pe.func=pe_7bit_diff;
    pe.name="7bit_diff";
    pe_list.push_back(pe);

    pe.func=pe_8bit_diff;
    pe.name="8bit_diff";
    pe_list.push_back(pe);

    pe.func=pe_2bit_diff_6bit_exor;
    pe.name="2bit_diff_6bit_exor";
    pe_list.push_back(pe);

    pe.func=pe_3bit_diff_5bit_exor;
    pe.name="3bit_diff_5bit_exor";
    pe_list.push_back(pe);

    pe.func=pe_4bit_diff_4bit_exor;
    pe.name="4bit_diff_4bit_exor";
    pe_list.push_back(pe);

    pe.func=pe_5bit_diff_3bit_exor;
    pe.name="5bit_diff_3bit_exor";
    pe_list.push_back(pe);

    pe.func=pe_6bit_diff_2bit_exor;
    pe.name="6bit_diff_2bit_exor";
    pe_list.push_back(pe);

    return pe_list;
}
