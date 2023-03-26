#include "BT_DECO_CONDITION_BUILD_HYDRALISK_DEN.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_BUILD_HYDRALISK_DEN::BT_DECO_CONDITION_BUILD_HYDRALISK_DEN(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, DoWeBuildHydraliskDen) {}


std::string BT_DECO_CONDITION_BUILD_HYDRALISK_DEN::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SUPPLY";
}

bool BT_DECO_CONDITION_BUILD_HYDRALISK_DEN::DoWeBuildHydraliskDen(void* data)
{
    Data* pData = (Data*)data;
    
    bool hasMinerals = BWAPI::Broodwar->self()->minerals() >= BWAPI::UnitTypes::Zerg_Hydralisk_Den.mineralPrice();
	bool hasGas = BWAPI::Broodwar->self()->gas() >= BWAPI::UnitTypes::Zerg_Hydralisk_Den.gasPrice();
    bool const hasSpawningPool = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Spawning_Pool) != nullptr;
    
    return hasGas && hasMinerals && hasSpawningPool;
}
