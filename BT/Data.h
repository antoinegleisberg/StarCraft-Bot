#pragma once
#include <unordered_set>
#include <BWAPI.h>

#define THRESHOLD1_MINERALS 200
#define THRESHOLD1_UNUSED_SUPPLY 2

#define NWANTED_WORKERS_TOTAL 9
#define NWANTED_WORKERS_FARMING_MINERALS 8
#define NWANTED_WORKERS_FARMING_VESPENE 2


class Data {
public:
	int currMinerals;
	int thresholdMinerals;
	int currSupply;
	int thresholdSupply;

	int nWantedWorkersTotal;
	int nWantedWorkersFarmingMinerals;
	int nWantedWorkersFarmingVespene;
	

	int nMorphingLarvaOverlords;
	int nMorphingLarvaZerglings;

	int nZerglingBase;

	std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;
	std::unordered_set<BWAPI::Unit> unitsFarmingVespene;
};
