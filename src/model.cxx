#include "model.hxx"
#include <iostream>



Model::Model()
    : config_(),
      buzzard0({double(config_.window_dimensions.width), 150}, config_, 400, 1.5),
      buzzard1({double(config_.window_dimensions.width), 150}, config_, 50, -1.5),
      buzzard2({double(config_.window_dimensions.width), 500}, config_, 650, 1.5),
      buzzard3({double(config_.window_dimensions.width), 400}, config_, 100, -1.5),
      egg0({0,0}, config_),
      egg1({0,0}, config_),
      egg2({0,0}, config_),
      egg3({0,0}, config_),
      ost_move_dir(Facing::left),
      side_key_pressed(false),
      ostrich_({0,0}, config_),
      counter(0),
      spawn_point(0,2),
      first_frame(true)
{
    // initialize platform rectangles
    make_platforms();

    // add buzzard addresses to vector of pointers to buzzards
    buzzards.push_back(&buzzard0);
    buzzards.push_back(&buzzard1);
    buzzards.push_back(&buzzard2);
    buzzards.push_back(&buzzard3);

    // add egg addresses to vector of pointers
    eggs.push_back(&egg0);
    eggs.push_back(&egg1);
    eggs.push_back(&egg2);
    eggs.push_back(&egg3);

    pair0 = {&egg0, &buzzard0};
    pair1 = {&egg1, &buzzard1};
    pair2 = {&egg2, &buzzard2};
    pair3 = {&egg3, &buzzard3};

    pairs.push_back(&pair0);
    pairs.push_back(&pair1);
    pairs.push_back(&pair2);
    pairs.push_back(&pair3);

}

void
Model::on_frame(double dt)
{


    counter++;

    if (wave_over()) {
        buzzard0 = Buzzard({double(config_.window_dimensions.width), 150}, config_, 400, 1.5);
        buzzard1 = Buzzard({double(config_.window_dimensions.width), 150}, config_, 50, -1.5);
        buzzard2 = Buzzard({double(config_.window_dimensions.width), 500}, config_, 650, 1.5);
        buzzard3 = Buzzard({double(config_.window_dimensions.width), 400}, config_, 100, -1.5);

    }

    if (first_frame) {
        ostrich_respawn();
        first_frame = false;
    }


    if (!ostrich_.alive) {
        if (ostrich_.lives > 0) {
            if(ostrich_.on_death(dt)) {
                ostrich_respawn();
                ostrich_.time_dead = 0;
                ostrich_.lives -= 1;
            }
        }
    }

    if (counter % 3 == 0) {
        ostrich_.flapping = false;
    }

    // advance ostrich position
    ostrich_.move();

    // ostriches bounce off of the top of the screen and wrap around the sides
    ostrich_.wrap_and_bounce();

    // slide on top of platforms, bounce off sides and bottom
    for (Platform plat : platforms) {
        ostrich_.handle_collisions(plat);
        if (ostrich_.hits_sprite(plat) && ostrich_.on_platform(plat) && side_key_pressed) {
            change_ostrich_velocity_x(true);
        }
    }

    if (ostrich_.initial_movement) {
        // loop iterates through all buzzards and eggs in model
        for (Pair *pair: pairs) {

            pair->buzzard->flapping = false;

            // if both the ostrich and buzzard are both alive
            if (ostrich_.alive && pair->buzzard->alive) {

                // check for collision and handle appropriately
                ostrich_.handle_buzzard_collisions(*pair->buzzard);

                // if buzzard is dead
                if (!pair->buzzard->alive) {

                    // egg appears at buzzard's location after it dies
                    pair->egg
                        ->go_to({pair->buzzard->posn.x + (config_.knight_size.width / 2), pair->buzzard->posn.y + (config_.knight_size.height / 2)});

                    // egg continues with buzzard's velocity
                    pair->egg->velocity = pair->buzzard->velocity;

                    // display egg on screen
                    pair->egg->show = true;
                }
            }

            // for (Pair* second_pair : pairs) {
            //     if (!(second_pair == pair)) {
            //         pair->buzzard->handle_buzzard_collisions(*second_pair->buzzard);
            //     }
            // }

            // choose target y-position
            pair->buzzard->choose_targets(ostrich_.posn.y);

            // flap buzzard wings as needed to achieve target y-position,
            // adjust x-velocity according to acceleration
            pair->buzzard->buzzard_change_vel();

            // wrap buzzards on sides of screen and bounce off top
            pair->buzzard->wrap_and_bounce();

            // for each platform in model
            for (Platform plat: platforms) {

                // if buzzard hits platform but not on top
                if (pair->buzzard->hits_sprite(plat) && !pair->buzzard->on_platform(plat)) {

                    // switch x-direction of velocity
                    pair->buzzard->target_xvel *= -1;

                    // adjust target y-position to current location of ostrich
                    pair->buzzard->target_yposn = ostrich_.posn.y;

                }
            }

            // assign current y-velocity to variable
            double yvel = pair->buzzard->velocity.height;

            // for all platforms in model
            for (Platform plat: platforms) {

                // // slide on top of platforms, bounce off sides and bottom
                pair->buzzard->handle_collisions(plat);

                // prevent buzzards from getting stuck on top of platforms (allow them to fly upwards)
                if (pair->buzzard->hits_sprite(plat) && pair->buzzard->on_platform(plat) && yvel < 0) {
                    pair->buzzard->velocity.height = yvel;
                }
            }

            // adjust buzzard location
            pair->buzzard->move();

            pair->buzzard->face();

            // wrap and bounce egg
            pair->egg->wrap_and_bounce();

            // slide on top of platforms, bounce off sides and bottom
            for (Platform plat: platforms) {
                pair->egg->handle_collisions(plat);
            }

            // adjust egg position
            pair->egg->move();

            // handle ostrich collisions
            pair->egg->hits_ostrich(ostrich_);

            if (pair->egg->show && pair->egg->time_to_hatch(dt)) {
                pair->buzzard->posn = pair->egg->posn;
                pair->buzzard->posn.x += config_.knight_size.width / 2;
                pair->buzzard->posn.y -= config_.knight_size.height / 2;
                pair->egg->show = false;
                pair->buzzard->alive = true;
                pair->buzzard->target_yposn = 600;
            }

        }
    }

}

// return private member ostrich
Ostrich
Model::ostrich() const
{
    return ostrich_;
}

// respond to keyboard input
void
Model::change_ostrich_velocity_x(bool on_plat)
{
    // given a direction, adjust x-velocity accordingly
    ostrich_.facing = ost_move_dir;
    ostrich_.initial_movement = true;
    double vel_change;
    if (on_plat) {
        vel_change = config_.ostrich_plat_accelx;
    } else {
        vel_change = config_.ostrich_flap_accelx;
    }

    if (ost_move_dir == Facing::right && ostrich_.velocity.width < config_.max_knight_velocity.width) {
        ostrich_.velocity.width += vel_change;
    }
    else if (ost_move_dir == Facing::left && ostrich_.velocity.width > (0 - config_.max_knight_velocity.width)) {
        ostrich_.velocity.width -= vel_change;
    }
}

void
Model::ostrich_respawn()
{
    int spawn_int = spawn_point.next();
    if (spawn_int == 0) {
        ostrich_.posn = {500, double(config_.window_dimensions.height - config_.plat_height - config_.knight_size.height)};
    } else if (spawn_int == 1) {
        ostrich_.posn = {500, 500-config_.knight_size.height};
    } else if (spawn_int == 2) {
        ostrich_.posn = {100, 200-config_.knight_size.height};
    }
    ostrich_.alive = true;
    ostrich_.velocity = {0,0};
}

// flap wings
void
Model::ostrich_flap()
{
    ostrich_.initial_movement = true;
    ostrich_.flap();
    counter = 0;
    if (side_key_pressed) {
        change_ostrich_velocity_x(false);
    }
}

// initialize platforms
void
Model::make_platforms()
{

    // make rectangle
    Platform platform0 = Platform::from_top_left({0, double(config_.window_dimensions.height-10)},{double(config_.window_dimensions.width), config_.plat_height});

    // add to vector
    platforms.push_back(platform0);

    // repeat
    Platform platform1 = Platform::from_top_left({400, 500},{200, config_.plat_height});
    platforms.push_back(platform1);

    Platform platform2 = Platform::from_top_left({0, 200}, {300, config_.plat_height});
    platforms.push_back(platform2);

    Platform platform3 = Platform::from_top_right({double(config_.window_dimensions.width), 200}, {300, config_.plat_height});
    platforms.push_back(platform3);

}

bool
Model::wave_over()
{
    if (buzzard0.alive) {
        return false;
    }
    if (buzzard1.alive) {
        return false;
    }
    if (buzzard2.alive) {
        return false;
    }
    if (buzzard3.alive) {
        return false;
    }
    if (egg0.show) {
        return false;
    }
    if (egg1.show) {
        return false;
    }
    if (egg2.show) {
        return false;
    }
    if (egg3.show) {
        return false;
    }

    return true;

}

void
Model::ostrich_face(Facing dir)
{
    ostrich_.facing = dir;
}