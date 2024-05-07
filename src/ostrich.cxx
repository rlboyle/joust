#include "ostrich.hxx"
#include <iostream>



Ostrich::Ostrich(ge211::Posn<double> pos, Game_config const& config)
    : Knight(pos, config),
      score(0),
      eggs_collected(0),
      lives(4),
      time_dead(0),
      initial_movement(false)
{
    flap_accel = -config_.ostrich_flap_accely;
}

void
Ostrich::handle_buzzard_collisions(Buzzard& buzzard)
{
    ge211::Rect<double> buzzard_rect = {buzzard.posn.x,buzzard.posn.y, buzzard.size.width, buzzard.size.height};
    ge211::Rect<double> ostrich_rect = {posn.x, posn.y, size.width, size.height};

    if (hits_sprite(buzzard_rect)) {

        if (ostrich_rect.center().y < buzzard_rect.center().y+3 && ostrich_rect.center().y > buzzard_rect.center().y-3) {
            if (ostrich_rect.top_left().x < buzzard_rect.top_left().x) {
                velocity.width = -2;
                buzzard.velocity.width = 1.5;
            } else {
                velocity.width = 2;
                buzzard.velocity.width = -1.5;
            }

        } else if (ostrich_rect.center().y > buzzard_rect.center().y) {
                alive = false;
                buzzard.velocity.width *= -1;

        } else if (ostrich_rect.center().y < buzzard_rect.center().y) {
            buzzard.alive = false;
            velocity.width *= -1;
            score += 500;


        }

    }

}

bool Ostrich::on_death(double dt)
{
    time_dead += dt;
    if (time_dead >= 1) {
        return true;
    }
    else {
        return false;
    }
}
