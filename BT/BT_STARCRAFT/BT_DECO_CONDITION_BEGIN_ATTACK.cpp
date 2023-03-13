#include "BT_DECO_CONDITION_BEGIN_ATTACK.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_BEGIN_ATTACK::BT_DECO_CONDITION_BEGIN_ATTACK(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, DoWeBeginAttack) {}


std::string BT_DECO_CONDITION_BEGIN_ATTACK::GetDescription()
{
    return "BT_DECO_CONDITION_BEGIN_ATTACK";
}

bool BT_DECO_CONDITION_BEGIN_ATTACK::DoWeBeginAttack(void* data)
{
    Data* pData = (Data*)data;


    return false;
}