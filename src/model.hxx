#pragma once

#include <ge211.hxx>
#include "ostrich.hxx"
#include "buzzard.hxx"
#include "knight.hxx"
#include "egg.hxx"
#include "game_config.hxx"
#include <vector>

struct Pair {
    Egg* egg;
    Buzzard* buzzard;
};

class Model
{
public:

    using Platform = ge211::Rect<double>;

    Model();

    void on_frame(double);

    Ostrich ostrich() const;

    void change_ostrich_velocity_x(bool);

    void ostrich_flap();

    void ostrich_respawn();

    void ostrich_face(Facing);

    Game_config config_;

    std::vector<Platform> platforms;

    std::vector<Pair*> pairs;

    std::vector<Buzzard*> buzzards;

    std::vector<Egg*> eggs;

    Buzzard buzzard0;
    Buzzard buzzard1;
    Buzzard buzzard2;
    Buzzard buzzard3;

    Egg egg0;
    Egg egg1;
    Egg egg2;
    Egg egg3;

    Pair pair0;
    Pair pair1;
    Pair pair2;
    Pair pair3;

    Facing ost_move_dir;

    bool side_key_pressed;

private:

    Ostrich ostrich_;

    void make_platforms();

    size_t counter;

    ge211::Random_source<int> spawn_point;

    bool first_frame;

    bool wave_over();

};
