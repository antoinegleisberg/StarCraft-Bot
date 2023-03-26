#include "BT_DECO_CONDITION_BUILD_REFINERY.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_BUILD_REFINERY::BT_DECO_CONDITION_BUILD_REFINERY(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, DoWeBuildRefinery) {}


std::string BT_DECO_CONDITION_BUILD_REFINERY::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SUPPLY";
}

bool BT_DECO_CONDITION_BUILD_REFINERY::DoWeBuildRefinery(void* data)
{
    Data* pData = (Data*)data;

    // Get the amount of supply supply we currently have unused
    bool hasMinerals = BWAPI::Broodwar->self()->minerals() >= BWAPI::UnitTypes::Zerg_Extractor.mineralPrice();
    bool hasEnoughWorkers = Tools::GetUnitCount(BWAPI::UnitTypes::Zerg_Drone) >= 8;

    // If we have a sufficient amount of supply, we don't need to do anything

    return hasMinerals && hasEnoughWorkers;
}
