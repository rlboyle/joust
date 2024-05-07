#include "controller.hxx"
#include "model.hxx"


Controller::Controller()
        : model_(),
          view_(model_),
          ostrich_(model_.ostrich())
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view_.window_dimensions();
}

void
Controller::on_key(ge211::Key key)
{

}

void
Controller::on_key_down(ge211::Key key)
{
    if (key == ge211::Key::code('w')) {
        model_.ostrich_flap();

    } else if (key == ge211::Key::code('a')) {
        model_.side_key_pressed = true;
        model_.ost_move_dir = Facing::left;
        model_.ostrich_face(Facing::left);


    } else if (key == ge211::Key::code('d')) {
        model_.side_key_pressed = true;
        model_.ost_move_dir = Facing::right;
        model_.ostrich_face(Facing::right);


    }
}

void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}

void
Controller::on_key_up(ge211::Key key)
{
    if (key == ge211::Key::code('a') || key == ge211::Key::code('d')) {
        model_.side_key_pressed = false;
    }
}