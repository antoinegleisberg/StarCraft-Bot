#include "BT_ACTION_BUILD_HATCHERY.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_BUILD_HATCHERY::BT_ACTION_BUILD_HATCHERY(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_BUILD_HATCHERY::Evaluate(void* data)
{
    return ReturnState(BuildHatchery(data));
}

std::string BT_ACTION_BUILD_HATCHERY::GetDescription()
{
    return "BUILD SUPPLY PROVIDER";
}


BT_NODE::State BT_ACTION_BUILD_HATCHERY::BuildHatchery(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Broodwar->printf("Build Hatchery");

    // let's build a supply provider
    const BWAPI::UnitType Hatchery = BWAPI::UnitTypes::Zerg_Hatchery;

    const bool startedBuilding = Tools::BuildBuilding(Hatchery);

    BWAPI::Error error = BWAPI::Broodwar->getLastError();
    if (error != BWAPI::Errors::None) {
        BWAPI::Broodwar->printf("Error while building hatchery");
        BWAPI::Broodwar->printf("Error: %s", error.c_str());
    }

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building %s", Hatchery.getName().c_str());

    return startedBuilding ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}