#include "BT_ACTION_MORPH_OVERLORDS.h"
#include "BT_ACTION_BUILD_SPAWN_POOL.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_MORPH_OVERLORDS::BT_ACTION_MORPH_OVERLORDS(std::string name, BT_NODE* parent)
	: BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_MORPH_OVERLORDS::Evaluate(void* data)
{
	return ReturnState(MorphToOverlords(data));
}

std::string BT_ACTION_MORPH_OVERLORDS::GetDescription()
{
	return "BUILD SUPPLY PROVIDER";
}

BT_NODE::State BT_ACTION_MORPH_OVERLORDS::MorphToOverlords(void* data)
{
	Data* pData = (Data*)data;
	
	{
		BWAPI::Unit larva = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Larva);
		// morph into an overlord
		if (larva != nullptr) {
			larva->morph(BWAPI::UnitTypes::Zerg_Overlord);
			if (larva->isMorphing()) pData->nMorphingLarvaOverlords++;
			return BT_NODE::SUCCESS;
		}
	}

	return BT_NODE::FAILURE;
}