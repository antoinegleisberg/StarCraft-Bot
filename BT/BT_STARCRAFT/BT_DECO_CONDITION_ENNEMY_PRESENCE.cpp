#pragma once
#include "BT_DECO_CONDITION_ENNEMY_PRESENCE.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_ENNEMY_PRESENCE::BT_DECO_CONDITION_ENNEMY_PRESENCE(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, CanWeAttackSomething) {}


std::string BT_DECO_CONDITION_ENNEMY_PRESENCE::GetDescription()
{
    return "BT_DECO_CONDITION_ENNEMY_PRESENC";
}

bool BT_DECO_CONDITION_ENNEMY_PRESENCE::CanWeAttackSomething(void* data)
{
    Data* pData = (Data*)data;

    //TODO
    return false;
}