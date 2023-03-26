#include "BT_ACTION_MANAGE_TROOPS.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_MANAGE_TROOPS::BT_ACTION_MANAGE_TROOPS(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_MANAGE_TROOPS::Evaluate(void* data)
{
    return ReturnState(FillSquads(data));
}

std::string BT_ACTION_MANAGE_TROOPS::GetDescription()
{
    return "MANAGE TROOPS IN SQUADS";
}


BT_NODE::State BT_ACTION_MANAGE_TROOPS::FillSquads(void* data)
{
    //std::cout << "trying managing" << std::endl;

    Data* pData = (Data*)data;

    if (!pData->finishedPhase1) return BT_NODE::SUCCESS;

    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();

    // detecter les unités décédées
    std::vector<BWAPI::Unit> DeceasedUnits;
    for (BWAPI::Unit troop : pData->Troops) {
        if (!myUnits.contains(troop)) {
            std::cout << "deceased unit detected" << std::endl;
            DeceasedUnits.push_back(troop);
        }
    }

    //Les enlever des escouades
    for (int j = 0; j < DeceasedUnits.size(); j++) {
        pData->Troops.erase(DeceasedUnits[j]);

        for (int i = 0; i < pData->squads.size(); i++) {
            if (pData->squads[i].contains(DeceasedUnits[j])) {
                pData->squads[i].erase(DeceasedUnits[j]);
                pData->squadCapacity[i] -= 1;
                pData->DeceasedUnits += 1;

                // Si l'escouade est vide on la supprime 
                if (pData->squadCapacity[i] == 0) {
                    pData->squads.erase(pData->squads.begin() + i);
                    pData->squadCapacity.erase(pData->squadCapacity.begin() + i);
                    pData->squadStatus.erase(pData->squadStatus.begin() + i);
                }

            }

        }
    }
    
    //Rajouter les nouvelles unités capables d'attaquer dans les esquades 
    for (BWAPI::Unit unit : myUnits) {
        BWAPI::UnitType TypeofUnit = unit->getType();
        if (containsType(pData->TypesOfTroops, TypeofUnit) && !pData->Troops.contains(unit)) {
            pData->Troops.insert(unit);
            std::cout << "trying to assign" << std::endl;
            AssignNewTroop(unit, pData);
        }
    }

    return BT_NODE::SUCCESS;
}


bool BT_ACTION_MANAGE_TROOPS::containsType(std::vector<BWAPI::UnitType> vec, const BWAPI::UnitType& elem)
{
    bool result = false;
    if (find(vec.begin(), vec.end(), elem) != vec.end())
    {
        result = true;
    }
    return result;
}


void BT_ACTION_MANAGE_TROOPS::AssignNewTroop(BWAPI::Unit unit, Data* pData) {
    // Range l'unité qui vient d'être créée dans la bonne escouade (pour l'instant la première qui n'est pas encore pleine)
    bool assigned = false;
    for (int i = 0; i < pData->squads.size();i++) {
        if (pData->squadCapacity[i] < 5 && pData->squadStatus[i].compare("IDLE") == 0) { // si pas encore pleine
            pData->squads[i].insert(unit); //assign unit to squad
            pData->squadCapacity[i] += 1;  // update squad capacity
            assigned = true;
            
            // check if squad is thus filled , send it to attack if filled
            if (pData->squadCapacity[i] == 5 ) {
                pData->squadStatus[i] = "READY FOR ATTACK";
            }
            break;
        }
    }
    if (!assigned) {
        //Créer nouvelle escouade
        BWAPI::Unitset newsquad;
        newsquad.insert(unit);
        pData->squads.push_back( newsquad);
        pData->squadCapacity.push_back(1);
        pData->squadStatus.push_back("IDLE");

    }

    std::cout <<"nb of squads " << pData->squadCapacity.size() << std::endl;
    
}