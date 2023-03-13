#include "BT_ACTION_SEND_IDLE_WORKER_TO_VESPENE.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_SEND_IDLE_WORKER_TO_VESPENE::BT_ACTION_SEND_IDLE_WORKER_TO_VESPENE(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_SEND_IDLE_WORKER_TO_VESPENE::Evaluate(void* data)
{
    return ReturnState(SendIdleWorkerToVespene(data));
}

std::string BT_ACTION_SEND_IDLE_WORKER_TO_VESPENE::GetDescription()
{
    return "SEND IDLE WORKER TO MINERAL";
}


BT_NODE::State BT_ACTION_SEND_IDLE_WORKER_TO_VESPENE::SendIdleWorkerToVespene(void* data)
{
    Data* pData = (Data*)data;

    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : myUnits)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
        if (unit->getType().isWorker() && unit->isIdle())
        {
			const BWAPI::UnitType Extractor = BWAPI::UnitTypes::Zerg_Extractor;
            // Get the closest mineral to this worker unit
            BWAPI::Unit closestVespene = Tools::GetUnitOfType(Extractor);


            
            // If a valid mineral was found, right click it with the unit in order to start harvesting
            if (closestVespene) {
                unit->rightClick(closestVespene);
                pData->unitsFarmingVespene.insert(unit);
                return BT_NODE::SUCCESS;
            }
        }
    }

    return BT_NODE::FAILURE;
}