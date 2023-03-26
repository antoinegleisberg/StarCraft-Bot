#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>
#include <Data.h>

//--------------------
class BT_ACTION_MANAGE_TROOPS : public BT_ACTION {
public:
    BT_ACTION_MANAGE_TROOPS(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;

    static BT_NODE::State FillSquads(void* data);
    static void AssignNewTroop(BWAPI::Unit unit, Data* pData);
    static bool containsType(std::vector<BWAPI::UnitType> vec, const BWAPI::UnitType& elem);
};
//----------