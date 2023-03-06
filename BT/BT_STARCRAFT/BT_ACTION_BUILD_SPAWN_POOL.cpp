#include "BT_ACTION_BUILD_SPAWN_POOL.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_BUILD_SPAWN_POOL::BT_ACTION_BUILD_SPAWN_POOL(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_BUILD_SPAWN_POOL::Evaluate(void* data)
{
    return ReturnState(BuildSpawningPool(data));
}

std::string BT_ACTION_BUILD_SPAWN_POOL::GetDescription()
{
    return "BUILD SUPPLY PROVIDER";
}


BT_NODE::State BT_ACTION_BUILD_SPAWN_POOL::BuildSpawningPool(void* data)
{
    Data* pData = (Data*)data;

	BWAPI::Broodwar->printf("Build Spawning Pool");

    // let's build a supply provider
	const BWAPI::UnitType spawningPool = BWAPI::UnitTypes::Zerg_Spawning_Pool;

    const bool startedBuilding = Tools::BuildBuilding(spawningPool);

    BWAPI::Error error = BWAPI::Broodwar->getLastError();
    if (error != BWAPI::Errors::None) {
		BWAPI::Broodwar->printf("Error while building spawning pool");
		BWAPI::Broodwar->printf("Error: %s", error.c_str());
    }

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building %s", spawningPool.getName().c_str());

    return startedBuilding ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}