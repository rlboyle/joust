#pragma once
#include "ge211.hxx"
#include "game_config.hxx"
#include "ostrich.hxx"

class Egg : public Knight {

public:

    int radius;

    ge211::Rect<double> bounding_box;

    bool show;

    void go_to(ge211::Posn<double>);

    Egg(ge211::Posn<double>, Game_config);

    void move() override;

    bool hits_ostrich(Ostrich&);

    bool time_to_hatch(double);

private:

    void add_to_score(Ostrich&);



    double time_alive;


};