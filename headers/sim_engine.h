#ifndef SIM_ENGINE_H
#define SIM_ENGINE_H

#include <string>
#include <vector>
#include "driver.h"
#include "team.h"

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
};
struct sim_engine {
private:
  std::vector<driver> grid;
  std::vector<team> team_registry;
  int total_laps;
  int current_lap;
  track current_track;

  void load(const std::string& drivers_csv, const std::string& teams_csv);

public:
  sim_engine(const track& active_track, int laps, const std::string& drivers_csv, const std::string& teams_csv);
  void run_qualifying();
  void run_race();
};
#endif