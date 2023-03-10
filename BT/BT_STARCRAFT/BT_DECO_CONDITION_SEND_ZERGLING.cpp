#include "BT_DECO_CONDITION_SEND_ZERGLING.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_SEND_ZERGLING::BT_DECO_CONDITION_SEND_ZERGLING(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, DoWeSendZergling) {}


std::string BT_DECO_CONDITION_SEND_ZERGLING::GetDescription()
{
    return "DECO_CONDITION_SEND_ZERGLING";
}

bool BT_DECO_CONDITION_SEND_ZERGLING::DoWeSendZergling(void* data)
{
    Data* pData = (Data*)data;

    // Get the amount of supply supply we currently have unused
	bool hasZerglings = Tools::GetUnitCount(BWAPI::UnitTypes::Zerg_Zergling) > 0;

    // If we have a sufficient amount of supply, we don't need to do anything
    return hasZerglings;
}
