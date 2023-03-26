#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>
#include <Data.h>

//--------------------
class BT_ACTION_ORDER_SQUADS : public BT_ACTION {
public:
    BT_ACTION_ORDER_SQUADS(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;

    static BT_NODE::State OrderSquads(void* data);

};
//----------