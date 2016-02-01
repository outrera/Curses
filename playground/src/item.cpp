#include "../include/item.h"

weapon::weapon(int _attack, std::string _name, char _symbol, int _x, int _y)
{
    attack=_attack;
    health=0;
    defense=0;
    speed=5;
    name = _name;
    type = _name;
    equipped = false;
    canEquip = true;
    canWear = false;
    canUse=false;
    x = _x;
    y = _y;
    selected=false;
    material=iron;
    texture = RSL::getTextureData("data/items/weapon_type.raw",name+".texture");

    sprite.setTexture(texture);

    sprite.setPosition(x*16,y*16);
}

std::string weapon::itemDescription()
{
    std::stringstream ss;
    ss << attack;
    std::string str = ss.str();
    std::string description;


    description+="This " + name + " does " + str + " damage.";
    return description;
}

void weapon::equip(bool equipping)
{

}

corpse::corpse(std::string _name, std::vector<item*> _equipment, char _symbol, int _x, int _y)
{
    name=_name;
    equipment=_equipment;
    x=_x;
    y=_y;
}