#include "BT_ACTION_LAUNCH_4POOL_ATTACK.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_LAUNCH_4POOL_ATTACK::BT_ACTION_LAUNCH_4POOL_ATTACK(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_LAUNCH_4POOL_ATTACK::Evaluate(void* data)
{
    return ReturnState(LaunchAttack(data));
}

std::string BT_ACTION_LAUNCH_4POOL_ATTACK::GetDescription()
{
    return "SEND ZERGLINGS TO ATTACK";
}


BT_NODE::State BT_ACTION_LAUNCH_4POOL_ATTACK::LaunchAttack(void* data)
{
    Data* pData = (Data*)data;

    // If we sent enough zerglings, the 4-Pool attack is over and we move on to phase 2
	if (pData->nDeadZerglings >= 14) return BT_NODE::State::SUCCESS;

    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();

    // Get ennemy base location
    // Step 1 : Get potential start locations
    BWAPI::TilePosition enemyLocation1 = BWAPI::Broodwar->getStartLocations()[0];
    BWAPI::TilePosition enemyLocation2 = BWAPI::Broodwar->getStartLocations()[1];
	// Step 2 : Get our start location, the ennemie's is the other one
    BWAPI::TilePosition enemyLocation = enemyLocation1;
    if (BWAPI::Broodwar->self()->getStartLocation() == enemyLocation1) enemyLocation = enemyLocation2;
    
    // Send units to attack
    for (auto& unit : myUnits)
    {
        // Check the unit type, if it is a Zergling, attack
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Zergling && unit->isIdle())
        {
            // if the unit is not in the enemy base, send it there
            unit->attack(BWAPI::Position(enemyLocation));

			// make the zergling target the closest enemy unit
            BWAPI::Unit ennemy = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getUnitsOnTile(enemyLocation));            
            if (ennemy) { unit->rightClick(ennemy); }
            
            else {
                bool randX = rand() % 2;
                bool randY = rand() % 2;

                bool randX2 = rand() % 2;
                bool randY2 = rand() % 2;
                
                BWAPI::TilePosition patLoc = BWAPI::TilePosition(enemyLocation.x + 10* randX - 10 * randX2, enemyLocation.y + 10* randY - 10 * randY2);
                unit->patrol(BWAPI::Position(patLoc));

            }
        }
    }

	// Train more Zerglings
    const BWAPI::Unit myDepot = Tools::GetDepot();
    const BWAPI::UnitType zerglingType = BWAPI::UnitTypes::Zerg_Zergling;
    const int availableCrystals = BWAPI::Broodwar->self()->minerals();

    if (myDepot && !myDepot->isTraining()) {
        const int nAdditionalZerglingsTrained = pData->additionalZerglingsTrained;
        if (nAdditionalZerglingsTrained < 2) {
            if (availableCrystals >= zerglingType.mineralPrice()) {
                myDepot->train(zerglingType);
				pData->additionalZerglingsTrained++;
            }
        }
        else {
			pData->startedPhase2 = true;
        }
        const BWAPI::Error error = BWAPI::Broodwar->getLastError();
        if (error != BWAPI::Errors::None)
            return BT_NODE::FAILURE;
    }

    return BT_NODE::RUNNING;
}