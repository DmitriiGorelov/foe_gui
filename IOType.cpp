
#include "IOType.h"
#include "IOType_Internals.h"

//namespace global_namespace {

	//template<>
	IOType::IOType(eIOType::E _typ, const tuData& val)
	{
		typ = _typ;
		udata = val;
	}

	IOType::IOType(eIOType::E _typ, const float& val)
	{
		memset(&udata, 0, sizeof(udata));
		typ = _typ;
		switch (typ)
		{
		case IOTypeFloat: udata.fData = val; break;
		case IOTypeDouble: udata.dbData = val;	break;
		case IOTypeInt: udata.iData = static_cast<int>(val);	break;
		case IOTypeSignedShort: udata.sData = static_cast<short>(val);	break;
		case IOTypeULL: udata.ullData = static_cast<unsigned long long>(val);	break;
		case IOTypeLL: udata.llData = static_cast<long long>(val);	break;
		case IOTypeULong: udata.ulData = static_cast<unsigned long>(val);	break;
		case IOTypeLong: udata.lData = static_cast<long>(val);	break;
		case IOTypeUI: udata.uiData = static_cast<unsigned int>(val);	break;
		case IOTypeUShort: udata.usData = static_cast<unsigned short>(val);	break;
		case IOTypeUnsignedChar: udata.ucData = static_cast<unsigned char>(val);	break;
		case IOTypeChar: udata.cData = static_cast<char>(val);	break;
		case IOTypeDIO: udata.iData = static_cast<int>(val);	break;
		default:
            //DEBUG_MESSAGE("eIOType type is not defined in " + QString(__FILE__) + " " + Cast::to_str(__LINE__));
            //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
			typ = IOTypeUnknown;
			break;
		}
	}

	IOType::IOType(eIOType::E _typ, const double& val)
	{
		memset(&udata, 0, sizeof(udata));
		typ = _typ;
		switch (typ)
		{
			case IOTypeFloat: udata.fData = val; break;
			case IOTypeDouble: udata.dbData = val;	break;
			case IOTypeInt: udata.iData = static_cast<int>(val);	break;
			case IOTypeSignedShort: udata.sData = static_cast<short>(val);	break;
			case IOTypeULL: udata.ullData = static_cast<unsigned long long>(val);	break;
			case IOTypeLL: udata.llData = static_cast<long long>(val);	break;
			case IOTypeULong: udata.ulData = static_cast<unsigned long>(val);	break;
			case IOTypeLong: udata.lData = static_cast<long>(val);	break;
			case IOTypeUI: udata.uiData = static_cast<unsigned int>(val);	break;
			case IOTypeUShort: udata.usData = static_cast<unsigned short>(val);	break;
			case IOTypeUnsignedChar: udata.ucData = static_cast<unsigned char>(val);	break;
			case IOTypeChar: udata.cData = static_cast<char>(val);	break;
			case IOTypeDIO: udata.iData = static_cast<int>(val);	break;
			default:
                //DEBUG_MESSAGE("eIOType type is not defined in " + QString(__FILE__) + " " + Cast::to_str(__LINE__));
                //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
				typ = IOTypeUnknown;
				break;
		}
	}

	IOType::IOType(eIOType::E _typ, const unsigned int& val)
	{
		memset(&udata, 0, sizeof(udata));
		typ = _typ;
		switch (typ)
		{
			case IOTypeInt: udata.iData = val;	break;
			case IOTypeFloat: udata.fData = val; break;
			case IOTypeSignedShort: udata.sData = val;	break;
			case IOTypeDouble: udata.dbData = val;	break;
			case IOTypeULL: udata.ullData = val; break;
			case IOTypeLL: udata.llData = val;	break;
			case IOTypeULong: udata.ulData = val; break;
			case IOTypeLong: udata.lData = val;	break;
			case IOTypeUI: udata.uiData = val;	break;
			case IOTypeUShort: udata.usData = val;	break;
			case IOTypeUnsignedChar: udata.ucData = val; break;
			case IOTypeChar: udata.cData = val; break;
			case IOTypeDIO: udata.iData = val;	break;
			default:
                //DEBUG_MESSAGE("eIOType type is not defined in " + QString(__FILE__) + " " + Cast::to_str(__LINE__));
                //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
				typ = IOTypeUnknown;
				break;
		}
	}

	//template<>
    IOType::IOType(eIOType::E _typ, const QString& value)
	{
		memset(&udata, 0, sizeof(udata));
		typ = _typ;
		try
		{
			switch (typ)
			{
                case IOTypeDIO: (udata.iData			= value.toInt()					); break;
                case IOTypeChar: (udata.cData			= value[0].toLatin1()					    ); break;//?
                case IOTypeDouble:(udata.dbData			= value.toDouble()				); break;
                case IOTypeFloat: (udata.fData			= value.toFloat()				); break;
                case IOTypeInt: (udata.iData			= value.toInt()					); break;
                case IOTypeLL: (udata.llData			= value.toLongLong()			); break;
                case IOTypeLong: (udata.lData			= value.toLong()					); break;
                case IOTypeSignedShort: (udata.sData	= value.toShort()				); break;
                case IOTypeUI: (udata.uiData			= value.toUInt()			); break;
                case IOTypeULL: (udata.ullData			= value.toULongLong()	); break;
                case IOTypeULong: (udata.ulData			= value.toULong()		); break;
                case IOTypeUnsignedChar: (udata.ucData	= value[0].toLatin1()		); break;  //?
                case IOTypeUShort: (udata.usData		= value.toUShort()		); break;
				default:
                    //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
					break;
			}
		}
		catch (...)
		{
			typ = IOTypeUnknown;
            //lerr << ("Cast error " + RefFileFunctLine + ", value " + value + ", function " + __FUNCTION__);
		}
	}

	void IOType::operator= (const IOType& val)
	{
		udata = val.udata;
		typ = val.typ;
	}

	//template<>
	bool IOType::operator< (const IOType& lo) 
	{
		if (typ != lo.typ)
		{
			return false;
		}

		switch (typ)
		{
			case IOTypeInt: return udata.iData < lo.udata.iData; break;
			case IOTypeFloat: return udata.fData < lo.udata.fData; break;
			case IOTypeSignedShort: return udata.sData < lo.udata.sData;	break;
			case IOTypeDouble: return udata.dbData < lo.udata.dbData;	break;
			case IOTypeULL: return udata.ullData < lo.udata.ullData;	break;
			case IOTypeLL: return udata.llData < lo.udata.llData;	break;
			case IOTypeULong: return udata.ulData < lo.udata.ulData;	break;
			case IOTypeLong: return udata.lData < lo.udata.lData;	break;
			case IOTypeUI: return udata.uiData < lo.udata.uiData;	break;
			case IOTypeUShort: return udata.usData < lo.udata.usData;	break;
			case IOTypeUnsignedChar: return udata.ucData < lo.udata.ucData;	break;
			case IOTypeChar: return udata.cData < lo.udata.cData;	break;
			case IOTypeDIO: return udata.iData < lo.udata.iData;	break;
			default:
                //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
				break;
		}

		return false;
	}

	bool IOType::operator<= (const IOType& lo)
	{
		if (typ != lo.typ)
		{
			return false;
		}

		switch (typ)
		{
		case IOTypeInt: return udata.iData <= lo.udata.iData; break;
		case IOTypeFloat: return udata.fData <= lo.udata.fData; break;
		case IOTypeSignedShort: return udata.sData <= lo.udata.sData;	break;
		case IOTypeDouble: return udata.dbData <= lo.udata.dbData;	break;
		case IOTypeULL: return udata.ullData <= lo.udata.ullData;	break;
		case IOTypeLL: return udata.llData <= lo.udata.llData;	break;
		case IOTypeULong: return udata.ulData <= lo.udata.ulData;	break;
		case IOTypeLong: return udata.lData <= lo.udata.lData;	break;
		case IOTypeUI: return udata.uiData <= lo.udata.uiData;	break;
		case IOTypeUShort: return udata.usData <= lo.udata.usData;	break;
		case IOTypeUnsignedChar: return udata.ucData <= lo.udata.ucData;	break;
		case IOTypeChar: return udata.cData <= lo.udata.cData;	break;
		case IOTypeDIO: return udata.iData <= lo.udata.iData;	break;
		default:
            //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
			break;
		}

		return false;
	}

	//template<>
	bool IOType::operator> (const IOType& lo)
	{
		if (typ != lo.typ)
		{
			return false;
		}

		switch (typ)
		{
			case IOTypeInt: return udata.iData > lo.udata.iData; break;
			case IOTypeFloat: return udata.fData > lo.udata.fData; break;
			case IOTypeSignedShort: return udata.sData > lo.udata.sData;	break;
			case IOTypeDouble: return udata.dbData > lo.udata.dbData;	break;
			case IOTypeULL: return udata.ullData > lo.udata.ullData;	break;
			case IOTypeLL: return udata.llData > lo.udata.llData;	break;
			case IOTypeULong: return udata.ulData > lo.udata.ulData;	break;
			case IOTypeLong: return udata.lData > lo.udata.lData;	break;
			case IOTypeUI: return udata.uiData > lo.udata.uiData;	break;
			case IOTypeUShort: return udata.usData > lo.udata.usData;	break;
			case IOTypeUnsignedChar: return udata.ucData > lo.udata.ucData;	break;
			case IOTypeChar: return udata.cData > lo.udata.cData;	break;
			case IOTypeDIO: return udata.iData > lo.udata.iData;	break;
			default:
                //lerr << "eIOType type is not defined in " << RefFileFunctLine;
				break;
		}

		return false;
	}

	bool IOType::operator>= (const IOType& lo)
	{
		if (typ != lo.typ)
		{
			return false;
		}

		switch (typ)
		{
			case IOTypeInt: return udata.iData >= lo.udata.iData; break;
			case IOTypeFloat: return udata.fData >= lo.udata.fData; break;
			case IOTypeSignedShort: return udata.sData >= lo.udata.sData;	break;
			case IOTypeDouble: return udata.dbData >= lo.udata.dbData;	break;
			case IOTypeULL: return udata.ullData >= lo.udata.ullData;	break;
			case IOTypeLL: return udata.llData >= lo.udata.llData;	break;
			case IOTypeULong: return udata.ulData >= lo.udata.ulData;	break;
			case IOTypeLong: return udata.lData >= lo.udata.lData;	break;
			case IOTypeUI: return udata.uiData >= lo.udata.uiData;	break;
			case IOTypeUShort: return udata.usData >= lo.udata.usData;	break;
			case IOTypeUnsignedChar: return udata.ucData >= lo.udata.ucData;	break;
			case IOTypeChar: return udata.cData >= lo.udata.cData;	break;
			case IOTypeDIO: return udata.iData >= lo.udata.iData;	break;
			default:
                //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
				break;
		}

		return false;
	}

	bool IOType::operator== (const char* lo)
	{
        return operator==(QString(lo));
	}
	
    bool IOType::operator== (const QString& lo)
	{
		try
		{
			switch (typ)
			{
                case IOTypeDIO: return (udata.iData == lo.toInt()); break;
                case IOTypeChar: return (udata.cData == lo[0]); break;//?
                case IOTypeDouble: return (udata.dbData == lo.toDouble()); break;
                case IOTypeFloat: return (udata.fData == lo.toFloat()); break;
                case IOTypeInt: return (udata.iData == lo.toInt()); break;
                case IOTypeLL: return (udata.llData == lo.toLongLong()); break;
                case IOTypeLong: return (udata.lData == lo.toLong()); break;
                case IOTypeSignedShort: return (udata.sData == lo.toShort()); break;
                case IOTypeUI: return (udata.uiData == lo.toUInt()); break;
                case IOTypeULL: return (udata.ullData == lo.toULongLong()); break;
                case IOTypeULong: return (udata.ulData == lo.toULong()); break;
                case IOTypeUnsignedChar: return (udata.ucData == lo[0]); break;  //?
                case IOTypeUShort: return (udata.usData == lo.toUShort()); break;
				default:
                    //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
					break;
			}
		}
		catch (...)
		{
            //lerr << ("Cast error " + RefFileFunctLine + ", value " + lo + ", " + RefFileFunctLine);
		}
		return false;
	}

	//template<>
	bool IOType::operator== (const IOType& lo)
	{		
		return !(*this != lo);
	}

	//template<>
	bool IOType::operator!= (const IOType& lo)
	{
		if (typ != lo.typ)
		{
            //lerr << ("IOType mismatch in " + RefFileFunctLine);
			return true;
		}

        switch (typ)
        {
            case IOTypeDIO: return (udata.iData != lo.udata.iData); break;
            case IOTypeChar: return (udata.cData != lo.udata.cData); break;//?
            case IOTypeDouble: return (udata.dbData != lo.udata.dbData); break;
            case IOTypeFloat: return (udata.fData != lo.udata.fData); break;
            case IOTypeInt: return (udata.iData != lo.udata.iData); break;
            case IOTypeLL: return (udata.llData != lo.udata.llData); break;
            case IOTypeLong: return (udata.lData != lo.udata.lData); break;
            case IOTypeSignedShort: return (udata.sData != lo.udata.sData); break;
            case IOTypeUI: return (udata.uiData != lo.udata.uiData); break;
            case IOTypeULL: return (udata.ullData != lo.udata.ullData); break;
            case IOTypeULong: return (udata.ulData != lo.udata.ulData); break;
            case IOTypeUnsignedChar: return (udata.ucData != lo.udata.ucData); break;  //?
            case IOTypeUShort: return (udata.usData != lo.udata.usData); break;
            default:
                //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
                break;
        }
		return true;
	}		

//} // global_namespace
