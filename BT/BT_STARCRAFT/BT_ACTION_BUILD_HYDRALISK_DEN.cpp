#include "BT_ACTION_BUILD_HYDRALISK_DEN.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_BUILD_HYDRALISK_DEN::BT_ACTION_BUILD_HYDRALISK_DEN(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_BUILD_HYDRALISK_DEN::Evaluate(void* data)
{
    return ReturnState(BuildHydraliskDen(data));
}

std::string BT_ACTION_BUILD_HYDRALISK_DEN::GetDescription()
{
    return "BUILD SUPPLY PROVIDER";
}


BT_NODE::State BT_ACTION_BUILD_HYDRALISK_DEN::BuildHydraliskDen(void* data)
{
    Data* pData = (Data*)data;

	BWAPI::Broodwar->printf("Build Hydralisk Den");

    // let's build a supply provider
	const BWAPI::UnitType hydraliskDen = BWAPI::UnitTypes::Zerg_Hydralisk_Den;

    const bool startedBuilding = Tools::BuildBuilding(hydraliskDen);

    BWAPI::Error error = BWAPI::Broodwar->getLastError();
    if (error != BWAPI::Errors::None) {
		BWAPI::Broodwar->printf("Error while building hydralisk den");
		BWAPI::Broodwar->printf("Error: %s", error.c_str());
    }

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building %s", hydraliskDen.getName().c_str());

    return startedBuilding ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}