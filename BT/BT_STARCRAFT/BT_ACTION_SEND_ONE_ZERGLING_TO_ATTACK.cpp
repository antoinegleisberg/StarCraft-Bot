#include "BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK.h"
#include "BT_ACTION_BUILD_SPAWN_POOL.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK::BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK::Evaluate(void* data)
{
    return ReturnState(SendZergling(data));
}

std::string BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK::GetDescription()
{
    return "SEND ZERGLING TO ATTACK";
}


BT_NODE::State BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK::SendZergling(void* data)
{
    Data* pData = (Data*)data;

    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : myUnits)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Zergling && unit->isIdle())
        {
            // player start location
            //BWAPI::Broodwar->self()->getStartLocation();
            // all start locations
            BWAPI::TilePosition enemyLocation1 = BWAPI::Broodwar->getStartLocations()[0];
            BWAPI::TilePosition enemyLocation2 = BWAPI::Broodwar->getStartLocations()[1];

            std::cout << "ennemy : " << BWAPI::Broodwar->enemy() << std::endl;
            std::cout << "ennemy location: " << enemyLocation1.x << " " << enemyLocation1.y << std::endl;
            std::cout << "ennemy location: " << enemyLocation2.x << " " << enemyLocation2.y << std::endl;

            BWAPI::TilePosition enemyLocation = enemyLocation1;

            if (BWAPI::Broodwar->self()->getStartLocation() == enemyLocation1)
            {
                enemyLocation = enemyLocation2;
            }
            // enemy start location
            //BWAPI::TilePosition ennemyLocation = BWAPI::Broodwar->enemy()->getStartLocation();

            // if the unit is not in the enemy base, send it there
            unit->attack(BWAPI::Position(enemyLocation));

            BWAPI::Unit ennemy = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getUnitsOnTile(enemyLocation));


            // If an enemy was found, right click it with the unit in order to start harvesting

            bool randX = rand() % 2;
			bool randY = rand() % 2;
            
            bool randX2 = rand() % 2;
            bool randY2 = rand() % 2;

            
            if (ennemy) { unit->rightClick(ennemy); }

			

            else {
                BWAPI::TilePosition patLoc = BWAPI::TilePosition(enemyLocation.x + 10* randX - 10 * randX2, enemyLocation.y + 10* randY - 10 * randY2);
                unit->patrol(BWAPI::Position(patLoc));

            }

            
        }
    }

    return BT_NODE::FAILURE;
}