#include "BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_VESPENE.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_VESPENE::BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_VESPENE(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, IsThereNotEnoughWorkersFarmingVespene) {}


std::string BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_VESPENE::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_VESPENE";
}

bool BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_VESPENE::IsThereNotEnoughWorkersFarmingVespene(void* data)
{
    Data* pData = (Data*)data;

    bool hasRefinery = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Extractor) != nullptr;
	std::cout << "test" << std::endl;

    return hasRefinery && (int)pData->unitsFarmingVespene.size() < pData->nWantedWorkersFarmingVespene;
}
