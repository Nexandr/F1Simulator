#ifndef TEAM_H
#define TEAM_H

#include <string>

struct team {
  std::string long_team_name;
  std::string team_name;

  // staff_list (TBD)

  // engineering department
  double staff_aero;
  double staff_power;
  double staff_chassis;
  // strategy department
  double staff_strategy;
  double staff_pitcrew;

  // performance
  double mech_aero;
  double mech_power;
  double mech_chassis;
  double reliability;

  // runtime mechanics
  double net_aero() const {
    return (0.8*mech_aero+0.2*staff_aero);
  }
  double net_power() const {
    return (0.8*mech_power+0.2*staff_power);
  }
  double net_chassis() const {
    return (0.8*mech_chassis+0.2*staff_chassis);
  }
};
#endif