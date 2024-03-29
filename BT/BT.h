#pragma once
//#define BT_DEBUG_VERBOSE
 
#include "BT_NODE.h"
#include "BT_LEAF.h"
#include "BT_ACTION.h"
#include "BT_DECORATOR.h"

//Composite notes
#include "BT_SEQUENCER.h"
#include "BT_SELECTOR.h"
#include "BT_PARALLEL_SEQUENCER.h"
#include "BT_PARALLEL_SELECTOR.h"

//Decorators
#include "BT_DECO_CONDITION.h"
#include "BT_DECO_COND_GREATER_THAN.h"
#include "BT_DECO_COND_LESSER_THAN.h"

#include "BT_DECO_INVERTER.h"
#include "BT_DECO_REPEATER.h"
#include "BT_DECO_RETURN_FAILURE.h"
#include "BT_DECO_RETURN_SUCCESS.h"
#include "BT_DECO_UNTIL_FAILURE.h"
#include "BT_DECO_UNTIL_SUCCESS.h"

// Conditions
#include "BT_CONDITION.h"
#include "BT_COND_GREATER_THAN.h"
#include "BT_COND_LESSER_THAN.h"

///Decorator Conditions
#include "BT_DECO_CONDITION_NOT_ENOUGH_WORKERS.h"
#include "BT_DECO_CONDITION_SEND_ZERGLING.h"
#include "BT_DECO_CONDITION_MORPH_OVERLORDS.h"
#include "BT_DECO_CONDITION_MORPH_ZERGLINGS.h"

#include "BT_DECO_CONDITION_BUILD_HATCHERY.h"
#include "BT_DECO_CONDITION_BUILD_REFINERY.h"

#include "BT_DECO_CONDITION_STARTED_PHASE2.h"

#include "BT_DECO_CONDITION_BUILD_HYDRALISK_DEN.h"
#include "BT_DECO_CONDITION_BUILD_LAIR.h"
#include "BT_DECO_CONDITION_BUILD_SPIRE.h"
#include "BT_DECO_CONDITION_BUILD_QUEENS_NEST.h"

///Actions
#include "BT_ACTION_IDLE.h"
#include "BT_ACTION_WAIT.h"
#include "BT_ACTION_LOG.h"

#include "BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES.h"

#include "BT_ACTION_BUILD_4POOL_ARMY.h"
#include "BT_ACTION_LAUNCH_4POOL_ATTACK.h"

#include "BT_ACTION_TRAIN_WORKER.h"
#include "BT_ACTION_BUILD_SPAWN_POOL.h"
#include "BT_ACTION_MORPH_OVERLORDS.h"
#include "BT_ACTION_MORPH_ZERGLINGS.h"

#include "BT_ACTION_BUILD_HATCHERY.h"
#include "BT_ACTION_BUILD_REFINERY.h"

#include "BT_ACTION_MANAGE_TROOPS.h"
#include "BT_ACTION_ORDER_SQUADS.h"

#include "BT_ACTION_TRAIN_UNITS.h"
#include "BT_ACTION_BUILD_HYDRALISK_DEN.h"
#include "BT_ACTION_BUILD_LAIR.h"
#include "BT_ACTION_BUILD_SPIRE.h"
#include "BT_ACTION_BUILD_QUEENS_NEST.h"