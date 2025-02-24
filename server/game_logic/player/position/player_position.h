#ifndef PLAYER_POSITION_H
#define PLAYER_POSITION_H

#include <memory>
#include <set>
#include <utility>
#include <vector>

#include "../../../../common/coordinate.h"
#include "../../map/stage.h"

#include "air_state.h"
class Player;
class PlayerPosition {
private:
    Coordinate position;
    std::vector<Coordinate> occupied;  // Las coordenadas que esta ocupando
    Player& player;
    std::shared_ptr<AirState> air_state;
    Stage& stage;
    uint8_t facing_direction;  // para disparar
    int aiming_direction;      // para disparar
    void move_vertically(int);
    bool aiming_up;
    uint8_t state;

public:
    PlayerPosition(Coordinate&, Player&, Stage&);
    void set_state(std::shared_ptr<AirState>, uint8_t);
    void move(const std::set<int>&, bool);
    Coordinate get_position();
    uint8_t get_state() { return state; }
    void occupy(Coordinate&);
    void free_occupied();
    std::vector<Coordinate> get_occupied();
    int get_facing_direction();
    int get_aiming_direction();
    void move_horizontally(int);
    void released_jump();
    bool is_aiming_up();
    void stop_aiming_up();
};

#endif
