#pragma once

#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>


class BT_ACTION_LAUNCH_4POOL_ATTACK : public BT_ACTION {
public:
    BT_ACTION_LAUNCH_4POOL_ATTACK(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State LaunchAttack(void* data);
};