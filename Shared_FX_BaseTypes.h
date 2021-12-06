#pragma once

#include "stdint.h"
typedef int32_t Integer;

typedef unsigned LongWord;
typedef unsigned short Word;
typedef unsigned char Byte;
typedef Byte BYTE;

typedef float Single;
typedef double Double;

namespace shared_FX
{
	
	namespace FXCommTCP
	{
		typedef double TFXPosition;		
		typedef float TFXVelocity;
		typedef float TFXAcceleration;
		typedef float TFXJerk;
		typedef BYTE TFXPositionLimits;
		typedef Word TFXMoveTrack;
		typedef float TFXPositionWindow;
		typedef Word TFXPositionWindowTime;
		typedef double TFXPosToDigi;
		typedef double TFXVelToDigi;
		typedef LongWord TFXSafetyIO;
		typedef float TFXLightValue;
		typedef Byte TFXVacSwitch;
		typedef Word TFXVacOptions;
		typedef LongWord TFXTime;
		typedef Word TFXVacDetectVal;
		typedef Word TFXVacState;
		typedef Byte TFXVacError;

		typedef Single TFXVolt;
		typedef Single TFXForce;
		typedef Single TFXForceRate;
		typedef Single TFXCurrent;

		
		typedef LongWord TFXCount;

		typedef Byte TFXSwitch;
		typedef Integer TFXSwitchAnalog;
		typedef float TFXFactor;

		typedef LongWord TFXStateIO;

		typedef Single TFXForceToDist;
		typedef LongWord TFXStartLevelMode;
	}
}
