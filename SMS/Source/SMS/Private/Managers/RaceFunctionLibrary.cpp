
#include "Managers/RaceFunctionLibrary.h"


bool URaceFunctionLibrary::IsReplacementPossible(int OwnTeamPts, int EnemyTeamPts)
{
	return EnemyTeamPts >= OwnTeamPts + 6 ;
}

