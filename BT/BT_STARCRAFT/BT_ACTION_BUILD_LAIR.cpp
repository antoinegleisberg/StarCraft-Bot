#include "BT_ACTION_BUILD_LAIR.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_BUILD_LAIR::BT_ACTION_BUILD_LAIR(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_BUILD_LAIR::Evaluate(void* data)
{
    return ReturnState(BuildLair(data));
}

std::string BT_ACTION_BUILD_LAIR::GetDescription()
{
    return "BUILD SUPPLY PROVIDER";
}


BT_NODE::State BT_ACTION_BUILD_LAIR::BuildLair(void* data)
{
    Data* pData = (Data*)data;

	BWAPI::Broodwar->printf("Build Lair");
    
    // let's build a supply provider
	const BWAPI::UnitType hatchery = BWAPI::UnitTypes::Zerg_Hatchery;
	BWAPI::Unit hatcheryInstance = Tools::GetUnitOfType(hatchery);

    const bool startedBuilding = hatcheryInstance->morph(BWAPI::UnitTypes::Zerg_Lair);

    BWAPI::Error error = BWAPI::Broodwar->getLastError();
    if (error != BWAPI::Errors::None) {
		BWAPI::Broodwar->printf("Error while building lair");
		BWAPI::Broodwar->printf("Error: %s", error.c_str());
    }

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building %s", hatchery.getName().c_str());

    return startedBuilding ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}