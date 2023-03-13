#include "BT_DECO_CONDITION_MORPH_OVERLORDS.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_MORPH_OVERLORDS::BT_DECO_CONDITION_MORPH_OVERLORDS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, DoWeMorphOverlords) {}


std::string BT_DECO_CONDITION_MORPH_OVERLORDS::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SUPPLY";
}

bool BT_DECO_CONDITION_MORPH_OVERLORDS::DoWeMorphOverlords(void* data)
{
    Data* pData = (Data*)data;

    // Get the amount of supply supply we currently have unused
    //bool hasSpawnPool = Tools::GetUnitCount(BWAPI::UnitTypes::Zerg_Spawning_Pool) > 0;

	bool needOverlords = Tools::GetUnitCount(BWAPI::UnitTypes::Zerg_Overlord) < 2 && Tools::GetUnitCount(BWAPI::UnitTypes::Zerg_Drone) > 6;

    // If we have a sufficient amount of supply, we don't need to do anything
    return needOverlords;
}
