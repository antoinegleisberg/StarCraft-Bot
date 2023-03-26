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

	bool finishedPhase1;
	bool startedPhase2;
	int additionalZerglingsTrained;
	int nDeadZerglings;

	// Management des escouades
	std::vector< BWAPI::Unitset > squads;
	std::vector< std::string> squadStatus;
	std::vector< int> squadCapacity;

	//Management des Troupes d'attaques 
	std::unordered_set<BWAPI::Unit> Troops;
	std::unordered_set<BWAPI::Unit> TroopsPhase1;
	std::vector<BWAPI::UnitType> TypesOfTroops;

	std::vector<BWAPI::UnitType> BestAvailableUnitTypes;

	// Management de stratégie
	bool ennemyLocFound;
	int  nbzergPhase1Stored;
	BWAPI::TilePosition ennemyLoc;
	int DeceasedUnits;
	bool message;

	std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;
	std::unordered_set<BWAPI::Unit> unitsFarmingVespene;
};
