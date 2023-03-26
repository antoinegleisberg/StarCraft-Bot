#include "BT_DECO_CONDITION_BUILD_QUEENS_NEST.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_BUILD_QUEENS_NEST::BT_DECO_CONDITION_BUILD_QUEENS_NEST(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, DoWeBuildNest) {}


std::string BT_DECO_CONDITION_BUILD_QUEENS_NEST::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SUPPLY";
}

bool BT_DECO_CONDITION_BUILD_QUEENS_NEST::DoWeBuildNest(void* data)
{
    Data* pData = (Data*)data;
    
    bool hasMinerals = BWAPI::Broodwar->self()->minerals() >= BWAPI::UnitTypes::Zerg_Queens_Nest.mineralPrice();
	bool hasGas = BWAPI::Broodwar->self()->gas() >= BWAPI::UnitTypes::Zerg_Queens_Nest.gasPrice();
    bool const hasSpawningPool = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Spawning_Pool) != nullptr;
	bool const hasLair = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Lair) != nullptr;
	bool const hasHydraliskDen = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Hydralisk_Den) != nullptr;
	bool const hasSpire = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Spire) != nullptr;
    
    return hasGas && hasMinerals && hasSpawningPool && hasLair && hasHydraliskDen && hasSpire;
}
