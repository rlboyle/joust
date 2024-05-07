#include "view.hxx"
#include <iostream>

using Color = ge211::Color;
static Color platform_color = {0,200,0};
static Color egg_color = {200, 0, 200};
static Color score_color = {255,255,255};


View::View(Model const& model)
        : model_(model),
          window_dimensions_(model_.config_.window_dimensions),
          ostrich_("ostrich_no_flap.png"),
          ostrich_flap_("ostrich.png"),
          platform0_(model.platforms[0].dimensions().into<int>(), platform_color),
          platform1_(model.platforms[1].dimensions().into<int>(), platform_color),
          platform2_(model.platforms[2].dimensions().into<int>(), platform_color),
          platform3_(model.platforms[3].dimensions().into<int>(), platform_color),
          buzz0_("buzzard_no_flap.png"),
          buzz_flap("buzzard_flap.png"),
          egg0_(model_.egg0.radius, egg_color),
          sans({"sans.ttf",24}),
          score_sprite()

{}

void
View::draw(ge211::Sprite_set& set)
{
    set.add_sprite(platform0_, model_.platforms[0].top_left().into<int>(), 1);
    set.add_sprite(platform1_, model_.platforms[1].top_left().into<int>(), 1);
    set.add_sprite(platform2_, model_.platforms[2].top_left().into<int>(), 1);
    set.add_sprite(platform3_, model_.platforms[3].top_left().into<int>(), 1);

    if (model_.ostrich().alive) {

        if (!model_.ostrich().flapping) {
            if (model_.ostrich().facing == Facing::right) {
                ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.1);
                set.add_sprite(ostrich_, model_.ostrich().posn.into<int>(), 0, scale_and_flip);
            } else {
                ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.1).set_flip_h(true);
                set.add_sprite(ostrich_, model_.ostrich().posn.into<int>(), 0, scale_and_flip);
            }
        } else {
            if (model_.ostrich().facing == Facing::right) {
                ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.06);
                set.add_sprite(ostrich_flap_, model_.ostrich().posn.into<int>(), 0, scale_and_flip);
            } else {
                ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.06).set_flip_h(true);
                set.add_sprite(ostrich_flap_, model_.ostrich().posn.into<int>(), 0, scale_and_flip);
            }
        }
    }

    if (model_.ostrich().initial_movement) {

        if (model_.buzzard0.flapping) {
            if (model_.buzzard0.alive) {
                if (model_.buzzard0.facing == Facing::right) {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07);
                    set.add_sprite(buzz0_, model_.buzzard0.posn.into<int>(), 0, scale_and_flip);
                } else {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07).set_flip_h(true);
                    set.add_sprite(buzz0_, model_.buzzard0.posn.into<int>(), 0, scale_and_flip);
                }
            }
        } else {
            if (model_.buzzard0.alive) {
                if (model_.buzzard0.facing == Facing::right) {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07);
                    set.add_sprite(buzz_flap, model_.buzzard0.posn.into<int>(), 0, scale_and_flip);
                } else {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07).set_flip_h(true);
                    set.add_sprite(buzz_flap, model_.buzzard0.posn.into<int>(), 0, scale_and_flip);
                }
            }
        }

        if (model_.buzzard1.flapping) {
            if (model_.buzzard1.alive) {
                if (model_.buzzard1.facing == Facing::right) {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07);
                    set.add_sprite(buzz0_, model_.buzzard1.posn.into<int>(), 0, scale_and_flip);
                } else {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07).set_flip_h(true);
                    set.add_sprite(buzz0_, model_.buzzard1.posn.into<int>(), 0, scale_and_flip);
                }
            }
        } else {
            if (model_.buzzard1.alive) {
                if (model_.buzzard1.facing == Facing::right) {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07);
                    set.add_sprite(buzz_flap, model_.buzzard1.posn.into<int>(), 0, scale_and_flip);
                } else {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07).set_flip_h(true);
                    set.add_sprite(buzz_flap, model_.buzzard1.posn.into<int>(), 0, scale_and_flip);
                }
            }
        }

        if (model_.buzzard2.flapping) {
            if (model_.buzzard2.alive) {
                if (model_.buzzard2.facing == Facing::right) {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07);
                    set.add_sprite(buzz0_, model_.buzzard2.posn.into<int>(), 0, scale_and_flip);
                } else {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07).set_flip_h(true);
                    set.add_sprite(buzz0_, model_.buzzard2.posn.into<int>(), 0, scale_and_flip);
                }
            }
        } else {
            if (model_.buzzard2.alive) {
                if (model_.buzzard2.facing == Facing::right) {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07);
                    set.add_sprite(buzz_flap, model_.buzzard2.posn.into<int>(), 0, scale_and_flip);
                } else {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07).set_flip_h(true);
                    set.add_sprite(buzz_flap, model_.buzzard2.posn.into<int>(), 0, scale_and_flip);
                }
            }
        }

        if (model_.buzzard3.flapping) {
            if (model_.buzzard3.alive) {
                if (model_.buzzard3.facing == Facing::right) {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07);
                    set.add_sprite(buzz0_, model_.buzzard3.posn.into<int>(), 0, scale_and_flip);
                } else {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07).set_flip_h(true);
                    set.add_sprite(buzz0_, model_.buzzard3.posn.into<int>(), 0, scale_and_flip);
                }
            }
        } else {
            if (model_.buzzard3.alive) {
                if (model_.buzzard3.facing == Facing::right) {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07);
                    set.add_sprite(buzz_flap, model_.buzzard3.posn.into<int>(), 0, scale_and_flip);
                } else {
                    ge211::Transform scale_and_flip = ge211::Transform {}.set_scale(0.07).set_flip_h(true);
                    set.add_sprite(buzz_flap, model_.buzzard3.posn.into<int>(), 0, scale_and_flip);
                }
            }
        }
    }

    if (model_.egg0.show) {
        set.add_sprite(egg0_, model_.egg0.bounding_box.center().into<int>());
    }

    if (model_.egg1.show) {
        set.add_sprite(egg0_, model_.egg1.bounding_box.center().into<int>());
    }

    if (model_.egg2.show) {
        set.add_sprite(egg0_, model_.egg2.bounding_box.center().into<int>());
    }

    if (model_.egg3.show) {
        set.add_sprite(egg0_, model_.egg3.bounding_box.center().into<int>());
    }

    ge211::Text_sprite::Builder score_builder(sans);
    score_builder.color(score_color);
    score_builder << "SCORE: " << model_.ostrich().score << "   Lives Rem: " << model_.ostrich().lives;
    score_sprite.reconfigure(score_builder);
    set.add_sprite(score_sprite, {10,0});



}

ge211::Dims<int>
View::window_dimensions() const
{
    return window_dimensions_;
}
