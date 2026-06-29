#include "EHelmetColour.h"

FLinearColor HelmetColours::GetHelmetColour(EHelmetColour Color)
{
	switch (Color)
	{
	case EHelmetColour::Red:    return FLinearColor::Red;
	case EHelmetColour::Blue:   return FLinearColor::Blue;
	case EHelmetColour::White:  return FLinearColor::White;
	case EHelmetColour::Yellow: return FLinearColor::Yellow;
	default: return FLinearColor::White;
	}
}