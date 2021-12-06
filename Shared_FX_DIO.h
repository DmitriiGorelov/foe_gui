#pragma once

#include "Shared_FX_BaseTypes.h"

namespace eDIOResult
{
	enum E
	{
		dioUNKNOWN = (LongWord)2,
		dioTRUE    = (LongWord)1,
		dioFALSE   = (LongWord)0,
	};

#define dioTRUE eDIOResult::E::dioTRUE
#define dioFALSE eDIOResult::E::dioFALSE
#define dioUNKNOWN eDIOResult::E::dioUNKNOWN

	class cDIOLogic
	{
	public:
		cDIOLogic(E value)
		: m_value(value)
		{
		}

		~cDIOLogic()
		{

		}

		E operator !()
		{
			switch (value())
			{
				case dioFALSE:
					return dioTRUE;
				case dioTRUE:
					return dioFALSE;
				default:
					return dioUNKNOWN;
			}
		}

		E value()
		{
			return m_value;
		}

	private:
		E m_value;
	};

	eDIOResult::E BoolToDIO(bool var);
	bool DIOToBool(eDIOResult::E var);
}

//inline eDIOResult::E operator&& (eDIOResult::E l, eDIOResult::E r) = delete;
inline bool operator&& (eDIOResult::E l, eDIOResult::E r) = delete; // to avoid errors in using && operator with this type of operands
inline eDIOResult::E operator&& (bool l, eDIOResult::E r) = delete; // to avoid errors in using && operator with this type of operands
inline eDIOResult::E operator&& (eDIOResult::E l, bool r) = delete; // to avoid errors in using && operator with this type of operands


inline eDIOResult::E operator< ( eDIOResult::E l, int r)
{ 
	if (l == dioTRUE && r == dioFALSE) return dioFALSE;
	if (l == dioFALSE && r == dioTRUE) return dioTRUE;

	return dioUNKNOWN;
}

inline eDIOResult::E operator> ( eDIOResult::E l, int r)
{
	if (l == dioTRUE && r == dioFALSE) return dioTRUE;
	if (l == dioFALSE && r == dioTRUE) return dioFALSE;

	return dioUNKNOWN;
}

inline eDIOResult::E operator<= ( eDIOResult::E l, int r)
{
	if (l == dioTRUE && r == dioFALSE) return dioFALSE;
	if (l == dioFALSE && r == dioTRUE) return dioTRUE;
	if (l == dioFALSE && r == dioFALSE) return dioTRUE;
	if (l == dioTRUE && r == dioTRUE) return dioTRUE;

	return dioUNKNOWN;
}

inline eDIOResult::E operator>= ( eDIOResult::E l,  int r)
{
	if (l == dioTRUE && r == dioFALSE) return dioTRUE;
	if (l == dioFALSE && r == dioTRUE) return dioFALSE;
	if (l == dioFALSE && r == dioFALSE) return dioTRUE;
	if (l == dioTRUE && r == dioTRUE) return dioTRUE;

	return dioUNKNOWN;
}

/*
inline eDIOResult::E operator< (eDIOResult::E l, eDIOResult::E r)
{
	if (l == dioTRUE && r == dioFALSE) return dioFALSE;
	if (l == dioFALSE && r == dioTRUE) return dioTRUE;

	return dioUNKNOWN;
}

inline eDIOResult::E operator> (eDIOResult::E l, eDIOResult::E r)
{
	if (l == dioTRUE && r == dioFALSE) return dioTRUE;
	if (l == dioFALSE && r == dioTRUE) return dioFALSE;

	return dioUNKNOWN;
}

inline eDIOResult::E operator<= (eDIOResult::E l, eDIOResult::E r)
{
	if (l == dioTRUE && r == dioFALSE) return dioFALSE;
	if (l == dioFALSE && r == dioTRUE) return dioTRUE;
	if (l == dioFALSE && r == dioFALSE) return dioTRUE;
	if (l == dioTRUE && r == dioTRUE) return dioTRUE;

	return dioUNKNOWN;
}

inline eDIOResult::E operator>= (eDIOResult::E l, eDIOResult::E r)
{
	if (l == dioTRUE && r == dioFALSE) return dioTRUE;
	if (l == dioFALSE && r == dioTRUE) return dioFALSE;
	if (l == dioFALSE && r == dioFALSE) return dioTRUE;
	if (l == dioTRUE && r == dioTRUE) return dioTRUE;

	return dioUNKNOWN;
}
*/

// This opeartor is not allowed. 
/*inline eDIOResult::E operator== (const eDIOResult::E l, const eDIOResult::E r)
{
	if (l == dioTRUE && r == dioFALSE) return dioFALSE;
	if (l == dioFALSE && r == dioTRUE) return dioFALSE;
	if (l == dioFALSE && r == dioFALSE) return dioTRUE;
	if (l == dioTRUE && r == dioTRUE) return dioTRUE;

	return dioUNKNOWN;
}*/

/* These operators can give unexpected results if used in a wrong way
inline eDIOResult::E operator|| (const eDIOResult::E l, const eDIOResult::E r)
{
	if (l == dioTRUE && r == dioFALSE) return dioTRUE;
	if (l == dioFALSE && r == dioTRUE) return dioTRUE;
	if (l == dioFALSE && r == dioFALSE) return dioFALSE;
	if (l == dioTRUE && r == dioTRUE) return dioTRUE;

	return dioUNKNOWN;
}

inline eDIOResult::E operator&& (const eDIOResult::E l, const eDIOResult::E r)
{
	if (l == dioTRUE && r == dioFALSE) return dioFALSE;
	if (l == dioFALSE && r == dioTRUE) return dioFALSE;
	if (l == dioFALSE && r == dioFALSE) return dioFALSE;
	if (l == dioTRUE && r == dioTRUE) return dioTRUE;

	return dioUNKNOWN;
}*/

inline eDIOResult::E operator! (const eDIOResult::E l)
{
	if (l == dioTRUE) return dioFALSE;
	if (l == dioFALSE) return dioTRUE;

	return dioUNKNOWN;
}

// FW20180919 added {
namespace eLogicEx
{
	enum E
	{
		valERROR   = (LongWord)3,
		valUNKNOWN = (LongWord)2,
		valTRUE    = (LongWord)1,
		valFALSE   = (LongWord)0,
	};

	class cLogicExLogic
	{
	public:
		cLogicExLogic(E value)
			: m_value(value)
		{
		}

		cLogicExLogic(eDIOResult::E dioResult)
		{
			switch (dioResult)
			{
				case dioUNKNOWN:
				{
					m_value = valUNKNOWN;
					break;
				}
				case dioTRUE:
				{
					m_value = valTRUE;
					break;
				}
				case dioFALSE:
				{
					m_value = valFALSE;
					break;
				}
				default:
				{
					m_value = valERROR;
					break;
				}
			}
		}

		~cLogicExLogic()
		{

		}

		E operator !()
		{
			switch (value())
			{
				case E::valFALSE:
					return E::valTRUE;
				case E::valTRUE:
					return E::valFALSE;
				case E::valERROR:
					return E::valERROR;
				default:
					return E::valUNKNOWN;
			}
		}

		E value()
		{
			return m_value;
		}

	private:
		E m_value;
	};

	eLogicEx::E BoolToLogicEx(bool var);
	bool LogicExToBool(eLogicEx::E var);
}
// FW20180919 added }

