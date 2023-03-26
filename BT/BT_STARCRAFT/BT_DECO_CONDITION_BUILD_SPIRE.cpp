#include "BT_DECO_CONDITION_BUILD_SPIRE.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_BUILD_SPIRE::BT_DECO_CONDITION_BUILD_SPIRE(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, DoWeBuildSpire) {}


std::string BT_DECO_CONDITION_BUILD_SPIRE::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SUPPLY";
}

bool BT_DECO_CONDITION_BUILD_SPIRE::DoWeBuildSpire(void* data)
{
    Data* pData = (Data*)data;
    
    bool hasMinerals = BWAPI::Broodwar->self()->minerals() >= BWAPI::UnitTypes::Zerg_Hydralisk_Den.mineralPrice();
	bool hasGas = BWAPI::Broodwar->self()->gas() >= BWAPI::UnitTypes::Zerg_Hydralisk_Den.gasPrice();
    bool const hasSpawningPool = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Spawning_Pool) != nullptr;
	bool const hasLair = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Lair) != nullptr;
	bool const hasHydraliskDen = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Hydralisk_Den) != nullptr;
    
    return hasGas && hasMinerals && hasSpawningPool && hasLair && hasHydraliskDen;
}
