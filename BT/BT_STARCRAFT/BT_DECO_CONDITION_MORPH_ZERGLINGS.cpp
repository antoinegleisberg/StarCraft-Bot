#include "BT_DECO_CONDITION_MORPH_ZERGLINGS.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_MORPH_ZERGLINGS::BT_DECO_CONDITION_MORPH_ZERGLINGS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, DoWeMorphZerglings) {}


std::string BT_DECO_CONDITION_MORPH_ZERGLINGS::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SUPPLY";
}

bool BT_DECO_CONDITION_MORPH_ZERGLINGS::DoWeMorphZerglings(void* data)
{
    Data* pData = (Data*)data;
    
    bool hasSpawnPool = Tools::GetUnitCount(BWAPI::UnitTypes::Zerg_Spawning_Pool) > 0;

    return hasSpawnPool;
}
