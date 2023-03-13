#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES : public BT_ACTION {
public:
    BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State SendWorkersToCollectResources(void* data);

    static bool WantMoreMinerals(void* data);
    static bool WantMoreGas(void* data);
};
//----------