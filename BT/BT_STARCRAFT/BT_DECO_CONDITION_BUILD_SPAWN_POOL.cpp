#include "BT_DECO_CONDITION_BUILD_SPAWN_POOL.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_BUILD_SPAWN_POOL::BT_DECO_CONDITION_BUILD_SPAWN_POOL(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, DoWeBuildSpawningPool) {}


std::string BT_DECO_CONDITION_BUILD_SPAWN_POOL::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SUPPLY";
}

bool BT_DECO_CONDITION_BUILD_SPAWN_POOL::DoWeBuildSpawningPool(void* data)
{
    Data* pData = (Data*)data;

    // Get the amount of supply supply we currently have unused
    bool haveMaxWorkers = BWAPI::Broodwar->self()->supplyUsed() >= BWAPI::Broodwar->self()->supplyTotal() - 2;
	bool hasSpawningPool = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Spawning_Pool) != nullptr;
    bool hasMinerals = BWAPI::Broodwar->self()->minerals() >= BWAPI::UnitTypes::Zerg_Spawning_Pool.mineralPrice();

    // If we have a sufficient amount of supply, we don't need to do anything
    
    return haveMaxWorkers && !hasSpawningPool && hasMinerals;
}
