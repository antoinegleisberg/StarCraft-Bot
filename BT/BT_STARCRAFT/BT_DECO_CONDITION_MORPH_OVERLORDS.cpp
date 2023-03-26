#include "BT_DECO_CONDITION_MORPH_OVERLORDS.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_MORPH_OVERLORDS::BT_DECO_CONDITION_MORPH_OVERLORDS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, DoWeMorphOverlords) {}


std::string BT_DECO_CONDITION_MORPH_OVERLORDS::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SUPPLY";
}

bool BT_DECO_CONDITION_MORPH_OVERLORDS::DoWeMorphOverlords(void* data)
{
    Data* pData = (Data*)data;

    // If we do not have enough supply left, morph an overlord
    bool needOverlords = (BWAPI::Broodwar->self()->supplyUsed() + 8 > BWAPI::Broodwar->self()->supplyTotal());

	BWAPI::Broodwar->drawTextScreen(10, 20, "Need overlords: %d", needOverlords);

    return needOverlords;
}