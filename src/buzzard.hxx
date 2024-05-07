#pragma once
#include "knight.hxx"
#include <vector>


class Buzzard : public Knight{
public:

    Buzzard(ge211::Posn<double>, Game_config const&, double, double);

    void choose_targets(double);

    void buzzard_change_vel();

    double target_xvel;

    double target_yposn;

    void face();

    size_t counter;

};