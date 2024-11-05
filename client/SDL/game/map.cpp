#include "map.h"

#include <iostream>

#define TILES_TO_PIXELS 16

Map::Map(SDL_Renderer* rend, std::vector<uint16_t> mapa): rend(rend), mapa(mapa) {
    // Deberia llegarme la info del fondo
    background.initialize(rend, "img_src/background/day.png");
}

void Map::makeTile(int columnaActual, int filaActual /*, TileType tileType*/) {
    Image* tile = new Image();
    tile->initialize(rend, "img_src/tiles/dayTiles/middle.png");
    tile->queryTexture();
    tile->defineSize(1 * TILES_TO_PIXELS, 1 * TILES_TO_PIXELS);
    tile->position(columnaActual * TILES_TO_PIXELS, filaActual * TILES_TO_PIXELS);
    tiles.push_back(tile);
}

void Map::addPlayer(int columnaActual, int filaActual, int color, std::string name) {
    Player* player = new Player(rend, Color(color));
    player->defineSize(3 * TILES_TO_PIXELS, 3 * TILES_TO_PIXELS);
    player->update(columnaActual * TILES_TO_PIXELS, filaActual * TILES_TO_PIXELS,
                   DuckState::STANDING, RIGHT);
    players[name] = player;
}

void Map::makeMap(int columnas, int filas) {

    std::vector<std::vector<int>> matriz(filas, std::vector<int>(columnas, 0));

    int filaActual = 0;
    int columnaActual = 0;
    for (uint16_t i: mapa) {
        if (columnaActual >= columnas) {
            columnaActual = 0;
            filaActual++;
        }

        if (filaActual >= filas) {
            break;
        }

        switch (i) {
            case 5:  // piso
            case 6:  // pared
                // if ((matriz[filaActual-1][columnaActual] == i) ||
                // (matriz[filaActual][columnaActual-1] == i) ) {
                //     break;
                // }
                // DEFINIR que tamaño tienen los tiles
                matriz[filaActual][columnaActual] = i;
                // aca determino que tipo de tile es para conseguir el string q necesito
                makeTile(columnaActual, filaActual);
                break;
            case 13:  // caja
            case 14:  // caja rota
                break;
            default:
                break;
        }
        columnaActual++;
    }
}

void Map::update(std::string player, int x, int y, DuckState state, Side side) {
    players[player]->update(x * TILES_TO_PIXELS, y * TILES_TO_PIXELS, state, side);
}

void Map::newWeapon(/*int x, int y*/) {}

void Map::fill() {  // Dibuja de atras para adelante

    background.fill(true);

    for (Image* tile: tiles) {
        tile->fill();
    }

    for (Image* piso: tiles) {
        piso->fill();
    }

    /*
    for (Weapon weapon: weapons) {
        weapon.fill();
    }
    */

    for (const auto& pair: players) {
        pair.second->fill();
    }
}

Map::~Map() {
    for (Image* piso: tiles) {
        delete piso;
    }
    for (const auto& pair: players) {
        delete pair.second;
    }
}
