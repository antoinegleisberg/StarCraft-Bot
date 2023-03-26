#include "StarterBot.h"

StarterBot::StarterBot()
{
    pData = new Data();
    
    // General info
    pData->currMinerals = 0;
    pData->thresholdMinerals = THRESHOLD1_MINERALS;
    pData->currSupply = 0;
    pData->thresholdSupply = THRESHOLD1_UNUSED_SUPPLY;
    pData->nMorphingLarvaOverlords = 0;
    pData->nZerglingBase = 0;

    // Section for resource farming
	pData->nMinWantedWorkersFarmingMinerals = NMIN_WANTED_WORKERS_FARMING_MINERALS;
	pData->nMinWantedWorkersFarmingGas = NMIN_WANTED_WORKERS_FARMING_GAS;
	pData->nMaxWantedWorkersFarmingMinerals = NMAX_WANTED_WORKERS_FARMING_MINERALS;
	pData->nMaxWantedWorkersFarmingGas = NMAX_WANTED_WORKERS_FARMING_GAS;

	// Section for 4-Pool attack
	pData->finishedPhase1 = false;
    pData->startedPhase2 = false;
    pData->additionalZerglingsTrained = 0;
    pData->nDeadZerglings = 0;

    //management of troops phase 2
    pData->TypesOfTroops.push_back(BWAPI::UnitTypes::Zerg_Mutalisk);
    pData->TypesOfTroops.push_back(BWAPI::UnitTypes::Zerg_Hydralisk);
    pData->TypesOfTroops.push_back(BWAPI::UnitTypes::Zerg_Zergling);
    pData->TypesOfTroops.push_back(BWAPI::UnitTypes::Zerg_Ultralisk);
    pData->ennemyLocFound = false;
    pData->message = false;
    pData->nbzergPhase1Stored = 0;
    pData->DeceasedUnits = 0;

    // Train troops
    pData->BestAvailableUnitTypes = { BWAPI::UnitTypes::Zerg_Zergling };

    pBT = new BT_DECORATOR("EntryPoint", nullptr);
    
    // Root node
    BT_PARALLEL_SEQUENCER* pParallelSeq = new BT_PARALLEL_SEQUENCER("MainParallelSequence", pBT, 30);

	// Send idle workers to collect resources
	BT_DECO_REPEATER* pSendWorkersToCollectResourcesRepeater = new BT_DECO_REPEATER("RepeatForeverSendWorkersToCollectResources", pParallelSeq, 0, true, false, false);
	BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES* pSendWorkersToCollectResourcesAction = new BT_ACTION_SEND_IDLE_WORKERS_TO_COLLECT_RESOURCES("SendWorkersToCollectResources", pSendWorkersToCollectResourcesRepeater);

    // Form the attack and base development strategy (everything that is not repetitive actions)
	BT_PARALLEL_SEQUENCER* pParallelSeqAttackStrategy = new BT_PARALLEL_SEQUENCER("AttackStrategy", pParallelSeq, 30);

    // Phase 1: Make a 4-Pool attack
    BT_SEQUENCER* p4PoolAttackSeq = new BT_SEQUENCER("4PoolAttackSequence", pParallelSeqAttackStrategy, 30);
    
    // Phase 1 Step 1: Make a spawn pool
	BT_DECO_UNTIL_SUCCESS* pBuildSpawnPoolUntilSuccess = new BT_DECO_UNTIL_SUCCESS("RepeatForeverBuildSpawnPool", p4PoolAttackSeq);
	BT_ACTION_BUILD_SPAWN_POOL* pBuildSpawnPool = new BT_ACTION_BUILD_SPAWN_POOL("BuildSpawnPool", pBuildSpawnPoolUntilSuccess);
    
    // Phase 1 Step 2: Build units
	BT_DECO_UNTIL_SUCCESS* pBuild4PoolArmyDecorator = new BT_DECO_UNTIL_SUCCESS("4PoolArmyCreationDecorator", p4PoolAttackSeq);
	BT_ACTION_BUILD_4POOL_ARMY* pBuild4PoolArmy = new BT_ACTION_BUILD_4POOL_ARMY("Build4PoolArmy", pBuild4PoolArmyDecorator);

	// Phase 1 Step 3: Send the army to attack + send 2 additional zergling waves
	BT_DECO_REPEATER* pLaunch4PoolAttackRepeater = new BT_DECO_REPEATER("RepeatForeverLaunch4PoolAttack", p4PoolAttackSeq, 0, true, false, false);
	BT_ACTION_LAUNCH_4POOL_ATTACK* pLaunch4PoolAttack = new BT_ACTION_LAUNCH_4POOL_ATTACK("Launch4PoolAttack", pLaunch4PoolAttackRepeater);

    //////////////////////////////////////////////////////////////////////////
    // Phase 2 : Parallel sequencer to develop multiple aspects of the base //
	//////////////////////////////////////////////////////////////////////////
    
    // Phase 2 Root
    BT_DECO_REPEATER* pRepeatPhase2 = new BT_DECO_REPEATER("RepeatPhase2", pParallelSeqAttackStrategy, 0, true, false, false);
    BT_DECO_CONDITION_STARTED_PHASE2* pConditionStartPhase2 = new BT_DECO_CONDITION_STARTED_PHASE2("ConditionStartPhase2", pRepeatPhase2);
    BT_PARALLEL_SEQUENCER* pParallelAttackStrategy = new BT_PARALLEL_SEQUENCER("AttackStrategy", pConditionStartPhase2, 30);
    
    // Phase 2 Thread 1 : Troop Management and Attack Management
    BT_DECO_REPEATER* pRepeatPhase2Attack = new BT_DECO_REPEATER("RepeatPhase2Attack", pParallelAttackStrategy, 0, true, false, true);
    BT_DECO_CONDITION_STARTED_PHASE2* pConditionStartPhase2Attack = new BT_DECO_CONDITION_STARTED_PHASE2("ConditionStartPhase2", pRepeatPhase2Attack);
    BT_SEQUENCER* pGiveOrdersAfterStructuring = new BT_SEQUENCER("GiveOrdersAfterStructuring", pConditionStartPhase2Attack, 2);
    BT_ACTION_MANAGE_TROOPS* pManageTroops = new BT_ACTION_MANAGE_TROOPS("ManageTroops", pGiveOrdersAfterStructuring);
    BT_ACTION_ORDER_SQUADS* pOrderSquads = new BT_ACTION_ORDER_SQUADS("OrderSquads", pGiveOrdersAfterStructuring);

    // Phase 2 Thread 2 : Build troops
    BT_DECO_REPEATER* pBuildTroopsForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildTroops", pParallelAttackStrategy, 0, true, false, false);
    BT_ACTION_TRAIN_UNITS* pTrainUnits = new BT_ACTION_TRAIN_UNITS("TrainUnits", pBuildTroopsForeverRepeater);

	// Phase 2 Thread 3: Train workers
    BT_DECO_REPEATER* pTrainingWorkersForeverRepeater = new BT_DECO_REPEATER("RepeatForeverTrainingWorkers", pParallelAttackStrategy, 0, true, false, false);
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS* pNotEnoughWorkers = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS("NotEnoughWorkers", pTrainingWorkersForeverRepeater);
    BT_ACTION_TRAIN_WORKER* pTrainWorker = new BT_ACTION_TRAIN_WORKER("TrainWorker", pNotEnoughWorkers);

    // Phase 2 Thread 4 : Continuously build Hatcheries
    BT_DECO_UNTIL_SUCCESS* pBuildHatcheryUntilSuccess = new BT_DECO_UNTIL_SUCCESS("RepeatForeverBuildHatchery", pParallelAttackStrategy);
    BT_DECO_CONDITION_BUILD_HATCHERY* pBuildHatcheryCondition = new BT_DECO_CONDITION_BUILD_HATCHERY("BuildHatchery", pBuildHatcheryUntilSuccess);
    BT_ACTION_BUILD_HATCHERY* pBuildHatchery = new BT_ACTION_BUILD_HATCHERY("BuildHatchery", pBuildHatcheryCondition);

    // Phase 2 Thread 5 : Continuously build Gas refineries
    BT_DECO_UNTIL_SUCCESS* pBuildRefineryUntilSuccess = new BT_DECO_UNTIL_SUCCESS("RepeatForeverBuildRefinery", pParallelAttackStrategy);
    BT_DECO_CONDITION_BUILD_REFINERY* pBuildRefineryCondition = new BT_DECO_CONDITION_BUILD_REFINERY("BuildRefinery", pBuildRefineryUntilSuccess);
    BT_ACTION_BUILD_REFINERY* pBuildRefinery = new BT_ACTION_BUILD_REFINERY("BuildRefinery", pBuildRefineryCondition);

    // Phase 2 Thread 6 : Continuously morph To Overlords
	BT_DECO_REPEATER* pMorphOverlordsForeverRepeater = new BT_DECO_REPEATER("RepeatForeverMorphOverlords", pParallelAttackStrategy, 0, true, false, false);
    BT_DECO_CONDITION_MORPH_OVERLORDS* pMorphOverlordsCondition = new BT_DECO_CONDITION_MORPH_OVERLORDS("MorphOverlords", pMorphOverlordsForeverRepeater);
	BT_ACTION_MORPH_OVERLORDS* pMorphOverlords = new BT_ACTION_MORPH_OVERLORDS("MorphOverlords", pMorphOverlordsCondition);

	// Phase 2 Thread 7 : Develop the buildings of the base
    // These are buildings of the tech tree, built only once
	BT_SEQUENCER* pDevelopBaseBuildingsSeq = new BT_SEQUENCER("DevelopBaseBuildingsSeq", pParallelAttackStrategy, 30);
    
    BT_DECO_UNTIL_SUCCESS* pBuildHydraliskDenUntilSuccess = new BT_DECO_UNTIL_SUCCESS("BuildHydraliskDenUntilSuccess", pDevelopBaseBuildingsSeq);
	BT_DECO_CONDITION_BUILD_HYDRALISK_DEN* pBuildHydraliskDenCondition = new BT_DECO_CONDITION_BUILD_HYDRALISK_DEN("BuildHydraliskDen", pBuildHydraliskDenUntilSuccess);
	BT_ACTION_BUILD_HYDRALISK_DEN* pBuildHydraliskDen = new BT_ACTION_BUILD_HYDRALISK_DEN("BuildHydraliskDen", pBuildHydraliskDenCondition);
    
	BT_DECO_UNTIL_SUCCESS* pBuildLairUntilSuccess = new BT_DECO_UNTIL_SUCCESS("BuildLairUntilSuccess", pDevelopBaseBuildingsSeq);
	BT_DECO_CONDITION_BUILD_LAIR* pBuildLairCondition = new BT_DECO_CONDITION_BUILD_LAIR("BuildLair", pBuildLairUntilSuccess);
	BT_ACTION_BUILD_LAIR* pBuildLair = new BT_ACTION_BUILD_LAIR("BuildLair", pBuildLairCondition);
    
	BT_DECO_UNTIL_SUCCESS* pBuildSpireUntilSuccess = new BT_DECO_UNTIL_SUCCESS("BuildSpireUntilSuccess", pDevelopBaseBuildingsSeq);
	BT_DECO_CONDITION_BUILD_SPIRE* pBuildSpireCondition = new BT_DECO_CONDITION_BUILD_SPIRE("BuildSpire", pBuildSpireUntilSuccess);
	BT_ACTION_BUILD_SPIRE* pBuildSpire = new BT_ACTION_BUILD_SPIRE("BuildSpire", pBuildSpireCondition);
    
	BT_DECO_UNTIL_SUCCESS* pBuildQueensNestUntilSuccess = new BT_DECO_UNTIL_SUCCESS("BuildQueensNestUntilSuccess", pDevelopBaseBuildingsSeq);
	BT_DECO_CONDITION_BUILD_QUEENS_NEST* pBuildQueensNestCondition = new BT_DECO_CONDITION_BUILD_QUEENS_NEST("BuildQueensNest", pBuildQueensNestUntilSuccess);
	BT_ACTION_BUILD_QUEENS_NEST* pBuildQueensNest = new BT_ACTION_BUILD_QUEENS_NEST("BuildQueensNest", pBuildQueensNestCondition);
    
	// We could continue with hive and ultralisk cavern ... but it is too slow against ennemies
}

// Called when the bot starts!
void StarterBot::onStart()
{
    // Set our BWAPI options here    
	BWAPI::Broodwar->setLocalSpeed(5);
    BWAPI::Broodwar->setFrameSkip(0);
    
    // Enable the flag that tells BWAPI top let users enter input while bot plays
    BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);

    // Call MapTools OnStart
    m_mapTools.onStart();
}

// Called on each frame of the game
void StarterBot::onFrame()
{
    // Update our MapTools information
    m_mapTools.onFrame();

    pData->currMinerals = BWAPI::Broodwar->self()->minerals();
    pData->currSupply = Tools::GetUnusedSupply(true);
    
    if (pBT != nullptr && pBT->Evaluate(pData) != BT_NODE::RUNNING)
    {
        delete (BT_DECORATOR*)pBT;
    }    

    
    // Draw unit health bars, which brood war unfortunately does not do
    Tools::DrawUnitHealthBars();

    // Draw some relevent information to the screen to help us debug the bot
    drawDebugInformation();
}

// Called whenever the game ends and tells you if you won or not
void StarterBot::onEnd(bool isWinner)
{
    std::cout << "We " << (isWinner ? "won!" : "lost!") << "\n";
}

void StarterBot::sendIdleZerglingsToAttack()
{

    // Let's send all of our starting workers to the closest mineral to them
    // First we need to loop over all of the units that we (BWAPI::Broodwar->self()) own
    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : myUnits)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Zergling && unit->isIdle())
        {

            // player start location
            BWAPI::Broodwar->self()->getStartLocation();
            // all start locations
            BWAPI::Broodwar->getStartLocations();
            // enemy start location
            BWAPI::TilePosition ennemyLocation = BWAPI::Broodwar->enemy()->getStartLocation();

            // if the unit is not in the enemy base, send it there
            unit->attack(BWAPI::Position(ennemyLocation));

			BWAPI::Unit ennemy = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getUnitsOnTile(ennemyLocation));
   

            // If a valid mineral was found, right click it with the unit in order to start harvesting
            
            if (ennemy) { unit->rightClick(ennemy); }
        }
    }
    
}

// Draw some relevent information to the screen to help us debug the bot
void StarterBot::drawDebugInformation()
{
    // BWAPI::Broodwar->drawTextScreen(BWAPI::Position(10, 10), "Hello, Dune!\n");
    Tools::DrawUnitCommands();
    Tools::DrawUnitBoundingBoxes();
}

// Called whenever a text is sent to the game by a user
void StarterBot::onSendText(std::string text) 
{ 
    if (text == "/map")
    {
        m_mapTools.toggleDraw();
    }
}

# pragma region UnitEvents


// Called whenever a unit is destroyed, with a pointer to the unit
void StarterBot::onUnitDestroy(BWAPI::Unit unit)
{
	if (unit->getType() == BWAPI::UnitTypes::Zerg_Zergling) pData->nDeadZerglings++;
    //if the unit is farming then remove it from data structure
    if (pData->unitsFarmingMinerals.contains(unit)) pData->unitsFarmingMinerals.erase(unit);
	if (pData->unitsFarmingVespene.contains(unit)) pData->unitsFarmingVespene.erase(unit);
}

// Called whenever a unit is morphed, with a pointer to the unit
// Zerg units morph when they turn into other units
void StarterBot::onUnitMorph(BWAPI::Unit unit)
{
	if (unit->getType()==BWAPI::UnitTypes::Zerg_Overlord)
	{
        pData->nMorphingLarvaOverlords--;
	}
    
    if (unit->getType() == BWAPI::UnitTypes::Zerg_Zergling)
    {
        pData->nMorphingLarvaZerglings--;
		pData->nZerglingBase++;
    }
}

// Called whenever a unit is created, with a pointer to the destroyed unit
// Units are created in buildings like barracks before they are visible, 
// so this will trigger when you issue the build command for most units
void StarterBot::onUnitCreate(BWAPI::Unit unit)
{ 
	
}

// Called whenever a unit finished construction, with a pointer to the unit
void StarterBot::onUnitComplete(BWAPI::Unit unit)
{
    if (unit->getType() == BWAPI::UnitTypes::Zerg_Hydralisk_Den) {
        pData->BestAvailableUnitTypes.clear();
        pData->BestAvailableUnitTypes.push_back(BWAPI::UnitTypes::Zerg_Hydralisk);
    }
    else if (unit->getType() == BWAPI::UnitTypes::Zerg_Spire) {
		pData->BestAvailableUnitTypes.push_back(BWAPI::UnitTypes::Zerg_Mutalisk);
    }
    else if (unit->getType() == BWAPI::UnitTypes::Zerg_Ultralisk_Cavern) {
		pData->BestAvailableUnitTypes.clear();
		pData->BestAvailableUnitTypes.push_back(BWAPI::UnitTypes::Zerg_Ultralisk);
        pData->BestAvailableUnitTypes.push_back(BWAPI::UnitTypes::Zerg_Mutalisk);
    }
}

// Called whenever a unit appears, with a pointer to the destroyed unit
// This is usually triggered when units appear from fog of war and become visible
void StarterBot::onUnitShow(BWAPI::Unit unit)
{ 
	
}

// Called whenever a unit gets hidden, with a pointer to the destroyed unit
// This is usually triggered when units enter the fog of war and are no longer visible
void StarterBot::onUnitHide(BWAPI::Unit unit)
{ 
	
}

void StarterBot::onUnitRenegade(BWAPI::Unit unit)
{

}

// Called whenever a unit switches player control
// This usually h