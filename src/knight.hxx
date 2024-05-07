#pragma once
#include "ge211.hxx"
#include "game_config.hxx"



/// A direction: either Facing::right or Facing::left
enum class Facing {
    right,
    left,
};

class Knight {
public:
    /// X and Y velocity vector of the knight
    ge211::Dims<double> velocity;

    /// Dimensions of the knight's bounding box. Used for collision detection
    ge211::Dims<double> size;

    /// Position of the knight on the screen
    ge211::Posn<double> posn;

    /// direction the knight is facing. Either Facing::right or Facing::left
    Facing facing = Facing::left;

    // Constructors and Methods

    Knight(ge211::Posn<double>, Game_config const&);

    void flap();

    void wrap_and_bounce();

    bool on_platform(ge211::Rect<double>);

    bool hits_sprite(ge211::Rect<double>);

    bool hits_side(ge211::Rect<double> platform);

    bool hits_bottom(ge211::Rect<double>);

    void handle_collisions(ge211::Rect<double>);

    virtual void move();

    bool alive;

    bool flapping;

protected:
    Game_config config_;

    double flap_accel;

};