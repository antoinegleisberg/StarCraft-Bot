#include "BT_DECO_CONDITION_BUILD_HATCHERY.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_BUILD_HATCHERY::BT_DECO_CONDITION_BUILD_HATCHERY(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, DoWeBuildHatchery) {}


std::string BT_DECO_CONDITION_BUILD_HATCHERY::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SUPPLY";
}

bool BT_DECO_CONDITION_BUILD_HATCHERY::DoWeBuildHatchery(void* data)
{
    Data* pData = (Data*)data;

    // Get the amount of supply supply we currently have unused
	bool notEnoughHatcheries = Tools::GetUnitCount(BWAPI::UnitTypes::Zerg_Hatchery) < 2;
    bool hasMinerals = BWAPI::Broodwar->self()->minerals() >= BWAPI::UnitTypes::Zerg_Hatchery.mineralPrice();
	bool needHatchery = Tools::GetUnitCount(BWAPI::UnitTypes::Zerg_Overlord) >= 2;

    // If we have a sufficient amount of supply, we don't need to do anything

    return notEnoughHatcheries && hasMinerals && needHatchery;
}
