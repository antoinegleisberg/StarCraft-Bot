#pragma once
#include "BT_ACTION_ATTACK_NEAREST_BUILDING.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_ATTACK_NEAREST_BUILDING::BT_ACTION_ATTACK_NEAREST_BUILDING(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_ATTACK_NEAREST_BUILDING::Evaluate(void* data)
{
    return ReturnState(AttackBuilding(data));
}

std::string BT_ACTION_ATTACK_NEAREST_BUILDING::GetDescription()
{
    return "make all available zergling on front Attack the nearest Building";
}


BT_NODE::State BT_ACTION_ATTACK_NEAREST_BUILDING::AttackBuilding(void* data)
{
    bool BuildingAttacked = false;

    //TODO

    return BuildingAttacked ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}