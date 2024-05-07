#pragma once

#include "ge211.hxx"

class Game_config {
public:
    Game_config();
    ge211::Dims<int> window_dimensions;
    ge211::Dims<double> max_knight_velocity;
    double bounce_vel;
    double acceleration;
    double plat_height;
    ge211::Dims<double> knight_size;
    double ostrich_flap_accely;
    double ostrich_flap_accelx;
    double ostrich_plat_accelx;
};