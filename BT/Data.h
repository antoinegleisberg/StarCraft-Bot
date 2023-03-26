#pragma once
#include <unordered_set>
#include <BWAPI.h>

#define THRESHOLD1_MINERALS 200
#define THRESHOLD1_UNUSED_SUPPLY 2

#define NMIN_WANTED_WORKERS_FARMING_MINERALS 16
#define NMIN_WANTED_WORKERS_FARMING_GAS 6
#define NMAX_WANTED_WORKERS_FARMING_MINERALS 24
#define NMAX_WANTED_WORKERS_FARMING_GAS 6


class Data {
public:
	int currMinerals;
	int thresholdMinerals;
	int currSupply;
	int thresholdSupply;
	
	int nMinWantedWorkersFarmingMinerals;
	int nMinWantedWorkersFarmingGas;
	int nMaxWantedWorkersFarmingMinerals;
	int nMaxWantedWorkersFarmingGas;
	

	int nMorphingLarvaOverlords;
	int nMorphingLarvaZerglings;

	int nZerglingBase;

	bool startedPhase2;
	int additionalZerglingsTrained;
	int nDeadZerglings;

	std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;
	std::unordered_set<BWAPI::Unit> unitsFarmingVespene;
};
