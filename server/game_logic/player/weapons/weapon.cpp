#include "weapon.h"

#include <cmath>
#include <memory>
#include <utility>

#include "../player.h"
#include "projectiles/projectile.h"
#include "projectiles/projectile_dropped_weapon.h"
#define PLAYER_SIZE 6
void Weapon::start_throw() {
    throw_started = true;
    if (throw_reach < 100) {
        throw_reach += 3;
    }
}
void Weapon::finish_throw(int x_direction, bool, std::shared_ptr<Weapon> weapon) {
    Coordinate gun_position = get_gun_position(x_direction);
    throw_started = false;
    /* double deviation_angle = M_PI / 2; */
    // TODO: deberia poder tirar la granada para arriba
    // std::cout << "la velocidad del nuevo arma es de:" << std::to_string(throw_reach) <<
    // std::endl;
    int speed = throw_reach / 10;
    throw_reach = 30;
    stopped_holding_trigger = false;  // Esto es para que no dispare cuando se agarra
    stage.add_projectile(std::move(std::make_unique<ProjectileThrownWeapon>(
            std::move(weapon), gun_position, speed, x_direction, 80, id)));
}

// aim_direction en el eje x
Coordinate Weapon::get_gun_position(int facing_direction) {
    Coordinate player_position = player->get_position();
    if (facing_direction == 1) {
        return Coordinate(player_position.x + 6, player_position.y + 3);
    }
    return Coordinate(player_position.x - 2, player_position.y + 3);
}

Unarmed::Unarmed(Stage& stage): Weapon(stage, 0, 3, 0) {}

Coordinate Unarmed::get_gun_position(int facing_direction) {
    Coordinate player_position = Weapon::get_gun_position(facing_direction);
    player_position.y--;
    return player_position;
}
void Unarmed::shoot(int x_direction, bool) {
    // Se fija si existe un DroppedProjectile en la direccion en la que esta apuntando
    Coordinate init_position = get_gun_position(x_direction);
    int handle_direction = x_direction;
    for (int i = 0; i < reach; i++) {
        for (int j = 0; j < PLAYER_SIZE; j++) {
            Coordinate checking(init_position.x + i * handle_direction, init_position.y + j);
            if (stage.get(checking) > 0) {  // TODO: Definir bien cuales son los pickables
                std::shared_ptr<Weapon> weapon = stage.pick_weapon(checking);
                if (weapon != nullptr) {
                    player->pick_weapon(std::move(weapon));
                    return;
                }
                continue;
            }
        }
    }
}
