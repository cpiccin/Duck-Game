#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "../../../common/coordinate.h"
#include "../map/stage.h"
#include "position/player_position.h"
#include "weapons/weapon.h"

#include "observer.h"
#include "subject.h"

class Player: public PlayerSubject {
private:
    int id;
    std::shared_ptr<PlayerPosition> position;
    bool is_alive;
    Stage* stage;
    std::shared_ptr<Weapon> weapon;
    std::set<int> current_actions;
    std::string name;
    bool should_notify;
    Coordinate initial_position;
    void notify_picked_weapon();
    void notify_dropped_weapon(uint8_t id);
    bool is_unarmed;

public:
    int get_id();
    Coordinate get_position();
    std::vector<Coordinate> get_occupied();
    int get_facing_direction();
    Player(Coordinate&, int, const std::string&, const PlayerObserver&);
    void die();
    void occupy(Coordinate&);
    void add_action(int&);
    void remove_action(int&);
    void move(const std::set<int>&);
    void execute(const int&);
    void shoot();
    void update();
    void Notify() { should_notify = true; }
    void notify_moved();
    void init_for_stage(Stage*);
    bool lives() { return is_alive; }
    void pick_weapon(std::shared_ptr<Weapon> new_weapon);
    void unarm_self();
};

#endif
