
#include "Managers/TrackManager.h"


void UTrackManager::InitializeManager(const FTrackData& NewTrackData)
{
	SetHomeTeamTrackData(NewTrackData);
	SetInitialTrackType();
	OnTrackUpdateRequestDelegate.AddUObject(this, &UTrackManager::TryUpdateTrack);
}


void UTrackManager::SetInitialTrackType()
{
	UE_LOG(LogTemp, Warning, TEXT("SetInitialTrackType"));
	float Total = 0.f;
	for (const auto& Probability : TrackData.TrackTypeProbability)
	{
		Total += Probability.Value;
	}
	CurrentTrackType = GetNewTrackType(Total);
	FString name = UEnum::GetDisplayValueAsText(CurrentTrackType).ToString();
	UE_LOG(LogTemp, Error, TEXT("Type %s"), *name);
	name = UEnum::GetDisplayValueAsText(DeniedOption).ToString();
	UE_LOG(LogTemp, Error, TEXT("denied type %s"), *name);
}


void UTrackManager::TryUpdateTrack()
{
	UE_LOG(LogTemp, Error, TEXT("TryUpdateTrack"));
	float MaxChance = 1.f;
	float Random = FMath::RandRange(0.f, MaxChance);
	UE_LOG(LogTemp, Warning, TEXT("Random %f"), Random);
	if (Random <= TrackData.ChanceToChange) UpdateTrackType();
}


void UTrackManager::UpdateTrackType()
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateTrackType"));
	float Total = 0.f;
	for (const auto& Probability : TrackData.TrackTypeProbability)
	{
		if (Probability.Key != DeniedOption) Total += Probability.Value;
	}
	CurrentTrackType = GetNewTrackType(Total);
	FString name = UEnum::GetDisplayValueAsText(CurrentTrackType).ToString();
	UE_LOG(LogTemp, Error, TEXT("Type %s"), *name);
	name = UEnum::GetDisplayValueAsText(DeniedOption).ToString();
	UE_LOG(LogTemp, Error, TEXT("denied type %s"), *name);
}


ETrackTypes UTrackManager::GetNewTrackType(const float Total)
{
	UE_LOG(LogTemp, Warning, TEXT("Total %f"), Total);
	if (Total == 0.f) return ETrackTypes::Normal;
	float RandomNumber = FMath::FRandRange(0.f,Total);
	UE_LOG(LogTemp, Warning, TEXT("random %f"), RandomNumber);
	float Chance = 0.f;
	for (const auto& Probability : TrackData.TrackTypeProbability)
	{
		if (Probability.Key == DeniedOption) continue;
		ETrackTypes ProbabilityType = Probability.Key;
		Chance += Probability.Value;
		UE_LOG(LogTemp, Warning, TEXT("Chance %f"), Chance);
		if (RandomNumber <= Chance)
		{
			if (ProbabilityType == ETrackTypes::Hard) DeniedOption = ETrackTypes::Grip;
			else if (ProbabilityType == ETrackTypes::Grip) DeniedOption = ETrackTypes::Hard;
			else DeniedOption = ETrackTypes::None;
			return ProbabilityType;
		}
	}
	return ETrackTypes::Normal;
}


void UTrackManager::SetHomeTeamTrackData(const FTrackData& NewTrackData){TrackData = NewTrackData;}
float UTrackManager::GetGateModifier(int32 GateID)
{
	return TrackData.Gates[GateID].StartModifiers[CurrentTrackType];
}
float UTrackManager::GetDrivingModifier()
{
	return TrackData.DrivingModifiers[CurrentTrackType];
}
ETrackTypes UTrackManager::GetCurrentTrackType() const{return CurrentTrackType;}
