//#pragma warning( disable : 4244 ) 

#include "IOType.h"
//#include "Utils/logMem.h"

#include <QDebug>

//namespace global_namespace {

	template <typename T>
	IOType::IOType(eIOType::E _typ, const T& val)
	{
		memset(&udata, 0, sizeof(udata));
		typ = _typ;
		switch (typ)
		{
			case IOTypeInt: udata.iData           = static_cast<int>(val);	break;
			case IOTypeFloat: udata.fData         = static_cast<float>(val); break;
			case IOTypeSignedShort: udata.sData   = static_cast<short>(val);	break;
			case IOTypeDouble: udata.dbData       = static_cast<double>(val);	break;
			case IOTypeULL: udata.ullData         = static_cast<unsigned long long>(val); break;
			case IOTypeLL: udata.llData           = static_cast<long long>(val);	break;
			case IOTypeULong: udata.ulData        = static_cast<unsigned long>(val); break;
			case IOTypeLong: udata.lData          = static_cast<long>(val);	break;
			case IOTypeUI: udata.uiData           = static_cast<unsigned int>(val);	break;
			case IOTypeUShort: udata.usData       = static_cast<unsigned short>(val);	break;
			case IOTypeUnsignedChar: udata.ucData = static_cast<unsigned char>(val); break;
			case IOTypeChar: udata.cData          = static_cast<char>(val); break;
			case IOTypeDIO: udata.iData           = static_cast<int>(val);	break;
			default:
				//DEBUG_MESSAGE("eIOType type is not defined in " + RefFileFunctLine);
                //qInfo() << ("eIOType type is not defined in " + RefFileFunctLine);
				typ = IOTypeUnknown;
				break;
		}
	}

	template <typename T>
	bool IOType::operator== (const T& lo)
	{
		switch (typ)
		{
			case IOTypeDIO: return (udata.iData == lo); break;
			case IOTypeChar: return (udata.cData == lo); break;//?
			case IOTypeDouble: return (udata.dbData == lo); break;
			case IOTypeFloat: return (udata.fData == lo); break;
			case IOTypeInt: return (udata.iData == lo); break;
			case IOTypeLL: return (udata.llData == lo); break;
			case IOTypeLong: return (udata.lData == lo); break;
			case IOTypeSignedShort: return (udata.sData == lo); break;
			case IOTypeUI: return (udata.uiData == lo); break;
			case IOTypeULL: return (udata.ullData == lo); break;
			case IOTypeULong: return (udata.ulData == lo); break;
			case IOTypeUnsignedChar: return (udata.ucData == lo); break;  //?
			case IOTypeUShort: return (udata.usData == lo); break;
			default:
                //qInfo() << ("eIOType type is not defined in " + RefFileFunctLine) << endl;
				break;
		}
		return false;
	}

	template <typename T>
	bool IOType::operator!= (const T& lo)
	{
		switch (typ)
		{
			case IOTypeDIO: return (udata.iData != lo); break;
			case IOTypeChar: return (udata.cData != lo); break;//?
			case IOTypeDouble: return (udata.dbData != lo); break;
			case IOTypeFloat: return (udata.fData != lo); break;
			case IOTypeInt: return (udata.iData != lo); break;
			case IOTypeLL: return (udata.llData != lo); break;
			case IOTypeLong: return (udata.lData != lo); break;
			case IOTypeSignedShort: return (udata.sData != lo); break;
			case IOTypeUI: return (udata.uiData != lo); break;
			case IOTypeULL: return (udata.ullData != lo); break;
			case IOTypeULong: return (udata.ulData != lo); break;
			case IOTypeUnsignedChar: return (udata.ucData != lo); break;  //?
			case IOTypeUShort: return (udata.usData != lo); break;
			default:
                //qInfo() << ("eIOType type is not defined in " + RefFileFunctLine) << endl;
				break;
		}
		return false;
	}

	template <typename T>
	bool IOType::operator< (const T& val)
	{
		switch (typ)
		{
			case IOTypeDIO:         return (udata.iData   < val); break;
			case IOTypeChar:		 return (udata.cData   < val); break;//?
			case IOTypeDouble:	     return (udata.dbData  < val); break;
			case IOTypeFloat:       return (udata.fData   < val); break;
			case IOTypeInt:         return (udata.iData   < val); break;
			case IOTypeLL:          return (udata.llData  < val); break;
			case IOTypeLong:        return (udata.lData   < val); break;
			case IOTypeSignedShort: return (udata.sData   < val); break;
			case IOTypeUI:          return (udata.uiData  < val); break;
			case IOTypeULL:         return (udata.ullData < val); break;
			case IOTypeULong:       return (udata.ulData  < val); break;
			case IOTypeUnsignedChar:return (udata.ucData  < val); break;  //?
			case IOTypeUShort:      return (udata.usData  < val); break;
			default:
                //qInfo() << ("eIOType type is not defined in " + RefFileFunctLine) << endl;
				break;
		}
		return false;
	}

	template <typename T>
	bool IOType::operator> (const T& val) 
	{
		switch (typ)
		{
		case IOTypeDIO:         return (udata.iData   > val); break;
		case IOTypeChar:		 return (udata.cData   > val); break;//?
		case IOTypeDouble:	     return (udata.dbData  > val); break;
		case IOTypeFloat:       return (udata.fData   > val); break;
		case IOTypeInt:         return (udata.iData   > val); break;
		case IOTypeLL:          return (udata.llData  > val); break;
		case IOTypeLong:        return (udata.lData   > val); break;
		case IOTypeSignedShort: return (udata.sData   > val); break;
		case IOTypeUI:          return (udata.uiData  > val); break;
		case IOTypeULL:         return (udata.ullData > val); break;
		case IOTypeULong:       return (udata.ulData  > val); break;
		case IOTypeUnsignedChar:return (udata.ucData  > val); break;  //?
		case IOTypeUShort:      return (udata.usData  > val); break;
		default:
            //qInfo() << ("eIOType type is not defined in " + RefFileFunctLine) << endl;
			break;
		}
		return false;
	}

	template <typename T>
	bool IOType::operator<= (const T& val)
	{
		switch (typ)
		{
		case IOTypeDIO:         return (udata.iData <= val); break;
		case IOTypeChar:		 return (udata.cData <= val); break;//?
		case IOTypeDouble:	     return (udata.dbData <= val); break;
		case IOTypeFloat:       return (udata.fData <= val); break;
		case IOTypeInt:         return (udata.iData <= val); break;
		case IOTypeLL:          return (udata.llData <= val); break;
		case IOTypeLong:        return (udata.lData <= val); break;
		case IOTypeSignedShort: return (udata.sData <= val); break;
		case IOTypeUI:          return (udata.uiData <= val); break;
		case IOTypeULL:         return (udata.ullData <= val); break;
		case IOTypeULong:       return (udata.ulData <= val); break;
		case IOTypeUnsignedChar:return (udata.ucData <= val); break;  //?
		case IOTypeUShort:      return (udata.usData <= val); break;
		default:
            //qInfo() << ("eIOType type is not defined in " + RefFileFunctLine) << endl;
			break;
		}
		return false;
	}

	template <typename T>
	bool IOType::operator>= (const T& val)
	{
		switch (typ)
		{
			case IOTypeDIO:         return (udata.iData >= val); break;
			case IOTypeChar:		 return (udata.cData >= val); break;//?
			case IOTypeDouble:	     return (udata.dbData >= val); break;
			case IOTypeFloat:       return (udata.fData >= val); break;
			case IOTypeInt:         return (udata.iData >= val); break;
			case IOTypeLL:          return (udata.llData >= val); break;
			case IOTypeLong:        return (udata.lData >= val); break;
			case IOTypeSignedShort: return (udata.sData >= val); break;
			case IOTypeUI:          return (udata.uiData >= val); break;
			case IOTypeULL:         return (udata.ullData >= val); break;
			case IOTypeULong:       return (udata.ulData >= val); break;
			case IOTypeUnsignedChar:return (udata.ucData >= val); break;  //?
			case IOTypeUShort:      return (udata.usData >= val); break;
			default:
                //qInfo() << ("eIOType type is not defined in " + RefFileFunctLine) << endl;
				break;
		}
		return false;
	}	

//}
