#include "StarterBot.h"

StarterBot::StarterBot()
{
    pBT = new BT_DECORATOR("EntryPoint", nullptr);

        
    BT_PARALLEL_SEQUENCER* pParallelSeq = new BT_PARALLEL_SEQUENCER("MainParallelSequence", pBT, 15);

    //Farming Minerals forever
    BT_DECO_REPEATER* pFarmingMineralsForeverRepeater = new BT_DECO_REPEATER("RepeatForeverFarmingMinerals", pParallelSeq, 0, true, false, false);
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS* pNotEnoughWorkersFarmingMinerals = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS("NotEnoughWorkersFarmingMinerals", pFarmingMineralsForeverRepeater);
    BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendWorkerToMinerals = new BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendWorkerToMinerals", pNotEnoughWorkersFarmingMinerals);


    //Farming Vespene forever
	BT_DECO_REPEATER* pFarmingVespeneForeverRepeater = new BT_DECO_REPEATER("RepeatForeverFarmingVespene", pParallelSeq, 0, true, false, false);
	BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_VESPENE* pNotEnoughWorkersFarmingVespene = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_VESPENE("NotEnoughWorkersFarmingVespene", pFarmingVespeneForeverRepeater);
	BT_ACTION_SEND_IDLE_WORKER_TO_VESPENE* pSendWorkerToVespene = new BT_ACTION_SEND_IDLE_WORKER_TO_VESPENE("SendWorkerToVespene", pNotEnoughWorkersFarmingVespene);
    

    //Training Workers
    BT_DECO_REPEATER* pTrainingWorkersForeverRepeater = new BT_DECO_REPEATER("RepeatForeverTrainingWorkers", pParallelSeq, 0, true, false, false);
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS* pNotEnoughWorkers = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS("NotEnoughWorkers", pTrainingWorkersForeverRepeater);
    BT_ACTION_TRAIN_WORKER* pTrainWorker = new BT_ACTION_TRAIN_WORKER("TrainWorker", pNotEnoughWorkers);

    //Build Additional Supply Provider
    BT_DECO_REPEATER* pBuildSupplyProviderForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildSupplyProvider", pParallelSeq, 0, true, false, false);
    BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY* pNotEnoughSupply = new BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY("NotEnoughSupply", pBuildSupplyProviderForeverRepeater);
    BT_ACTION_BUILD_SUPPLY_PROVIDER* pBuildSupplyProvider = new BT_ACTION_BUILD_SUPPLY_PROVIDER("BuildSupplyProvider", pNotEnoughSupply);

    // Build Spawning Pool
	BT_DECO_UNTIL_SUCCESS* pBuildSpawnPoolUntilSuccess = new BT_DECO_UNTIL_SUCCESS("RepeatForeverBuildSpawnPool", pParallelSeq);
	BT_DECO_CONDITION_BUILD_SPAWN_POOL* pBuildSpawnPoolCondition = new BT_DECO_CONDITION_BUILD_SPAWN_POOL("BuildSpawnPool", pBuildSpawnPoolUntilSuccess);
	BT_ACTION_BUILD_SPAWN_POOL* pBuildSpawnPool = new BT_ACTION_BUILD_SPAWN_POOL("BuildSpawnPool", pBuildSpawnPoolCondition);

    // Build Hatchery
    BT_DECO_UNTIL_SUCCESS* pBuildHatcheryUntilSuccess = new BT_DECO_UNTIL_SUCCESS("RepeatForeverBuildHatchery", pParallelSeq);
    BT_DECO_CONDITION_BUILD_HATCHERY* pBuildHatcheryCondition = new BT_DECO_CONDITION_BUILD_HATCHERY("BuildHatchery", pBuildHatcheryUntilSuccess);
    BT_ACTION_BUILD_HATCHERY* pBuildHatchery = new BT_ACTION_BUILD_HATCHERY("BuildHatchery", pBuildHatcheryCondition);

    // Build Refinery
    BT_DECO_UNTIL_SUCCESS* pBuildRefineryUntilSuccess = new BT_DECO_UNTIL_SUCCESS("RepeatForeverBuildRefinery", pParallelSeq);
    BT_DECO_CONDITION_BUILD_REFINERY* pBuildRefineryCondition = new BT_DECO_CONDITION_BUILD_REFINERY("BuildRefinery", pBuildRefineryUntilSuccess);
    BT_ACTION_BUILD_REFINERY* pBuildRefinery = new BT_ACTION_BUILD_REFINERY("BuildRefinery", pBuildRefineryCondition);

    
    // Morph To Overlords
	BT_DECO_REPEATER* pMorphOverlordsForeverRepeater = new BT_DECO_REPEATER("RepeatForeverMorphOverlords", pParallelSeq, 0, true, false, false);
    BT_DECO_CONDITION_MORPH_OVERLORDS* pMorphOverlordsCondition = new BT_DECO_CONDITION_MORPH_OVERLORDS("MorphOverlords", pMorphOverlordsForeverRepeater);
	BT_ACTION_MORPH_OVERLORDS* pMorphOverlords = new BT_ACTION_MORPH_OVERLORDS("MorphOverlords", pMorphOverlordsCondition);

    // Morph To Zerglings
    
    BT_DECO_REPEATER* pMorphZerglingsForeverRepeater = new BT_DECO_REPEATER("RepeatForeverMorphZerglings", pParallelSeq, 0, true, false, false);
    BT_DECO_CONDITION_MORPH_ZERGLINGS* pMorphZerglingsCondition = new BT_DECO_CONDITION_MORPH_ZERGLINGS("MorphZerglings", pMorphZerglingsForeverRepeater);
    BT_ACTION_MORPH_ZERGLINGS* pMorphZerglings = new BT_ACTION_MORPH_ZERGLINGS("MorphZerglings", pMorphZerglingsCondition);
    
    
    
    // Destroy Base
    //BT_DECO_REPEATER* pSendOneZerglingToAttackForeverRepeater = new BT_DECO_REPEATER("RepeatForeverDestroyBase", pParallelSeq, 0, true, false, false);
    //BT_DECO_CONDITION_DESTROY_BASE* pDestroyBaseCondition = new BT_DECO_CONDITION_DESTROY_BASE("DestroyBase", pDestroyBaseForeverRepeater);
    //BT_ACTION_DESTROY_BASE* pDestroyBase = new BT_ACTION_DESTROY_BASE("SendZergling", pDestroyBaseCondition);
    
    BT_DECO_REPEATER* pAttackProcedure = new BT_DECO_REPEATER("RepeatForeverTryingToAttack", pParallelSeq, 0, true, false, false);
    //If the preparations are done (enough Zergling and base built , then attack
    BT_DECO_CONDITION_BEGIN_ATTACK* pConditionToBeginAttack = new BT_DECO_CONDITION_BEGIN_ATTACK("BeginAttack", pAttackProcedure);

    
    BT_PARALLEL_SEQUENCER* pAttackTasks = new BT_PARALLEL_SEQUENCER("AttackParrallelSequence", pConditionToBeginAttack, 10);
    //////////
    
    
    // Envoyer tout les Zergling disponibles vers la base ennemie
    BT_DECO_REPEATER* pSupplyZergsToAttack = new BT_DECO_REPEATER("RepeatForeverSendOneZerglingToEnnemyBase", pAttackTasks, 0, true, false, false); // Jusqu'à la fin de l'attaque
   
    // Send One Zergling to Attack
    BT_DECO_REPEATER* pSendOneZerglingToAttackForeverRepeater = new BT_DECO_REPEATER("RepeatForeverSendOneZerglingToAttack", pParallelSeq, 0, true, false, false);
    BT_DECO_CONDITION_SEND_ZERGLING* pSendZerglingCondition = new BT_DECO_CONDITION_SEND_ZERGLING("SendZergling", pSendOneZerglingToAttackForeverRepeater);
    BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK* pSendZergling = new BT_ACTION_SEND_ONE_ZERGLING_TO_ATTACK("SendZergling", pSendZerglingCondition);
    //////////

    

    
    //Eliminer les ennemis sur le front
    BT_DECO_REPEATER* pKillEnnemies = new BT_DECO_REPEATER("KillEnnemies", pAttackTasks, 0, true, false, false); // Jusqu'à la fin de l'attaque
    BT_DECO_CONDITION_ENNEMY_PRESENCE* pEnnemyPresenceCondition = new BT_DECO_CONDITION_ENNEMY_PRESENCE("CheckEnnemyPresence", pKillEnnemies); // Si il existe un ennemy qui défend la base ennemie
    BT_ACTION_ATTACK_NEAREST_ENNEMY* pKill = new BT_ACTION_ATTACK_NEAREST_ENNEMY("Kill", pEnnemyPresenceCondition); // on le tue 
    //eliminer les batiments
    BT_DECO_REPEATER* pDestroyBaseBuildings = new BT_DECO_REPEATER("DestroyBase", pAttackTasks, 0, true, false, false); // Jusqu'à la fin de l'attaque
    BT_DECO_CONDITION_ENNEMY_ABSENCE* pEnnemyAbsenceCondition = new BT_DECO_CONDITION_ENNEMY_ABSENCE("CheckEnnemyAbsence", pDestroyBaseBuildings); // Si la base ennemie n'est pas défendu
    BT_ACTION_ATTACK_NEAREST_BUILDING* pDestroy = new BT_ACTION_ATTACK_NEAREST_BUILDING("Destroy", pEnnemyAbsenceCondition); // Alors on détruit la base 



    
    
    
    pData = new Data();
    pData->currMinerals = 0;
    pData->thresholdMinerals = THRESHOLD1_MINERALS;
    pData->currSupply = 0;
    pData->thresholdSupply = THRESHOLD1_UNUSED_SUPPLY;
    pData->nMorphingLarvaOverlords = 0;
	pData->nZerglingBase = 0;
    
    pData->nWantedWorkersTotal = NWANTED_WORKERS_TOTAL;
    pData->nWantedWorkersFarmingMinerals = NWANTED_WORKERS_FARMING_MINERALS;
	pData->nWantedWorkersFarmingVespene = NWANTED_WORKERS_FARMING_VESPENE;
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

# pragma region OldBehaviour
// Now replaced by the behaviour tree

// Send our idle workers to mine minerals so they don't just stand there
void StarterBot::sendIdleWorkersToMinerals()
{
    // Let's send all of our starting workers to the closest mineral to them
    // First we need to loop over all of the units that we (BWAPI::Broodwar->self()) own
    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : myUnits)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
        if (unit->getType().isWorker() && unit->isIdle())
        {
            // Get the closest mineral to this worker unit
            BWAPI::Unit closestMineral = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getMinerals());

            // If a valid mineral was found, right click it with the unit in order to start harvesting
            if (closestMineral) { unit->rightClick(closestMineral); }
        }
    }
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


// Train more workers so we can gather more income
void StarterBot::trainAdditionalWorkers()
{
    const BWAPI::UnitType workerType = BWAPI::Broodwar->self()->getRace().getWorker();
    const int workersWanted = 10;
    const int workersOwned = Tools::CountUnitsOfType(workerType, BWAPI::Broodwar->self()->getUnits());
    if (workersOwned < workersWanted)
    {
        // get the unit pointer to my depot
        const BWAPI::Unit myDepot = Tools::GetDepot();

        // if we have a valid depot unit and it's currently not training something, train a worker
        // there is no reason for a bot to ever use the unit queueing system, it just wastes resources
        if (myDepot && !myDepot->isTraining()) { myDepot->train(workerType); }
    }
}

// Build more supply if we are going to run out soon
void StarterBot::buildAdditionalSupply()
{
    // Get the amount of supply supply we currently have unused
    const int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();

    // If we have a sufficient amount of supply, we don't need to do anything
    if (unusedSupply >= 2) { return; }

    // Otherwise, we are going to build a supply provider
    const BWAPI::UnitType supplyProviderType = BWAPI::Broodwar->self()->getRace().getSupplyProvider();

    const bool startedBuilding = Tools::BuildBuilding(supplyProviderType);
    if (startedBuilding)
    {
        BWAPI::Broodwar->printf("Started Building %s", supplyProviderType.getName().c_str());
    }
}

# pragma endregion

// Draw some relevent information to the screen to help us debug the bot
void StarterBot::drawDebugInformation()
{
    BWAPI::Broodwar->drawTextScreen(BWAPI::Position(10, 10), "Hello, Dune!\n");
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

// Called whenever a unit switches player control
// This usually happens when a dark archon takes control of a unit
void StarterBot::onUnitRenegade(BWAPI::Unit unit)
{ 
	
}

# pragma endregion