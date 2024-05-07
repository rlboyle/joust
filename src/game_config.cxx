#include "game_config.hxx"

Game_config::Game_config()
    :
      window_dimensions({1000,700}),
      max_knight_velocity({3,2}),
      bounce_vel(1),
      acceleration(0.1),
      plat_height(20),
      knight_size({40, 40}),
      ostrich_flap_accely(1.5),
      ostrich_flap_accelx(0.9),
      ostrich_plat_accelx(0.3)

{ }