#include "spawn_point.h"

#include "../player/weapons/projectiles/projectile_dropped_weapon.h"

void WeaponSpawnPoint::spawn_weapon() {
    // Para agregar mas opciones de armas agregarlas unicamente al switch
    std::unique_ptr<Weapon> weapon;
    switch (type_of_weapon) {
        case COWBOY_PISTOL:
            weapon = std::make_unique<CowboyGun>(stage);
            break;
        case MAGNUM:
            weapon = std::make_unique<Magnum>(stage);
            break;
        case HELMET:
        case HELMET2:
        case HELMET3:
            weapon = std::make_unique<Helmet>(stage, type_of_weapon);
            break;
        case CHEST:
            weapon = std::make_unique<Chest>(stage);
            break;
        default:
            weapon = std::make_unique<CowboyGun>(stage);
            break;
    }

    stage.add_projectile(std::make_unique<ProjectileDroppedWeapon>(std::move(weapon), position,
                                                                       4, 4, type_of_weapon, this));
}
void WeaponSpawnPoint::set_weapon(int weapon_id) { type_of_weapon = weapon_id; }

void WeaponSpawnPoint::update() {
    if (!is_free) {
        return;
    }
    counter++;
    // el counter es despues de cuantas iteraciones va a tirar un arma de nuevo
    if (counter == 300) {
        spawn_weapon();
        counter = 0;
        is_free = false;
    }
}

void WeaponSpawnPoint::free() { is_free = true; }

