#include "ge211.hxx"

class Platform {
public:
    Platform(ge211::Rect<int>, ge211::Posn<int>);
private:
    ge211::Rect<int> dimensions;
    ge211::Posn<int> position;
};