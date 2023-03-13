#include "BT_DECO_CONDITION_SEND_IDLE_WORKERS_TO_VESPENE.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_SEND_IDLE_WORKERS_TO_VESPENE::BT_DECO_CONDITION_SEND_IDLE_WORKERS_TO_VESPENE(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, SendIdleWorkerToVespene) {}


std::string BT_DECO_CONDITION_SEND_IDLE_WORKERS_TO_VESPENE::GetDescription()
{
    return "DECO_CONDITION_SEND_IDLE_WORKERS_TO_VESPENE";
}

bool BT_DECO_CONDITION_SEND_IDLE_WORKERS_TO_VESPENE::SendIdleWorkerToVespene(void* data)
{
    Data* pData = (Data*)data;

    bool CondVespene = (int)pData->unitsFarmingVespene.size() < pData->nWantedWorkersFarmingVespene;


    if (Tools::GetUnitCount(BWAPI::UnitTypes::Zerg_Extractor) == 0)
        return false;

    return (int)pData->unitsFarmingVespene.size() < pData->nWantedWorkersFarmingVespene;
}
