#ifndef STAGE_H
#define STAGE_H

#include <string>
#include "air_state.h"
#define ROW_NUMBER 50
#define COLUMN_NUMBER 50
#include <vector>
#include "map.h"

class Player; // Declaracion adelantada para evitar dependencia circular.
class Stage{
private:
    Map map;
    void printStage();
public:
    // Son virtuales para poder mockear la clase mas facilmente
    virtual void draw_player(Player&);
    virtual bool is_valid_position(Player&, Coordinate);
    Stage(const std::string&);
    virtual void delete_player_from_stage(Player&);
    virtual void print();
    virtual bool should_fall(Player&);
};

#endif 
