#ifndef DRIVER_H
#define DRIVER_H

#include "team.h"
#include <string>

struct driver {
  // identity attributes
  std::string name;
  std::string abbreviation;
  std::string team_name;
  const team *car = nullptr;

  // skill attributes
  int cornering;
  int one_lap_pace;
  int overtaking_defending;
  int spatial_awareness;
  int reaction_time;
  int wet_weather;
  int g_force_tolerance;
  int feedback_setup;
  int composure;
  int tyre_saving;
  int system_management;

  // race dynamic attributes
  int current_race_position;
  double tyre_wear = 0.0;
  int pitstops = 0;
  double time_in_pits = 0.0;
  bool is_dnf = false;

  // calculation functions
  double racecraft_index();
  double strategic_index();
  double tyre_management();
  void degrade_tyres();
};
#endif