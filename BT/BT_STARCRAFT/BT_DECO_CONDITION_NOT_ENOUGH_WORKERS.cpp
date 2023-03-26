#include "BT_DECO_CONDITION_NOT_ENOUGH_WORKERS.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_NOT_ENOUGH_WORKERS::BT_DECO_CONDITION_NOT_ENOUGH_WORKERS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughWorkers) {}


std::string BT_DECO_CONDITION_NOT_ENOUGH_WORKERS::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_WORKERS";
}

bool BT_DECO_CONDITION_NOT_ENOUGH_WORKERS::IsThereNotEnoughWorkers(void *data)
{
    Data* pData = (Data*)data;
    
    const BWAPI::UnitType workerType = BWAPI::Broodwar->self()->getRace().getWorker();
    const int workersOwned = Tools::CountUnitsOfType(workerType, BWAPI::Broodwar->self()->getUnits());

    const int maxSupply = BWAPI::Broodwar->self()->supplyTotal();
	const int supplyUsed = BWAPI::Broodwar->self()->supplyUsed();

    // Don't build workers if there is a too big proportion of them (we need defense/attack units)
	const float currentProportionOfWorkersToMax = (float)workersOwned / (float)maxSupply;
	const float currentProportionOfWorkersToUnits = (float)workersOwned / (float)supplyUsed;
	bool tooManyWorkers = currentProportionOfWorkersToMax > 0.3f || currentProportionOfWorkersToUnits > 0.3f;

	// Don't build workers if we have enough
	const int maxWorkers = pData->nMaxWantedWorkersFarmingMinerals + pData->nMaxWantedWorkersFarmingGas;

	const bool wantWorkers = !tooManyWorkers && workersOwned < maxWorkers;

	BWAPI::Broodwar->drawTextScreen(10, 10, "wantWorkers: %d", wantWorkers);

    return wantWorkers;
}
