#include "BT_ACTION_BUILD_QUEENS_NEST.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_BUILD_QUEENS_NEST::BT_ACTION_BUILD_QUEENS_NEST(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_BUILD_QUEENS_NEST::Evaluate(void* data)
{
    return ReturnState(BuildNest(data));
}

std::string BT_ACTION_BUILD_QUEENS_NEST::GetDescription()
{
    return "BUILD SPIRE";
}


BT_NODE::State BT_ACTION_BUILD_QUEENS_NEST::BuildNest(void* data)
{
    Data* pData = (Data*)data;

	BWAPI::Broodwar->printf("Build Nest");

    // let's build a supply provider
	const BWAPI::UnitType nest = BWAPI::UnitTypes::Zerg_Queens_Nest;

    const bool startedBuilding = Tools::BuildBuilding(nest);

    BWAPI::Error error = BWAPI::Broodwar->getLastError();
    if (error != BWAPI::Errors::None) {
		BWAPI::Broodwar->printf("Error while building spire");
		BWAPI::Broodwar->printf("Error: %s", error.c_str());
    }

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building %s", nest.getName().c_str());

    return startedBuilding ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}