#include "../headers/resource_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>


static std::string clean(const std::string& s) {
    std::string result = s;
    if (!result.empty() && result.back() == '\r') result.pop_back();
    return result;
}

static std::vector<std::string> split_csv(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string cell;
    while (std::getline(ss, cell, ','))
        fields.push_back(clean(cell));
    return fields;
}

resource_loader::resource_loader(const std::string& drivers_csv,
                                 const std::string& teams_csv,
                                 const std::string& calendar_csv) {
    reload(drivers_csv, teams_csv, calendar_csv);
}

void resource_loader::reload(const std::string& drivers_csv,
                             const std::string& teams_csv,
                             const std::string& calendar_csv) {
    master_grid.clear();
    master_teams.clear();
    master_calendar.clear();

    std::string line;

    //teams
    std::ifstream teams_file(teams_csv);
    if(!teams_file.is_open()){
        throw std::runtime_error("Failed to open teams data.");
        return;
    }
    std::getline(teams_file, line);
    while(std::getline(teams_file, line)){
        if(line.empty()) continue;
        auto fields=split_csv(line);
        if(fields.size()<11) continue;

        team t;
        t.long_team_name=fields[0];
        t.team_name=fields[1];
        t.staff_aero=std::stod(fields[2]);
        t.staff_power=std::stod(fields[3]);
        t.staff_chassis=std::stod(fields[4]);
        t.staff_strategy=std::stod(fields[5]);
        t.staff_pitcrew=std::stod(fields[6]);
        t.mech_aero=std::stod(fields[7]);
        t.mech_power=std::stod(fields[8]);
        t.mech_chassis=std::stod(fields[9]);
        t.reliability=std::stod(fields[10]);
        master_teams.push_back(t);
    }
    teams_file.close();

    //drivers
    std::ifstream drivers_file(drivers_csv);
    if(!drivers_file.is_open()){
        throw std::runtime_error("Could not open drivers data.");
        return;
    }
    std::getline(drivers_file, line);
    while(std::getline(drivers_file, line)){
        if(line.empty()) continue;
        auto fields=split_csv(line);
        if(fields.size()<14) continue;

        driver d;
        d.name=fields[0];
        d.abbreviation=fields[1];
        d.team_name=fields[2];
        d.cornering=std::stoi(fields[3]);
        d.one_lap_pace=std::stoi(fields[4]);
        d.overtaking_defending=std::stoi(fields[5]);
        d.spatial_awareness=std::stoi(fields[6]);
        d.reaction_time=std::stoi(fields[7]);
        d.wet_weather=std::stoi(fields[8]);
        d.g_force_tolerance=std::stoi(fields[9]);
        d.feedback_setup=std::stoi(fields[10]);
        d.composure=std::stoi(fields[11]);
        d.tyre_saving=std::stoi(fields[12]);
        d.system_management=std::stoi(fields[13]);

        for(const auto& curr_team:master_teams){
            if(curr_team.team_name==d.team_name){
                d.car=&curr_team;
                break;
            }
        }
        if(d.car==nullptr){
            throw std::runtime_error("Driver "+d.name+" not assigned seat.");
        }
        master_grid.push_back(d);
    }
    drivers_file.close();

    //tracklist
    std::ifstream tracklist(calendar_csv);
    if(!tracklist.is_open()){
        throw std::runtime_error("Could not open track data.");
        return;
    }
    std::getline(tracklist, line);
    while(std::getline(tracklist,line)){
        if(line.empty()) continue;
        auto fields=split_csv(line);
        if(fields.size()<11) continue;

        track tk;
        tk.name=fields[1];
        tk.circuit_name=fields[2];
        tk.laps=std::stoi(fields[3]);
        tk.track_type=fields[4];
        tk.overtaking_ease=std::stoi(fields[5]);
        tk.tyre_wear_multiplier=std::stod(fields[6]);
        tk.avg_temp=std::stod(fields[7]);
        tk.track_degradation=std::stod(fields[8]);
        tk.base_lap_time=std::stod(fields[9]);
        tk.rain_probability=std::stod(fields[10]);
        tk.hard_compound_tier=1;
        master_calendar.push_back(tk);
    }
    tracklist.close();
}
