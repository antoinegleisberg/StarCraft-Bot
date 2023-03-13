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
	int count = Tools::GetUnitCount(BWAPI::UnitTypes::Zerg_Overlord) + pData->nMorphingLarvaOverlords;
	//BWAPI::Unit unit = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Zergling);

	if (count <= 1)
	{	
		printf("morphing to overlord");
		// checks if the max number of units is reached
		//if (BWAPI::Broodwar->self()->supplyUsed() >= BWAPI::Broodwar->self()->supplyTotal() - 2)
		{
			BWAPI::Broodwar->printf("max number of units reached");
			BWAPI::Unit larva = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Larva);
			// morph into an overlord
			if (larva != nullptr) {
				larva->morph(BWAPI::UnitTypes::Zerg_Overlord);
				//printf("morphing to overlord");
				if (larva->isMorphing()) pData->nMorphingLarvaOverlords++;
				std::cout << pData->nMorphingLarvaOverlords << std::endl;
				return BT_NODE::SUCCESS;
			}
		}
		//else
		//{
		//	BWAPI::Broodwar->printf("wait to have full supply before sending units");
		//	return BT_NODE::FAILURE;
		//}
	}
	else
	{
		BWAPI::Broodwar->printf("max number of overlords reached");
		return BT_NODE::FAILURE;
	}

	return BT_NODE::SUCCESS;
}