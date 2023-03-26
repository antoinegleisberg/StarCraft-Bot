#include "BT_ACTION_TRAIN_UNITS.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_TRAIN_UNITS::BT_ACTION_TRAIN_UNITS(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_TRAIN_UNITS::Evaluate(void* data)
{
    return ReturnState(TrainUnit(data));
}

std::string BT_ACTION_TRAIN_UNITS::GetDescription()
{
    return "TRAIN UNITS";
}


BT_NODE::State BT_ACTION_TRAIN_UNITS::TrainUnit(void* data)
{
    Data* pData = (Data*)data;

    const std::vector<BWAPI::UnitType> unitsToTrain = pData->BestAvailableUnitTypes;
    
    const BWAPI::Unit myDepot = Tools::GetDepot();

    // if we have a valid depot unit and it's currently not training something, train a worker
    // there is no reason for a bot to ever use the unit queueing system, it just wastes resources
    if (myDepot) {
        BWAPI::Broodwar->drawTextScreen(10, 30, "TRAINING %s", unitsToTrain[0].getName().c_str());
		if (unitsToTrain.size() > 1) BWAPI::Broodwar->drawTextScreen(10, 40, "TRAINING %s", unitsToTrain[1].getName().c_str());
		if (unitsToTrain.size() > 2) BWAPI::Broodwar->drawTextScreen(10, 50, "TRAINING %s", unitsToTrain[2].getName().c_str());
        for (BWAPI::UnitType unitType : unitsToTrain)
        {
            myDepot->train(unitType);
            BWAPI::Error error = BWAPI::Broodwar->getLastError();
            if (error != BWAPI::Errors::None)
                return BT_NODE::FAILURE;
            else {
                return BT_NODE::SUCCESS;
            }
        }
    }

    return BT_NODE::FAILURE;
}