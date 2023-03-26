#include "BT_ACTION_BUILD_SPIRE.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_BUILD_SPIRE::BT_ACTION_BUILD_SPIRE(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_BUILD_SPIRE::Evaluate(void* data)
{
    return ReturnState(BuildSpire(data));
}

std::string BT_ACTION_BUILD_SPIRE::GetDescription()
{
    return "BUILD SPIRE";
}


BT_NODE::State BT_ACTION_BUILD_SPIRE::BuildSpire(void* data)
{
    Data* pData = (Data*)data;

	BWAPI::Broodwar->printf("Build Spire");

    // let's build a supply provider
	const BWAPI::UnitType spire = BWAPI::UnitTypes::Zerg_Spire;

    const bool startedBuilding = Tools::BuildBuilding(spire);

    BWAPI::Error error = BWAPI::Broodwar->getLastError();
    if (error != BWAPI::Errors::None) {
		BWAPI::Broodwar->printf("Error while building spire");
		BWAPI::Broodwar->printf("Error: %s", error.c_str());
    }

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building %s", spire.getName().c_str());

    return startedBuilding ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}