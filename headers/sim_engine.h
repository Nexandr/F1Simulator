#ifndef SIM_ENGINE_H
#define SIM_ENGINE_H

#include <string>
#include <vector>
#include "driver.h"

struct track {
  std::string name;
  std::string circuit_name;
  int laps;
  std::string track_type;
  int overtaking_ease;
  double tyre_wear_multiplier;
  double avg_temp;
  double track_degradation;
  double base_lap_time;
  double rain_probability;
  int hard_compound_tier;
};
struct sim_engine {
private:
  std::vector<driver>& grid;
  int total_laps;
  int current_lap;
  track current_track;

public:
  sim_engine(const track& active_track,std::vector<driver>& working_grid);

  void run_qualifying();
  void run_race();
};
#endif