#pragma once

#include "model.hxx"

class View
{
public:

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    ge211::Dims<int> window_dimensions() const;



private:

    Model const& model_;

    ge211::Dims<int> window_dimensions_;

    ge211::Image_sprite const ostrich_;

    ge211::Image_sprite const ostrich_flap_;

    ge211::Rectangle_sprite const platform0_;

    ge211::Rectangle_sprite const platform1_;

    ge211::Rectangle_sprite const platform2_;

    ge211::Rectangle_sprite const platform3_;

    ge211::Image_sprite const buzz0_;

    ge211::Image_sprite const buzz_flap;

    ge211::Circle_sprite const egg0_;

    ge211::Font sans;

    ge211::Text_sprite score_sprite;

};


