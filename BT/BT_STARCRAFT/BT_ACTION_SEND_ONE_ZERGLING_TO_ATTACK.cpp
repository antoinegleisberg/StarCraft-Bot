#include "BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK::BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK::Evaluate(void* data)
{
    return ReturnState(SendToAttack(data));
}

std::string BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK::GetDescription()
{
    return "BUILD SUPPLY PROVIDER";
}

BT_NODE::State BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK::SendToAttack(void* data)
{
    Data* pData = (Data*)data;
	
	BWAPI::Unit unit = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Zergling);
	
	if (unit == nullptr)
	{
		// checks if the max number of units is reached
		if (BWAPI::Broodwar->self()->supplyUsed() >= BWAPI::Broodwar->self()->supplyTotal())
		{
			BWAPI::Broodwar->printf("max number of units reached");
			BWAPI::Unit worker = Tools::GetUnitOfType(BWAPI::UnitTypes::Zerg_Drone);
			// morph into a spawning pool
			worker->build(BWAPI::UnitTypes::Zerg_Spawning_Pool);
			return BT_NODE::SUCCESS;
		}
		else 
		{
			BWAPI::Broodwar->printf("wait to have full supply before sending units");
			return BT_NODE::FAILURE;
		}
	}
	// player start location
	BWAPI::Broodwar->self()->getStartLocation();
	// all start locations
	BWAPI::Broodwar->getStartLocations();
	// enemy start location
	BWAPI::TilePosition ennemyLocation = BWAPI::Broodwar->enemy()->getStartLocation();

	// if the unit is not in the enemy base, send it there
	unit->move(BWAPI::Position(ennemyLocation));

    return BT_NODE::SUCCESS;
}