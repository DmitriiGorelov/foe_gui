#pragma once

#include "Shared_FX_DIO.h"

namespace eDIOResult
{
	eDIOResult::E BoolToDIO(bool var)
	{
		switch(var)
		{
			case true:
				return dioTRUE;
			case false:
				return dioFALSE;
			default:
				return dioUNKNOWN;
		}
	}

	bool DIOToBool(eDIOResult::E var)
	{
		switch(var)
		{
			case dioTRUE:
				return true;
			case dioFALSE:
				return false;
			default:
				return false;
		}
	}

	eDIOResult::E IntToDIO(int var)
	{
		switch (var)
		{
		case 1:
			return dioTRUE;
		case 0:
			return dioFALSE;
		default:
			return dioUNKNOWN;
		}
	}

	bool DIOToInt(eDIOResult::E var)
	{
		switch (var)
		{
		case dioTRUE:
			return true;
		case dioFALSE:
			return false;
		default:
			return false;
		}
	}
}

// FW20180919 added {
namespace eLogicEx
{
	eLogicEx::E BoolToLogicEx(bool var)
	{
		switch (var)
		{
			case true:
				return eLogicEx::valTRUE;
			case false:
				return eLogicEx::valFALSE;
			default:
				return eLogicEx::valUNKNOWN;
		}
	}

	bool LogicExToBool(eLogicEx::E var)
	{
		switch (var)
		{
			case eLogicEx::valTRUE:
				return true;
			case eLogicEx::valFALSE:
				return false;
			default:
				return false;
		}
	}
}
// FW20180919 added }
