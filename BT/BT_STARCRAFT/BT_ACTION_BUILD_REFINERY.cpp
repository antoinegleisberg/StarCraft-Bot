#include "BT_ACTION_BUILD_REFINERY.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_BUILD_REFINERY::BT_ACTION_BUILD_REFINERY(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_BUILD_REFINERY::Evaluate(void* data)
{
    return ReturnState(BuildRefinery(data));
}

std::string BT_ACTION_BUILD_REFINERY::GetDescription()
{
    return "BUILD SUPPLY PROVIDER";
}


BT_NODE::State BT_ACTION_BUILD_REFINERY::BuildRefinery(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Broodwar->printf("Build Refinery");

    // let's build a supply provider
    const BWAPI::UnitType Refinery = BWAPI::UnitTypes::Zerg_Extractor;

    const bool startedBuilding = Tools::BuildBuilding(Refinery);

    BWAPI::Error error = BWAPI::Broodwar->getLastError();
    if (error != BWAPI::Errors::None) {
        BWAPI::Broodwar->printf("Error while building refinery");
        BWAPI::Broodwar->printf("Error: %s", error.c_str());
    }

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building %s", Refinery.getName().c_str());

    return startedBuilding ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}