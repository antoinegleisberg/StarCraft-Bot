#pragma once

#include "BT_ACTION_ATTACK_NEAREST_ENNEMY.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_ATTACK_NEAREST_ENNEMY::BT_ACTION_ATTACK_NEAREST_ENNEMY(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_ATTACK_NEAREST_ENNEMY::Evaluate(void* data)
{
    return ReturnState(AttackEnnemy(data));
}

std::string BT_ACTION_ATTACK_NEAREST_ENNEMY::GetDescription()
{
    return "make all available zergling on front Attack the nearest Ennemy";
}


BT_NODE::State BT_ACTION_ATTACK_NEAREST_ENNEMY::AttackEnnemy(void* data)
{
    bool EnnemyAttacked = false;

    //TODO

    return EnnemyAttacked ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}