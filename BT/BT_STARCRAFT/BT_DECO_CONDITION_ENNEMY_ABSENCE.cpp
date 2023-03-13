#include "BT_DECO_CONDITION_ENNEMY_ABSENCE.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_ENNEMY_ABSENCE::BT_DECO_CONDITION_ENNEMY_ABSENCE(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, AreWeInDanger) {}


std::string BT_DECO_CONDITION_ENNEMY_ABSENCE::GetDescription()
{
    return "BT_DECO_CONDITION_ENNEMY_ABSENCE";
}

bool BT_DECO_CONDITION_ENNEMY_ABSENCE::AreWeInDanger(void* data)
{
    Data* pData = (Data*)data;

    //TODO
    return false;
}