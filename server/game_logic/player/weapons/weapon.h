#ifndef WEAPON_H
#define WEAPON_H
#include <algorithm>
#include <memory>

#include "../../map/stage.h"

class Weapon {
protected:
    int ammo;
    int reach;
    Stage& stage;
    Player* player;
    bool stopped_holding_trigger;
    bool throw_started;
    int throw_reach;
    int id;

public:
    Weapon(Stage& stage, int ammo, int reach, int id):
            ammo(ammo),
            reach(reach),
            stage(stage),
            player(nullptr),
            stopped_holding_trigger(false),
            throw_started(false),
            throw_reach(30),
            id(id) {}
    virtual ~Weapon() = default;
    virtual void shoot(int, bool) {}
    virtual Coordinate get_gun_position(int offset, bool is_aiming_up);
    virtual void stop_shooting() { stopped_holding_trigger = true; }
    virtual void start_throw();
    virtual void finish_throw(int, bool, std::shared_ptr<Weapon>);
    virtual void set_player(Player* new_player) { player = new_player; }
    virtual void deset_player() { player = nullptr; }
    virtual void update() {}
    virtual void update(Coordinate) {}
    virtual uint8_t get_id() { return id; }
    virtual bool is_unarmed() { return false; }
    virtual bool is_dead() { return ammo == 0; }
};

class Unarmed: public Weapon {
public:
    explicit Unarmed(Stage&);
    virtual void shoot(int, bool) override;
    virtual Coordinate get_gun_position(int offset, bool is_aiming_up) override;
    virtual bool is_unarmed() override { return true; }
};

#endif
