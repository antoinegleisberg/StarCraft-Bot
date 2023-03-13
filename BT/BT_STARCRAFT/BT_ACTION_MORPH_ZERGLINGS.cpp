#include "BT_ACTION_MORPH_ZERGLINGS.h"
#include "BT_ACTION_BUILD_SPAWN_POOL.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_MORPH_ZERGLINGS::BT_ACTION_MORPH_ZERGLINGS(std::string name, BT_NODE* parent)
	: BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_MORPH_ZERGLINGS::Evaluate(void* data)
{
	return ReturnState(MorphToZerglings(data));
}

std::string BT_ACTION_MORPH_ZERGLINGS::GetDescription()
{
	return "BUILD SUPPLY PROVIDER";
}

BT_NODE::State BT_ACTION_MORPH_ZERGLINGS::MorphToZerglings(void* data)
{
	Data* pData = (Data*)data;
	int countZ = Tools::GetUnitCount(BWAPI::UnitTypes::Zerg_Zergling);
	int countO = Tools::GetUnitCount(BWAPI::UnitTypes::Zerg_Overlord);
	//BWAPI::Unit unit = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Zergling);

	if (countZ <= 50 && countO > 1)
	{
		Data* pData = (Data*)data;

		const BWAPI::UnitType larva = BWAPI::UnitTypes::Zerg_Larva;
		const BWAPI::Unit myDepot = Tools::GetUnitOfType(larva);
		
		
		// if we have a valid depot unit and it's currently not training something, train a worker
		// there is no reason for a bot to ever use the unit queueing system, it just wastes resources
		if (myDepot && !myDepot->isMorphing()) {
			myDepot->morph(BWAPI::UnitTypes::Zerg_Zergling);

			
			
			BWAPI::Error error = BWAPI::Broodwar->getLastError();
			if (error != BWAPI::Errors::None)
				return BT_NODE::FAILURE;
			
			else return BT_NODE::SUCCESS;
		}

	}

	return BT_NODE::SUCCESS;
}