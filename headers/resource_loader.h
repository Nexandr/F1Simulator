#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <string>
#include <vector>
#include "sim_engine.h"
#include "driver.h"
#include "team.h"

struct resource_loader {
    std::vector<team>   master_teams;
    std::vector<driver> master_grid;
    std::vector<track>  master_calendar;

    resource_loader(const std::string& drivers_csv,
                    const std::string& teams_csv,
                    const std::string& calendar_csv);
    void reload(const std::string& drivers_csv,
                const std::string& teams_csv,
                const std::string& calendar_csv);
};

#endif
