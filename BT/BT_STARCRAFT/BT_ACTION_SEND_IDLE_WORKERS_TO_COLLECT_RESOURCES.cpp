#include "BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES::BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES::Evaluate(void* data)
{
    return ReturnState(SendWorkersToCollectResources(data));
}

std::string BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES::GetDescription()
{
    return "SEND IDLE WORKER TO MINE RESOURCES";
}


bool BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES::WantMoreMinerals(void* data) {
	const Data* pData = (const Data*)data;
	return (int)pData->unitsFarmingMinerals.size() < pData->nWantedWorkersFarmingMinerals;
}

bool BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES::WantMoreGas(void* data) {
    const Data* pData = (const Data*)data;
	bool const hasRefinery = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Extractor) != nullptr;
	return hasRefinery && (int)pData->unitsFarmingVespene.size() < pData->nWantedWorkersFarmingVespene;
}

BT_NODE::State BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES::SendWorkersToCollectResources(void* data)
{
    Data* pData = (Data*)data;

    bool farm_minerals = BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES::WantMoreMinerals(data);
	bool farm_gas = BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES::WantMoreGas(data);

	bool success = false;

    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : myUnits)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
        if (unit->getType().isWorker() && unit->isIdle())
        {
			BWAPI::Unit closestResource = nullptr;
            if (!farm_gas && !farm_minerals) {
				// no specific needs, just send it to the closest mineral
                closestResource = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getMinerals());
            }
            else if (farm_minerals) {
                closestResource = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getMinerals());
            }
            else if (farm_gas) {
				const BWAPI::UnitType Extractor = BWAPI::UnitTypes::Zerg_Extractor;
				closestResource = Tools::GetUnitOfType(Extractor);
            }

            // If a valid resource was found, right click it with the unit in order to start harvesting
            if (closestResource) {
                unit->rightClick(closestResource);
                pData->unitsFarmingMinerals.insert(unit);
                success = true;
                farm_minerals = BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES::WantMoreMinerals(data);
                farm_gas = BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES::WantMoreGas(data);
            }   
        }
    }
    
	if (success) {
		return BT_NODE::SUCCESS;
	}

    return BT_NODE::FAILURE;
}