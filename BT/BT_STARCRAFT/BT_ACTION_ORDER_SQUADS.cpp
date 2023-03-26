#include "BT_ACTION_ORDER_SQUADS.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_ORDER_SQUADS::BT_ACTION_ORDER_SQUADS(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_ORDER_SQUADS::Evaluate(void* data)
{
    return ReturnState(OrderSquads(data));
}

std::string BT_ACTION_ORDER_SQUADS::GetDescription()
{
    return "GIVE ORDERS TO SQUADS";
}


BT_NODE::State BT_ACTION_ORDER_SQUADS::OrderSquads(void* data)
{
    //std::cout << "trying orders" << std::endl;

    Data* pData = (Data*)data;

    if (!pData->finishedPhase1) return BT_NODE::SUCCESS;

    //get ennemy location once for all
    if (!pData->ennemyLocFound) {
        BWAPI::TilePosition enemyLocation1 = BWAPI::Broodwar->getStartLocations()[0];
        BWAPI::TilePosition enemyLocation2 = BWAPI::Broodwar->getStartLocations()[1];
        BWAPI::TilePosition enemyLocation = enemyLocation1;
        if (BWAPI::Broodwar->self()->getStartLocation() == enemyLocation1)
        {
            enemyLocation = enemyLocation2;
        }
        pData->ennemyLoc = enemyLocation;
        pData->ennemyLocFound = true;
    }

    // Send strong squads in waves of 2

    int count = 0;
    for (int i = 0; i < pData->squads.size(); i++) {
        if (pData->squadStatus[i].compare("READY FOR ATTACK") == 0) {
            count += 1;
        }
    }
    
    //std::cout << "nb of squads ready to attack " << count << std::endl;
    if (count >= 2) {
        for (int i = 0; i < pData->squads.size(); i++) {
            if (pData->squadStatus[i].compare("READY FOR ATTACK") == 0) {
                pData->squads[i].attack(BWAPI::Position(pData->ennemyLoc));
                pData->squadStatus[i] = "GOING ON ATTACK";
            }
        }
    }

    // Send units to attack
    for (int i = 0; i < pData->squads.size(); i++) {
        // Check the unit type, if it is a Zergling, attack
        if (pData->squadStatus[i].compare("GOING ON ATTACK") == 0) {
            // make the squad target the closest enemy unit
            BWAPI::Unitset ennemyUnits = BWAPI::Broodwar->getUnitsInRadius(BWAPI::Position(pData->ennemyLoc), 1000, BWAPI::Filter::IsEnemy);
            BWAPI::Unit ennemy = Tools::GetClosestUnitTo(pData->squads[i].getPosition(), ennemyUnits);

            if (ennemy) {
                for (BWAPI::Unit unit : pData->squads[i]) {
                    Tools::SmartRightClick(unit, ennemy);
                }
            }

            // if we didn't find an ennemy, look around in the ennemy base to find one
            else {
                bool randX = rand() % 2;
                bool randY = rand() % 2;

                bool randX2 = rand() % 2;
                bool randY2 = rand() % 2;
                BWAPI::Position enemyLocation = BWAPI::Position(pData->ennemyLoc);
                BWAPI::TilePosition targetPosition = BWAPI::TilePosition(enemyLocation.x + 10 * randX - 10 * randX2, enemyLocation.y + 10 * randY - 10 * randY2);
                for (BWAPI::Unit unit : pData->squads[i]) {
                    unit->attack(BWAPI::Position(targetPosition));
                }

            }
        }
    }

    return BT_NODE::SUCCESS;

}


