// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Classes/AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	//GetPatrolPoints
	auto controlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	APatrollingGuard* patrollingGuard = Cast<APatrollingGuard>(controlledPawn);
	auto patrolPoints = patrollingGuard->patrolPoints;

	//Get Index and set new Waypoint
	if (ensure(patrolPoints.Num()>0)) {
		auto blackboardComp = OwnerComp.GetBlackboardComponent();
		int32 currentIndex = blackboardComp->GetValueAsInt(indexKey.SelectedKeyName);
		AActor* nextWaypoint = patrolPoints[currentIndex];
		blackboardComp->SetValueAsObject(currentWaypointKey.SelectedKeyName,nextWaypoint);

		//set new index
		int32 nextIndex = (currentIndex + 1) % patrolPoints.Num();
		blackboardComp->SetValueAsInt(indexKey.SelectedKeyName, nextIndex);
	}
	return EBTNodeResult::Succeeded;
}



