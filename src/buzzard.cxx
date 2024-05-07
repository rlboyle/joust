#include "buzzard.hxx"
#include "ge211.hxx"
#include <iostream>


Buzzard::Buzzard(ge211::Posn<double> pos, Game_config const& config, double init_ytarg, double init_xtarg)
    : Knight(pos, config),
      target_xvel(init_xtarg),
      target_yposn(init_ytarg)
{
    flap_accel = -0.7;
}

void
Buzzard::buzzard_change_vel()
{
    counter++;

    if (counter % 3 == 0) {
        flapping = false;
    }

    if (target_xvel < velocity.width) {
        velocity.width -= config_.acceleration;

    } else if (target_xvel > velocity.width) {
        velocity.width += config_.acceleration;
    }

    if (target_yposn < posn.y && counter % 6 == 0) {
        flap();
        counter = 0;
    }

}

void
Buzzard::choose_targets(double target)
{
    if (posn.y >= target_yposn - 20 && posn.y <= target_yposn + 20) {
        target_yposn = target;
    }
}

void
Buzzard::face()
{
    if (velocity.width > 0) {
        facing = Facing::right;
    } else if (velocity.width < 0) {
        facing = Facing::left;
    }
}

// void
// Buzzard::handle_buzzard_collisions(Buzzard buzz)
// {
//     ge211::Rect<double> buzz_rect = {buzz.posn.x, buzz.posn.y, buzz.size.width, buzz.size.height};
//
//     if (hits_sprite(buzz_rect)) {
//         velocity.width *= -1;
//         buzz.velocity.width *= -1;
//     }
// }