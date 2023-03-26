#pragma once
#include <cassert>
#include "BT_DECO_CONDITION.h"

//Evaluates the specified conditional task. If the conditional task returns success then the child task is run and the child status is returned. If the conditional task does not
// return success then the child task is not run and a failure status is immediately returned.
// 
//--------------------
class BT_DECO_CONDITION_BUILD_HYDRALISK_DEN : public BT_DECO_CONDITION {
public:
    BT_DECO_CONDITION_BUILD_HYDRALISK_DEN(std::string name, BT_NODE* parent);
    std::string GetDescription() override;

    static bool DoWeBuildHydraliskDen(void* data);

};
//----------