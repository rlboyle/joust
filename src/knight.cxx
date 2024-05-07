#include "knight.hxx"
#include <iostream>

Knight::Knight(ge211::Posn<double> pos, Game_config const& config)
        : velocity({0, 0}),
          size(config.knight_size),
          posn(pos),
          facing(Facing::right),
          alive(true),
          flapping(false),
          config_(config),
          flap_accel(0)


{ }

void
Knight::flap()
{
    velocity.height += flap_accel;
    flapping = true;
}

void
Knight::wrap_and_bounce()
{
    if (posn.x > config_.window_dimensions.width) {
        posn.x = 0;
    } else if (posn.x + size.width < 0) {
        posn.x = config_.window_dimensions.width;
    }

    if (posn.y < 0) {
        velocity.height = config_.bounce_vel;
    }
}

bool
Knight::on_platform(ge211::Rect<double> platform)
{
    int bottom = posn.y + size.height;

    if (bottom <= platform.y) {
        return false;
    }
    if (bottom > platform.y + 2) {
        return false;
    }
    return true;
}

bool
Knight::hits_sprite(ge211::Rect<double> platform)
{

    float top = posn.y;
    float bottom = posn.y+size.height;
    float left = posn.x;
    float right = posn.x + size.width;
    if (right < platform.top_left().x || left > platform.top_right().x) {
        return false;
    }
    else if (bottom < platform.top_left().y || top > platform.bottom_left().y) {
        return false;
    }
    return true;

}

bool
Knight::hits_side(ge211::Rect<double> platform)
{
    float left = posn.x;
    float right = posn.x + size.width;

    if (right > platform.top_left().x && right < platform.top_left().x + 4) {
        return true;
    } else if (left < platform.top_right().x && left > platform.top_right().x - 4) {
        return true;
    }

    return false;

}

bool
Knight::hits_bottom(ge211::Rect<double> platform)
{
    int top = posn.y;

    if (top >= platform.bottom_right().y) {
        return false;
    }
    if (top < platform.bottom_right().y - 4) {
        return false;
    }

    return true;

}

void
Knight::handle_collisions(ge211::Rect<double> platform)
{
    if (hits_sprite(platform)) {

            if (on_platform(platform)) {
                velocity.height = 0;
            } else if (hits_bottom(platform)) {
                velocity.height = config_.bounce_vel;
            } else if (velocity.width != 0 && hits_side(platform)) {
                velocity.width *= -1;
            }

    }
}

void
Knight::move()
{
    posn.x += velocity.width;
    posn.y += velocity.height;

    if (velocity.height < config_.max_knight_velocity.height) {
        velocity.height += config_.acceleration;
    }
}

