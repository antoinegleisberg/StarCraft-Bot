#include "BT_DECO_CONDITION_STARTED_PHASE2.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_STARTED_PHASE2::BT_DECO_CONDITION_STARTED_PHASE2(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, StartedPhase2) {}


std::string BT_DECO_CONDITION_STARTED_PHASE2::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SUPPLY";
}

bool BT_DECO_CONDITION_STARTED_PHASE2::StartedPhase2(void *data)
{
    Data* pData = (Data*)data;

    bool startPhase2 = pData->startedPhase2;

    return startPhase2;
}