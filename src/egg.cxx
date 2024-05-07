#include "egg.hxx"
#include <iostream>


Egg::Egg(ge211::Posn<double> pos, Game_config config)
    : Knight(pos, config),
      radius(10),
      bounding_box({posn.x-radius, posn.y-radius, double(2*radius), double(2*radius)}),
      show(false),
      time_alive(0)
{
    size.width = double(radius*2);
    size.height = double(radius*2);
}

void
Egg::go_to(ge211::Posn<double> pos)
{

    posn = pos;
    bounding_box.x = pos.x - radius;
    bounding_box.y = pos.y - radius;

}

void
Egg::move()
{
    posn.x += velocity.width;
    posn.y += velocity.height;

    if (velocity.height < config_.max_knight_velocity.height) {
        velocity.height += config_.acceleration;
    }

    if (velocity.height >= -1 && velocity.height <= 1) {
        velocity.width *= 0.99;
    }

    bounding_box.x = posn.x - radius;
    bounding_box.y = posn.y - radius;

}

bool
Egg::hits_ostrich(Ostrich& ostrich)
{
    ge211::Rect<double> ostrich_box = ge211::Rect<double>::from_top_left(ostrich.posn, ostrich.size);
    if (hits_sprite(ostrich_box) && ostrich.alive && show) {
        show = false;
        add_to_score(ostrich);
        return true;
    }

    return false;

}

void
Egg::add_to_score(Ostrich& ostrich)
{

    ostrich.eggs_collected += 1;

    if (ostrich.eggs_collected == 1) {
        ostrich.score += 250;
    } else if (ostrich.eggs_collected == 2) {
        ostrich.score += 500;
    } else if (ostrich.eggs_collected == 3) {
        ostrich.score += 750;
    } else {
        ostrich.score += 1000;
    }

}

bool
Egg::time_to_hatch(double dt)
{
    time_alive += dt;
    if (time_alive >= 15) {
        time_alive = 0;
        return true;
    }
    return false;
}