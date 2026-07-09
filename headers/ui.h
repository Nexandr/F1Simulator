#ifndef UI_H
#define UI_H

#include <vector>
#include "driver.h"
#include "sim_engine.h"

struct ui {
    //util
    static void clear_screen();
    static void sleep_ms(int milliseconds);

    //renderers
    static void display_timing_screen(const std::vector<driver>& grid, int lap, const track& current_track);
    static void display_final_results(const std::vector<driver>& grid, const track& current_track);
};
#endif