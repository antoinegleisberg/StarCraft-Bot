#include "BT_DECO_CONDITION_BUILD_LAIR.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_BUILD_LAIR::BT_DECO_CONDITION_BUILD_LAIR(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, DoWeBuildLair) {}


std::string BT_DECO_CONDITION_BUILD_LAIR::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SUPPLY";
}

bool BT_DECO_CONDITION_BUILD_LAIR::DoWeBuildLair(void* data)
{
    Data* pData = (Data*)data;
    
    bool hasMinerals = BWAPI::Broodwar->self()->minerals() >= BWAPI::UnitTypes::Zerg_Lair.mineralPrice();
	bool hasGas = BWAPI::Broodwar->self()->gas() >= BWAPI::UnitTypes::Zerg_Lair.gasPrice();
    BWAPI::Unit hatchery = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Hatchery);
    
    return hasGas && hasMinerals && hatchery != nullptr;
}
