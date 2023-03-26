#include "BT_ACTION_BUILD_4POOL_ARMY.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_BUILD_4POOL_ARMY::BT_ACTION_BUILD_4POOL_ARMY(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_BUILD_4POOL_ARMY::Evaluate(void* data)
{
    return ReturnState(Build4PoolArmy(data));
}

std::string BT_ACTION_BUILD_4POOL_ARMY::GetDescription()
{
    return "Build 4Pool Army";
}


BT_NODE::State BT_ACTION_BUILD_4POOL_ARMY::Build4PoolArmy(void* data)
{
    // If we are done building the 4-Pool, move on to the attack
    if (BWAPI::Broodwar->self()->supplyTotal() == BWAPI::Broodwar->self()->supplyUsed()) {
        BWAPI::Broodwar->printf("Done building troops for 4-Pool");
        return BT_NODE::SUCCESS;
    }

    Data* pData = (Data*)data;

    const BWAPI::UnitType workerType = BWAPI::Broodwar->self()->getRace().getWorker();
	const BWAPI::UnitType zerglingType = BWAPI::UnitTypes::Zerg_Zergling;
	const BWAPI::UnitType larvaType = BWAPI::UnitTypes::Zerg_Larva;
    const BWAPI::Unit myDepot = Tools::GetDepot();

    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
	int nWorkers = Tools::CountUnitsOfType(workerType, myUnits);
	int nZerglings = Tools::CountUnitsOfType(zerglingType, myUnits);

    for (const BWAPI::Unit unit : myUnits) {
        if (unit->getType() == larvaType && unit->getBuildType() == zerglingType) {
            nZerglings += 2;
        }
        if (unit->getType() == larvaType && unit->getBuildType() == workerType) {
            nWorkers++;
        }
    }

	int availableCrystals = BWAPI::Broodwar->self()->minerals();

    if (myDepot && !myDepot->isTraining()) {
        if (nWorkers < 4) {
            if (availableCrystals >= workerType.mineralPrice()) {
                myDepot->train(workerType);
            }
        }
		else if (nZerglings < 10) {
            if (availableCrystals >= zerglingType.mineralPrice()) {
                myDepot->train(zerglingType);
            }
        }
        const BWAPI::Error error = BWAPI::Broodwar->getLastError();
        if (error != BWAPI::Errors::None)
            return BT_NODE::FAILURE;
    }    
    
    return BT_NODE::RUNNING;
}