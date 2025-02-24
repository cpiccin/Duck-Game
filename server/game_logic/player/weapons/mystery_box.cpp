#include "mystery_box.h"

MysteryBox::MysteryBox(Stage& stage, Coordinate position): stage(stage), pos(position) {
    broken = false;
    item = 0;
}

std::shared_ptr<ProjectileDroppedWeapon> MysteryBox::destroy_box() {
    if (broken) {
        return nullptr;
    }
    std::list<uint> items = {BANANA,  COWBOY_PISTOL, MAGNUM,        DUEL_PISTOL, AK_47,
                             SHOTGUN, SNIPER,        PEW_PEW_LASER, LASER_RIFLE, HELMET,
                             HELMET2, HELMET3,       CHEST,         EXPLOSION};
    // get random item from the list
    auto it = items.begin();
    std::advance(it, rand() % items.size());
    item = *it;

    broken = true;
    if (item == EXPLOSION) {
        explode();
        return nullptr;
    } else {
        return drop_weapon();
    }
}


void MysteryBox::explode() {
    int radius = Config::get_instance()->explosion_range;
    stage.set_explosion(pos, radius);
}


std::shared_ptr<ProjectileDroppedWeapon> MysteryBox::drop_weapon() {
    std::shared_ptr<Weapon> weapon;
    switch (item) {
        case BANANA:
            weapon = std::make_shared<Banana>(stage);
            break;
        case COWBOY_PISTOL:
            weapon = std::make_shared<CowboyGun>(stage);
            break;
        case MAGNUM:
            weapon = std::make_shared<Magnum>(stage);
            break;
        case DUEL_PISTOL:
            weapon = std::make_shared<DuelPistol>(stage);
            break;
        case AK_47:
            weapon = std::make_shared<Ak47>(stage);
            break;
        case SHOTGUN:
            weapon = std::make_shared<Shotgun>(stage);
            break;
        case SNIPER:
            weapon = std::make_shared<Sniper>(stage);
            break;
        case PEW_PEW_LASER:
            weapon = std::make_shared<PewLaser>(stage);
            break;
        case LASER_RIFLE:
            weapon = std::make_shared<LaserRifle>(stage);
            break;
        case HELMET:
        case HELMET2:
        case HELMET3:
            weapon = std::make_shared<Helmet>(stage, item);
            break;
        case CHEST:
            weapon = std::make_shared<Chest>(stage);
            break;
        default:
            weapon = std::make_shared<CowboyGun>(stage);
            break;
    }

    return std::make_unique<ProjectileDroppedWeapon>(weapon, pos, 4, 4000, item, nullptr);
}
