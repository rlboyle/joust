#pragma once
#include "knight.hxx"
#include "game_config.hxx"
#include "buzzard.hxx"

class Ostrich : public Knight {
public:

    Ostrich(ge211::Posn<double>, Game_config const&);

    void handle_buzzard_collisions(Buzzard&);

    size_t score;

    unsigned int eggs_collected;

    int lives;

    double time_dead;

    bool on_death(double);

    bool initial_movement;



};