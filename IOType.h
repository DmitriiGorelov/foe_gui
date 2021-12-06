#pragma once

#include <QString>

#include "Shared_FX_DIO.h"
#include "Shared_FX_BaseTypes.h"
//#include "shared/TCP/Shared_FX_DeviceError.h"

#include "GmasInternals.h"

/*struct tuData
{
	tuData()
	{
		memset(&u, 0, sizeof(u));
	}

	SEND_SDO_DATA_EX u;
};
*/
typedef SEND_SDO_DATA_EX tuData;

//namespace global_namespace {

	using namespace gmas;

	namespace eIOType 
	{
		enum E {
			eIOTypeInt = 0, 
			eIOTypeFloat = 1,
			eIOTypeSignedShort = 2,
			eIOTypeDouble = 3,
			eIOTypeULL = 4,
			eIOTypeLL = 5,
			eIOTypeULong = 6,
			eIOTypeLong = 7,
			eIOTypeUI = 8,
			eIOTypeUShort = 9,
			eIOTypeUnsignedChar = 10,
			eIOTypeChar = 11,

			//!!
			eIOTypeDIO = 12,

			eIOTypeUnknown = 1000,
			//eIOTypeDefault = eIOTypeInt,
		};
	};

#define IOTypeDefault eIOType::eIOTypeInt 
#define IOTypeInt eIOType::eIOTypeInt 
#define IOTypeFloat eIOType::eIOTypeFloat
#define IOTypeSignedShort eIOType::eIOTypeSignedShort
#define IOTypeDouble  eIOType::eIOTypeDouble
#define IOTypeULL eIOType::eIOTypeULL
#define IOTypeLL eIOType::eIOTypeLL
#define IOTypeULong eIOType::eIOTypeULong
#define IOTypeLong eIOType::eIOTypeLong
#define IOTypeUI eIOType::eIOTypeUI
#define IOTypeUShort eIOType::eIOTypeUShort
#define IOTypeUnsignedChar eIOType::eIOTypeUnsignedChar
#define IOTypeChar eIOType::eIOTypeChar
#define IOTypeDIO eIOType::eIOTypeDIO
#define IOTypeUnknown eIOType::eIOTypeUnknown

	class IOType
	{
		// No Default constructor, because we need a specific eIOType
		//IOType() = delete;

		//void operator=(IOType&) = delete;
		//IOType(const IOType&) = delete;
		//IOType(const IOType&&) = delete;
	public:	

		/*static IOType Create()
		{
			return IOType();
		}*/

		/*static IOType Create(eDIOResult::E value)
		{
			return IOType(value);
		}*/

		/*static IOType Create(int value)
		{
			return IOType(value);
		}

		static IOType Create(double value)
		{
			return IOType(value);
		}

		static IOType Create(float value)
		{
			return IOType(value);
		}
		*/
	public:

		IOType()
			: udata()
			, typ(IOTypeUnknown)
		{
			memset(&udata, 0, sizeof(udata));
		}

		IOType(const IOType& h)
			: udata(h.data())
			, typ(h.type())
		{
		
		}				
		
		IOType(eDIOResult::E val) 
		{
			memset(&udata, 0, sizeof(udata));
			typ = IOTypeDIO;
			udata.iData = val;
		}

		IOType(eIOType::E _typ, const tuData& value);
        IOType(eIOType::E _typ, const QString& value);
		IOType(eIOType::E _typ, const float& val);
		IOType(eIOType::E _typ, const double& val);
		IOType(eIOType::E _typ, const unsigned int& val);

		template <typename E>
		explicit IOType(eIOType::E _typ, const E& val);

		IOType(eIOType::E _typ)
		{
			memset(&udata, 0, sizeof(udata));
			typ = _typ;
			switch (typ)
			{
				case IOTypeInt: udata.iData = 0;	break;
				case IOTypeFloat: udata.fData = 0; break;
				case IOTypeSignedShort: udata.sData = 0;	break;
				case IOTypeDouble: udata.dbData = 0;	break;
				case IOTypeULL: udata.ullData = 0; break;
				case IOTypeLL: udata.llData = 0;	break;
				case IOTypeULong: udata.ulData = 0; break;
				case IOTypeLong: udata.lData = 0;	break;
				case IOTypeUI: udata.uiData = 0;	break;
				case IOTypeUShort: udata.usData = 0;	break;
				case IOTypeUnsignedChar: udata.ucData = 0; break;
				case IOTypeChar: udata.cData = 0; break;
				case IOTypeDIO: udata.iData = dioUNKNOWN;	break;
				default:
					//lerr << ("eIOType type is not defined in " + RefFileFunctLine); // no need in this constructor
					typ = IOTypeUnknown;
					break;
			}
		}		

		public:

		static tuData dataLong(long value)
		{
			tuData data;
			data.lData = value;
			return data;
		}

		static tuData dataUInt(unsigned int value)
		{
			tuData data;
			data.uiData = value;
			return data;
		}

		static tuData dataInt(int value)
		{
			tuData data;
			data.uiData = value;
			return data;
		}

		static tuData dataFloat(float value)
		{
			tuData data;
			data.fData = value;
			return data;
		}

		static tuData dataDIO(eDIOResult::E value)
		{
			tuData data;
			data.iData = value;
			return data;
		}
		//

		static IOType Long(long value)
		{
			tuData data;
			data.lData = value;
			return IOType(IOTypeLong, data);
		}

		static IOType Int(int value)
		{
			tuData data;
			data.uiData = value;
			return IOType(IOTypeInt, data);
		}

		static IOType UInt(unsigned int value)
		{
			tuData data;
			data.uiData = value;
			return IOType(IOTypeUI, data);
		}

		static IOType Float(float value)
		{
			tuData data;
			data.fData = value;
			return IOType(IOTypeFloat, data);
		}

		static IOType Double(double value)
		{
			tuData data;
			data.dbData = value;
			return IOType(IOTypeDouble, data);
		}

		static IOType DIO(eDIOResult::E value)
		{
			tuData data;
			data.iData = value;
			return IOType(IOTypeDIO, data);
		}

		bool check()
		{			
			if (typ == IOTypeUnknown)
				return false;

			return true;

			// this check does not work for doubles and floats.
			//return memcmp(IOType(typ, toStr()).udata.pData, udata.pData, sizeof(udata)) == 0;
		}

		eIOType::E type() const
		{
			return typ;
		}

		static unsigned int dataLen(eIOType::E typ) 
		{
			switch (typ)
			{
				case IOTypeInt: return 4;	break;
				case IOTypeFloat: return 4; break;
				case IOTypeSignedShort: return 2;	break;
				case IOTypeDouble: return 4;	break;
				case IOTypeULL: return 8; break;
				case IOTypeLL: return 8;	break;
				case IOTypeULong: return 4; break;
				case IOTypeLong: return 4;	break;
				case IOTypeUI: return 4;	break;
				case IOTypeUShort: return 2;	break;
				case IOTypeUnsignedChar: return 1; break;
				case IOTypeChar: return 1; break;
				case IOTypeDIO: return 4;	break;
				default:
                    //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
					break;
			}
			return 4;
		}

		unsigned int dataLen() const
		{
			switch (typ)
			{
				case IOTypeInt: return 4;	break;
				case IOTypeFloat: return 4; break;
				case IOTypeSignedShort: return 2;	break;
				case IOTypeDouble: return 4;	break;
				case IOTypeULL: return 8; break;
				case IOTypeLL: return 8;	break;
				case IOTypeULong: return 4; break;
				case IOTypeLong: return 4;	break;
				case IOTypeUI: return 4;	break;
				case IOTypeUShort: return 2;	break;
				case IOTypeUnsignedChar: return 1; break;
				case IOTypeChar: return 1; break;
				case IOTypeDIO: return 4;	break;
				default:
                    //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
					break;
			}
			return 4;
		}

		template<typename T>
		T factor(T value)
		{
			switch (typ)
			{
				case IOTypeInt: return udata.iData * value; break;
				case IOTypeFloat: return udata.fData * value; break;
				case IOTypeSignedShort: return udata.sData * value;	break;
				case IOTypeDouble: return udata.dbData * value;	break;
				case IOTypeULL: return udata.ullData * value; break;
				case IOTypeLL: return udata.llData * value;	break;
				case IOTypeULong: return udata.ulData * value; break;
				case IOTypeLong: return udata.lData * value;	break;
				case IOTypeUI: return udata.uiData * value;	break;
				case IOTypeUShort: return udata.usData * value;	break;
				case IOTypeUnsignedChar: return udata.ucData * value; break;
				case IOTypeChar: return udata.cData * value; break;
				case IOTypeDIO: return udata.iData * value;	break;
				default:
                    //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
					break;
			}
			return T(0);
		}

		eDIOResult::E toDIO() const
		{
			if (typ == IOTypeDIO)
				return eDIOResult::E(udata.iData);

            //lerr << ("eIOType type mismatch in " + RefFileFunctLine);
			return dioUNKNOWN;
		}

		double toDouble(bool checkType = true) const
		{
			if (checkType && typ != IOTypeDouble)
                //lerr << ("eIOType type mismatch in " + RefFileFunctLine);

			switch (typ)
			{
				case IOTypeInt: return udata.iData; break;
				case IOTypeFloat: return udata.fData; break;
				case IOTypeSignedShort: return udata.sData; break;
				case IOTypeDouble: return udata.dbData; break;
				case IOTypeULL: return static_cast<double>(udata.ullData); break;
				case IOTypeLL: return static_cast<double>(udata.llData); break;
				case IOTypeULong: return udata.ulData; break;
				case IOTypeLong: return udata.lData; break;
				case IOTypeUI: return udata.uiData; break;
				case IOTypeUShort: return udata.usData; break;
				case IOTypeUnsignedChar: return udata.ucData; break;
				case IOTypeChar: return udata.cData; break;
				case IOTypeDIO: return udata.iData; break;
				default:
                    //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
					break;
				}
			return 0.0;
		}

		float toFloat(bool checkType = true) const
		{
			if (checkType && typ != IOTypeFloat)
                //lerr << ("eIOType type mismatch in " + RefFileFunctLine);

			switch (typ)
			{
				case IOTypeInt: return static_cast<float>(udata.iData); break;
				case IOTypeFloat: return static_cast<float>(udata.fData); break;
				case IOTypeSignedShort: return static_cast<float>(udata.sData); break;
				case IOTypeDouble: return static_cast<float>(udata.dbData); break;
				case IOTypeULL: return static_cast<float>(udata.ullData); break;
				case IOTypeLL: return static_cast<float>(udata.llData); break;
				case IOTypeULong: return static_cast<float>(udata.ulData); break;
				case IOTypeLong: return static_cast<float>(udata.lData); break;
				case IOTypeUI: return static_cast<float>(udata.uiData); break;
				case IOTypeUShort: return static_cast<float>(udata.usData); break;
				case IOTypeUnsignedChar: return static_cast<float>(udata.ucData); break;
				case IOTypeChar: return static_cast<float>(udata.cData); break;
				case IOTypeDIO: return static_cast<float>(udata.iData); break;
				default:
                    //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
					break;
			}
			return 0.0;
		}

		int toInt(bool checkType=true) const
		{
			if (checkType && typ != IOTypeInt)
                //lerr << ("eIOType type mismatch in " + RefFileFunctLine);

			switch (typ)
			{
				case IOTypeInt: return udata.iData; break;
				case IOTypeFloat: return static_cast<int>(udata.fData); break;
				case IOTypeSignedShort: return udata.sData; break;
				case IOTypeDouble: return static_cast<int>(udata.dbData); break;
				case IOTypeULL: return static_cast<int>(udata.ullData); break;
				case IOTypeLL: return static_cast<int>(udata.llData); break;
				case IOTypeULong: return udata.ulData; break;
				case IOTypeLong: return udata.lData; break;
				case IOTypeUI: return udata.uiData; break;
				case IOTypeUShort: return udata.usData; break;
				case IOTypeUnsignedChar: return udata.ucData; break;
				case IOTypeChar: return udata.cData; break;
				case IOTypeDIO: return udata.iData; break;
				default:
                    //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
					break;
			}
			return 0;
		}

		unsigned int toUInt(bool checkType = true) const
		{
			if (checkType && typ != IOTypeUI)
                //lerr << ("eIOType type mismatch in " + RefFileFunctLine);

			switch (typ)
			{
				case IOTypeInt: return udata.iData; break;
				case IOTypeFloat: return static_cast<unsigned int>(udata.fData); break;
				case IOTypeSignedShort: return udata.sData; break;
				case IOTypeDouble: return static_cast<unsigned int>(udata.dbData); break;
				case IOTypeULL: return static_cast<unsigned int>(udata.ullData); break;
				case IOTypeLL: return static_cast<unsigned int>(udata.llData); break;
				case IOTypeULong: return udata.ulData; break;
				case IOTypeLong: return udata.lData; break;
				case IOTypeUI: return udata.uiData; break;
				case IOTypeUShort: return udata.usData; break;
				case IOTypeUnsignedChar: return udata.ucData; break;
				case IOTypeChar: return udata.cData; break;
				case IOTypeDIO: return udata.iData; break;
				default:
                    //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
					break;
			}

			return 0;
		}

		unsigned short toUShort(bool checkType = true) const
		{
			if (checkType && typ != IOTypeUShort)
                //lerr << ("eIOType type mismatch in " + RefFileFunctLine);

			switch (typ)
			{
				case IOTypeInt: return udata.iData; break;
				case IOTypeFloat: return static_cast<unsigned int>(udata.fData); break;
				case IOTypeSignedShort: return udata.sData; break;
				case IOTypeDouble: return static_cast<unsigned int>(udata.dbData); break;
				case IOTypeULL: return static_cast<unsigned int>(udata.ullData); break;
				case IOTypeLL: return static_cast<unsigned int>(udata.llData); break;
				case IOTypeULong: return udata.ulData; break;
				case IOTypeLong: return udata.lData; break;
				case IOTypeUI: return udata.uiData; break;
				case IOTypeUShort: return udata.usData; break;
				case IOTypeUnsignedChar: return udata.ucData; break;
				case IOTypeChar: return udata.cData; break;
				case IOTypeDIO: return udata.iData; break;
				default:
                    //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
					break;
			}

			return 0;
		}

		bool Set(const tuData& value)
		{
			/*if (typ != value.type())
			{
				lerr << ("IOType type mismatch in " + RefFileFunctLine);
				return false;
			}*/

			udata = value;

			return true;
		}

        /*static IOType FromStr(const QString& value, eIOType::E typ)
		{
			IOType res;
			res.typ = typ;
			try
			{
				switch (typ)
				{
					case eIOTypeChar: res.udata.cData = Cast::to<char>(value); break;//?
					case eIOTypeDIO: res.udata.iData = Cast::to<int>(value); break;
					case eIOTypeDouble: res.udata.dbData = Cast::to<double>(value); break;
					case eIOTypeFloat: res.udata.fData = Cast::to<float>(value); break;
					case eIOTypeInt: res.udata.iData = Cast::to<int>(value); break;
					case eIOTypeLL: res.udata.llData = Cast::to<long long>(value); break;
					case eIOTypeLong: res.udata.lData = Cast::to<long>(value); break;
					case eIOTypeSignedShort: res.udata.sData = Cast::to<short>(value); break;
					case eIOTypeUI: res.udata.uiData = Cast::to<unsigned int>(value); break;
					case eIOTypeULL: res.udata.ullData = Cast::to<unsigned long long>(value); break;
					case eIOTypeULong: res.udata.ulData = Cast::to<unsigned long>(value); break;
					case eIOTypeUnsignedChar: res.udata.ucData = Cast::to<unsigned char>(value); break;//?
					case eIOTypeUShort: res.udata.usData = Cast::to<unsigned short>(value); break;
					default:
						lerr << ("eIOType type is not defined in " + RefFileFunctLine);
						res.typ = eIOTypeUnknown;
						break;
				}
				
			}
			catch(...)
			{
				res.typ = eIOTypeUnknown;
			}
			return res;
		}*/

        QString toStr() const
		{
            QString res;
			try
			{
				switch (typ)
				{
                    case IOTypeChar: res = QString::number(udata.cData); break;//?
                    case IOTypeDIO: res = QString::number(udata.iData); break;
                    case IOTypeDouble: res = QString::number(udata.dbData); break;
                    case IOTypeFloat: res = QString::number(udata.fData); break;
                    case IOTypeInt: res = QString::number(udata.iData); break;
                    case IOTypeLL: res = QString::number(udata.llData); break;
                    case IOTypeLong: res = QString::number(udata.lData); break;
                    case IOTypeSignedShort: res = QString::number(udata.sData); break;
                    case IOTypeUI: res = QString::number(udata.uiData); break;
                    case IOTypeULL: res = QString::number(udata.ullData); break;
                    case IOTypeULong: res = QString::number(udata.ulData); break;
                    case IOTypeUnsignedChar: res = QString(udata.ucData); break; //?
                    case IOTypeUShort: res = QString::number(udata.usData); break;
					default:
                        //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
						break;
				}
			}
			catch (...)
			{

			}
			return res;
		}

        /*bool InRange(const QString& lo, const QString& hi)
		{
			bool res;
			switch (typ)
			{
			case eIOTypeChar: res = (data.cData >= Cast::to<char>(lo)) && (data.cData <= Cast::to<char>(hi)); //?
			case eIOTypeDIO: res = (data.iData >= Cast::to<int>(lo)) && (data.iData <= Cast::to<int>(hi));
			case eIOTypeDouble: res = (data.dbData >= Cast::to<double>(lo)) && (data.dbData <= Cast::to<double>(hi));
			case eIOTypeFloat: res = (data.fData >= Cast::to<float>(lo)) && (data.fData <= Cast::to<float>(hi));
			case eIOTypeInt: res = (data.iData >= Cast::to<int>(lo)) && (data.iData <= Cast::to<int>(hi));
			case eIOTypeLL: res = (data.llData >= Cast::to<long long>(lo)) && (data.llData <= Cast::to<long long>(hi));
			case eIOTypeLong: res = (data.lData >= Cast::to<long>(lo)) && (data.lData <= Cast::to<long>(hi));
			case eIOTypeSignedShort: res = (data.sData >= Cast::to<short>(lo)) && (data.sData <= Cast::to<short>(hi));
			case eIOTypeUI: res = (data.uiData >= Cast::to<unsigned int>(lo)) && (data.uiData <= Cast::to<unsigned int>(hi));
			case eIOTypeULL: res = (data.ullData >= Cast::to<unsigned long long>(lo)) && (data.ullData <= Cast::to<unsigned long long>(hi));
			case eIOTypeULong: res = (data.ulData >= Cast::to<unsigned long>(lo)) && (data.ulData <= Cast::to<unsigned long>(hi));
			case eIOTypeUnsignedChar: res = (data.ucData >= Cast::to<unsigned char>(lo)) && (data.ucData <= Cast::to<unsigned char>(hi)); //?
			case eIOTypeUShort: res = (data.usData >= Cast::to<unsigned short>(lo)) && (data.usData <= Cast::to<unsigned short>(hi));
			default:
				lerr << ("eIOType type is not defined in " + RefFileFunctLine);
				res = false;
			}
			return res;
		}		*/

        /*eDIOResult::E operator>= (const QString& lo);
        eDIOResult::E operator<= (const QString& lo);
        eDIOResult::E operator> (const QString& lo);
        eDIOResult::E operator< (const QString& lo);
        eDIOResult::E operator== (const QString& lo);*/

		//eDIOResult::E operator== (const eDIOResult::E& lo);
		//bool operator== (const eDIOResult::E& lo);

		bool operator== (const char* lo);
        bool operator== (const QString& lo);
		bool operator== (const IOType& lo);
		template <typename T> bool operator== (const T& lo);

		bool operator!= (const IOType& lo);
		template <typename T> bool operator!= (const T& lo);

		bool operator< (const IOType& lo);
		template <typename T> bool operator< (const T& val);

		bool operator> (const IOType& lo);
		template <typename T> bool operator> (const T& val);

		bool operator<= (const IOType& lo);
		template <typename T> bool operator<= (const T& val);
		
		bool operator>= (const IOType& lo);
		template <typename T> bool operator>= (const T& val);
		
		//void operator= (const tuData& val);
		void operator= (const IOType& val);
		//template <typename T> void operator= (const T& val);

		/*void operator=(const float& value)
		{
			typ = eIOTypeFloat;
			udata.fData = value;
		}*/

		/*void operator=(const IOType& value)
		{
			typ = value.type();
			memcpy(&udata, &value.udata, sizeof(udata));
		}

		void operator=(const tuData& value)
		{
			memcpy(&udata, &value, sizeof(udata));
		}*/

		/*bool operator< (const IOType& lo) const
		{
			if (typ != lo.typ)
			{
				return false;
			}

			switch (typ)
			{
				case eIOTypeInt: return udata.iData < lo.udata.iData; break;
				case eIOTypeFloat: return udata.fData < lo.udata.fData; break;
				case eIOTypeSignedShort: return udata.sData < lo.udata.sData;	break;
				case eIOTypeDouble: return udata.dbData < lo.udata.dbData;	break;
				case eIOTypeULL: return udata.ullData < lo.udata.ullData;	break;
				case eIOTypeLL: return udata.llData < lo.udata.llData;	break;
				case eIOTypeULong: return udata.ulData < lo.udata.ulData;	break;
				case eIOTypeLong: return udata.lData < lo.udata.lData;	break;
				case eIOTypeUI: return udata.uiData < lo.udata.uiData;	break;
				case eIOTypeUShort: return udata.usData < lo.udata.usData;	break;
				case eIOTypeUnsignedChar: return udata.ucData < lo.udata.ucData;	break;
				case eIOTypeChar: return udata.cData < lo.udata.cData;	break;
				case eIOTypeDIO: return udata.iData < lo.udata.iData;	break;
				default:
					lerr << ("eIOType type is not defined in " + RefFileFunctLine);
					break;
			}
		}

		bool operator> (const IOType& lo)
		{
			if (typ != lo.typ)
			{
				return false;
			}

			switch (typ)
			{
				case eIOTypeInt: return udata.iData > lo.udata.iData; break;
				case eIOTypeFloat: return udata.fData > lo.udata.fData; break;
				case eIOTypeSignedShort: return udata.sData > lo.udata.sData;	break;
				case eIOTypeDouble: return udata.dbData > lo.udata.dbData;	break;
				case eIOTypeULL: return udata.ullData > lo.udata.ullData;	break;
				case eIOTypeLL: return udata.llData > lo.udata.llData;	break;
				case eIOTypeULong: return udata.ulData > lo.udata.ulData;	break;
				case eIOTypeLong: return udata.lData > lo.udata.lData;	break;
				case eIOTypeUI: return udata.uiData > lo.udata.uiData;	break;
				case eIOTypeUShort: return udata.usData > lo.udata.usData;	break;
				case eIOTypeUnsignedChar: return udata.ucData > lo.udata.ucData;	break;
				case eIOTypeChar: return udata.cData > lo.udata.cData;	break;
				case eIOTypeDIO: return udata.iData > lo.udata.iData;	break;
				default:
					lerr << ("eIOType type is not defined in " + RefFileFunctLine);
					break;
			}
		}*/

		/*bool operator== (const IOType& lo)
		{
			if (typ != lo.typ)
			{
				lerr << ("IOType mismatch as expected in " + RefFileFunctLine);
				return false;
			}

			return toStr() == lo.toStr();
		}

		bool operator!= (const IOType& lo)
		{
			if (typ != lo.typ)
			{
				lerr << ("IOType mismatch in " + RefFileFunctLine);
				return true;
			}

			return toStr() != lo.toStr();
		}*/

		/*template <typename T>
		operator T();*/

		/*explicit operator eDIOResult::T()
		{
			if (typ != eIOTypeDIO)
			{
				lerr << ("IOType mismatch eDIOResult in " + RefFileFunctLine);
				return dioUNKNOWN;
			}
			return eDIOResult::E(udata.iData);
		}

		explicit operator double()
		{
			if (typ != eIOTypeDouble)
			{
				lerr << ("IOType mismatch in " + RefFileFunctLine);
				return 0.0;
			}
			return udata.dbData;
		}

		explicit operator float()
		{
			if (typ != eIOTypeFloat)
			{
				lerr << ("IOType mismatch in " + RefFileFunctLine);
				return 0.0;
			}
			return udata.fData;
		}*/

		tuData data() const
		{
			return udata;
		}		

	private:
		tuData udata;

	private:
		eIOType::E typ;
	};			

	inline IOType operator+ (const IOType& lhs, const IOType& rhs) 
	{ 
		//throw - TODO!
		if (lhs.type()!=rhs.type()) 
			return IOType(eIOType::eIOTypeInt); 

		switch (lhs.type())
		{
			case IOTypeInt:          return IOType(lhs.type(),lhs.data().iData		+ rhs.data().iData); break;
			case IOTypeFloat:        return IOType(lhs.type(), lhs.data().fData		+ rhs.data().fData); break;
			case IOTypeSignedShort:  return IOType(lhs.type(), lhs.data().sData		+ rhs.data().sData); break;
			case IOTypeDouble:       return IOType(lhs.type(), lhs.data().dbData	+ rhs.data().dbData); break;
			case IOTypeULL:          return IOType(lhs.type(), lhs.data().ullData	+ rhs.data().ullData); break;
			case IOTypeLL:           return IOType(lhs.type(), lhs.data().llData	+ rhs.data().llData); break;
			case IOTypeULong:        return IOType(lhs.type(), lhs.data().ulData	+ rhs.data().ulData); break;
			case IOTypeLong:         return IOType(lhs.type(), lhs.data().lData		+ rhs.data().lData); break;
			case IOTypeUI:           return IOType(lhs.type(), lhs.data().uiData	+ rhs.data().uiData); break;
			case IOTypeUShort:       return IOType(lhs.type(), lhs.data().usData	+ rhs.data().usData); break;
			case IOTypeUnsignedChar: return IOType(lhs.type(), lhs.data().ucData	+ rhs.data().ucData); break;
			case IOTypeChar:         return IOType(lhs.type(), lhs.data().cData		+ rhs.data().cData); break;
			case IOTypeDIO:          return IOType(lhs.type(), lhs.data().iData		+ rhs.data().iData); break;
			default:
                //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
				break;
		}
		return IOType(eIOType::eIOTypeInt);

	}
	inline IOType operator- (const IOType& lhs, const IOType& rhs)
	{
		//throw - TODO!
		if (lhs.type() != rhs.type())
			return IOType(eIOType::eIOTypeInt);

		switch (lhs.type())
		{
		case IOTypeInt:          return IOType(lhs.type(), lhs.data().iData		- rhs.data().iData); break;
		case IOTypeFloat:        return IOType(lhs.type(), lhs.data().fData		- rhs.data().fData); break;
		case IOTypeSignedShort:  return IOType(lhs.type(), lhs.data().sData		- rhs.data().sData); break;
		case IOTypeDouble:       return IOType(lhs.type(), lhs.data().dbData	- rhs.data().dbData); break;
		case IOTypeULL:          return IOType(lhs.type(), lhs.data().ullData	- rhs.data().ullData); break;
		case IOTypeLL:           return IOType(lhs.type(), lhs.data().llData	- rhs.data().llData); break;
		case IOTypeULong:        return IOType(lhs.type(), lhs.data().ulData	- rhs.data().ulData); break;
		case IOTypeLong:         return IOType(lhs.type(), lhs.data().lData		- rhs.data().lData); break;
		case IOTypeUI:           return IOType(lhs.type(), lhs.data().uiData	- rhs.data().uiData); break;
		case IOTypeUShort:       return IOType(lhs.type(), lhs.data().usData	- rhs.data().usData); break;
		case IOTypeUnsignedChar: return IOType(lhs.type(), lhs.data().ucData	- rhs.data().ucData); break;
		case IOTypeChar:         return IOType(lhs.type(), lhs.data().cData		- rhs.data().cData); break;
		case IOTypeDIO:          return IOType(lhs.type(), lhs.data().iData		- rhs.data().iData); break;
		default:
            //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
			break;
		}
		return IOType(eIOType::eIOTypeInt);

	}
	inline IOType operator* (const IOType& lhs, const IOType& rhs)
	{
		//throw - TODO!
		if (lhs.type() != rhs.type())
			return IOType(eIOType::eIOTypeInt);

		switch (lhs.type())
		{
		case IOTypeInt:          return IOType(lhs.type(), lhs.data().iData		* rhs.data().iData); break;
		case IOTypeFloat:        return IOType(lhs.type(), lhs.data().fData		* rhs.data().fData); break;
		case IOTypeSignedShort:  return IOType(lhs.type(), lhs.data().sData		* rhs.data().sData); break;
		case IOTypeDouble:       return IOType(lhs.type(), lhs.data().dbData	* rhs.data().dbData); break;
		case IOTypeULL:          return IOType(lhs.type(), lhs.data().ullData	* rhs.data().ullData); break;
		case IOTypeLL:           return IOType(lhs.type(), lhs.data().llData	* rhs.data().llData); break;
		case IOTypeULong:        return IOType(lhs.type(), lhs.data().ulData	* rhs.data().ulData); break;
		case IOTypeLong:         return IOType(lhs.type(), lhs.data().lData		* rhs.data().lData); break;
		case IOTypeUI:           return IOType(lhs.type(), lhs.data().uiData	* rhs.data().uiData); break;
		case IOTypeUShort:       return IOType(lhs.type(), lhs.data().usData	* rhs.data().usData); break;
		case IOTypeUnsignedChar: return IOType(lhs.type(), lhs.data().ucData	* rhs.data().ucData); break;
		case IOTypeChar:         return IOType(lhs.type(), lhs.data().cData		* rhs.data().cData); break;
		case IOTypeDIO:          return IOType(lhs.type(), lhs.data().iData		* rhs.data().iData); break;
		default:
            //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
			break;
		}
		return IOType(eIOType::eIOTypeInt);

	}
	inline IOType operator/ (const IOType& lhs, const IOType& rhs)
	{
		if (rhs.data().iData == 0)
		{
            //lerr << ("rhs = 0 in " + RefFileFunctLine);
			return IOType(lhs.type());
		}
		//throw - TODO!
		if (lhs.type() != rhs.type())
			return IOType(eIOType::eIOTypeInt);

		switch (lhs.type())
		{
		case IOTypeInt:          if (rhs.data().iData != 0) return IOType(lhs.type(), lhs.data().iData / rhs.data().iData); else IOType(lhs.type()); break;
		case IOTypeFloat:        if (rhs.data().fData != 0.0) return IOType(lhs.type(), lhs.data().fData / rhs.data().fData); else IOType(lhs.type());  break;
		case IOTypeSignedShort:  if (rhs.data().sData != 0) return IOType(lhs.type(), lhs.data().sData / rhs.data().sData); else IOType(lhs.type());  break;
		case IOTypeDouble:       if (rhs.data().dbData != 0.0) return IOType(lhs.type(), lhs.data().dbData / rhs.data().dbData); else IOType(lhs.type());  break;
		case IOTypeULL:          if (rhs.data().ullData != 0) return IOType(lhs.type(), lhs.data().ullData / rhs.data().ullData); else IOType(lhs.type());  break;
		case IOTypeLL:           if (rhs.data().llData != 0) return IOType(lhs.type(), lhs.data().llData / rhs.data().llData); else IOType(lhs.type());  break;
		case IOTypeULong:        if (rhs.data().ulData != 0) return IOType(lhs.type(), lhs.data().ulData / rhs.data().ulData); else IOType(lhs.type());  break;
		case IOTypeLong:         if (rhs.data().lData != 0) return IOType(lhs.type(), lhs.data().lData / rhs.data().lData); else IOType(lhs.type());  break;
		case IOTypeUI:           if (rhs.data().uiData != 0) return IOType(lhs.type(), lhs.data().uiData / rhs.data().uiData); else IOType(lhs.type());  break;
		case IOTypeUShort:       if (rhs.data().usData != 0) return IOType(lhs.type(), lhs.data().usData / rhs.data().usData); else IOType(lhs.type());  break;
		case IOTypeUnsignedChar: if (rhs.data().ucData != 0) return IOType(lhs.type(), lhs.data().ucData / rhs.data().ucData); else IOType(lhs.type());  break;
		case IOTypeChar:         if (rhs.data().cData != 0) return IOType(lhs.type(), lhs.data().cData / rhs.data().cData); else IOType(lhs.type());  break;
		case IOTypeDIO:          if (rhs.data().iData != 0) return IOType(lhs.type(), lhs.data().iData	/ rhs.data().iData); else IOType(lhs.type());  break;
		default:
            //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
			break;
		}
		return IOType(eIOType::eIOTypeInt);
	}

    /*inline IOType operator+ (const IOType& lhs, const QString& value)
	{
		switch (lhs.type())
		{
			case IOTypeInt:          return IOType(lhs.type(), lhs.data().iData		+ Cast::to<int>(value)); break;
			case IOTypeFloat:        return IOType(lhs.type(), lhs.data().fData		+ Cast::to<char>(value)); break;
			case IOTypeSignedShort:  return IOType(lhs.type(), lhs.data().sData		+ Cast::to<double>(value)); break;
			case IOTypeDouble:       return IOType(lhs.type(), lhs.data().dbData	+ Cast::to<float>(value)); break;
			case IOTypeULL:          return IOType(lhs.type(), lhs.data().ullData	+ Cast::to<int>(value)); break;
			case IOTypeLL:           return IOType(lhs.type(), lhs.data().llData	+ Cast::to<long long>(value)); break;
			case IOTypeULong:        return IOType(lhs.type(), lhs.data().ulData	+ Cast::to<long>(value)); break;
			case IOTypeLong:         return IOType(lhs.type(), lhs.data().lData		+ Cast::to<short>(value)); break;
			case IOTypeUI:           return IOType(lhs.type(), lhs.data().uiData	+ Cast::to<unsigned int>(value)); break;
			case IOTypeUShort:       return IOType(lhs.type(), lhs.data().usData	+ Cast::to<unsigned long long>(value)); break;
			case IOTypeUnsignedChar: return IOType(lhs.type(), lhs.data().ucData	+ Cast::to<unsigned long>(value)); break;
			case IOTypeChar:         return IOType(lhs.type(), lhs.data().cData		+ Cast::to<unsigned char>(value)); break;
			case IOTypeDIO:          return IOType(lhs.type(), lhs.data().iData		+ Cast::to<unsigned short>(value)); break;
			default:
				lerr << ("eIOType type is not defined in " + RefFileFunctLine);
				break;
		}
		return IOType(eIOType::eIOTypeInt);

	}
    inline IOType operator- (const IOType& lhs, const QString& value)
	{
		switch (lhs.type())
		{
		case IOTypeInt:          return IOType(lhs.type(), lhs.data().iData - Cast::to<int>(value)); break;
		case IOTypeFloat:        return IOType(lhs.type(), lhs.data().fData - Cast::to<char>(value)); break;
		case IOTypeSignedShort:  return IOType(lhs.type(), lhs.data().sData - Cast::to<double>(value)); break;
		case IOTypeDouble:       return IOType(lhs.type(), lhs.data().dbData - Cast::to<float>(value)); break;
		case IOTypeULL:          return IOType(lhs.type(), lhs.data().ullData - Cast::to<int>(value)); break;
		case IOTypeLL:           return IOType(lhs.type(), lhs.data().llData - Cast::to<long long>(value)); break;
		case IOTypeULong:        return IOType(lhs.type(), lhs.data().ulData - Cast::to<long>(value)); break;
		case IOTypeLong:         return IOType(lhs.type(), lhs.data().lData	- Cast::to<short>(value)); break;
		case IOTypeUI:           return IOType(lhs.type(), lhs.data().uiData - Cast::to<unsigned int>(value)); break;
		case IOTypeUShort:       return IOType(lhs.type(), lhs.data().usData - Cast::to<unsigned long long>(value)); break;
		case IOTypeUnsignedChar: return IOType(lhs.type(), lhs.data().ucData - Cast::to<unsigned long>(value)); break;
		case IOTypeChar:         return IOType(lhs.type(), lhs.data().cData - Cast::to<unsigned char>(value)); break;
		case IOTypeDIO:          return IOType(lhs.type(), lhs.data().iData - Cast::to<unsigned short>(value)); break;
		default:
			lerr << ("eIOType type is not defined in " + RefFileFunctLine);
			break;
		}
		return IOType(eIOType::eIOTypeInt);

	}
    inline IOType operator* (const IOType& lhs, const QString& value)
	{
		switch (lhs.type())
		{
		case IOTypeInt:          return IOType(lhs.type(), lhs.data().iData * Cast::to<int>(value)); break;
		case IOTypeFloat:        return IOType(lhs.type(), lhs.data().fData * Cast::to<char>(value)); break;
		case IOTypeSignedShort:  return IOType(lhs.type(), lhs.data().sData * Cast::to<double>(value)); break;
		case IOTypeDouble:       return IOType(lhs.type(), lhs.data().dbData * Cast::to<float>(value)); break;
		case IOTypeULL:          return IOType(lhs.type(), lhs.data().ullData * Cast::to<int>(value)); break;
		case IOTypeLL:           return IOType(lhs.type(), lhs.data().llData * Cast::to<long long>(value)); break;
		case IOTypeULong:        return IOType(lhs.type(), lhs.data().ulData * Cast::to<long>(value)); break;
		case IOTypeLong:         return IOType(lhs.type(), lhs.data().lData * Cast::to<short>(value)); break;
		case IOTypeUI:           return IOType(lhs.type(), lhs.data().uiData * Cast::to<unsigned int>(value)); break;
		case IOTypeUShort:       return IOType(lhs.type(), lhs.data().usData * Cast::to<unsigned long long>(value)); break;
		case IOTypeUnsignedChar: return IOType(lhs.type(), lhs.data().ucData * Cast::to<unsigned long>(value)); break;
		case IOTypeChar:         return IOType(lhs.type(), lhs.data().cData * Cast::to<unsigned char>(value)); break;
		case IOTypeDIO:          return IOType(lhs.type(), lhs.data().iData * Cast::to<unsigned short>(value)); break;
		default:
			lerr << ("eIOType type is not defined in " + RefFileFunctLine);
			break;
		}
		return IOType(eIOType::eIOTypeInt);

	}
    inline IOType operator/ (const IOType& lhs, const QString& value)
	{
		if (value == "" || Cast::to<float>(value) == 0 || Cast::to<int>(value) == 0)
		{
			lerr << ("rhs = 0 in " + RefFileFunctLine);
			return IOType(lhs.type(),"0");
		}

		switch (lhs.type())
		{
			case IOTypeInt:          return IOType(lhs.type(), lhs.data().iData / Cast::to<int>(value)); break;
			case IOTypeFloat:        return IOType(lhs.type(), lhs.data().fData / Cast::to<char>(value)); break;
			case IOTypeSignedShort:  return IOType(lhs.type(), lhs.data().sData / Cast::to<double>(value)); break;
			case IOTypeDouble:       return IOType(lhs.type(), lhs.data().dbData / Cast::to<float>(value)); break;
			case IOTypeULL:          return IOType(lhs.type(), lhs.data().ullData / Cast::to<int>(value)); break;
			case IOTypeLL:           return IOType(lhs.type(), lhs.data().llData / Cast::to<long long>(value)); break;
			case IOTypeULong:        return IOType(lhs.type(), lhs.data().ulData / Cast::to<long>(value)); break;
			case IOTypeLong:         return IOType(lhs.type(), lhs.data().lData / Cast::to<short>(value)); break;
			case IOTypeUI:           return IOType(lhs.type(), lhs.data().uiData / Cast::to<unsigned int>(value)); break;
			case IOTypeUShort:       return IOType(lhs.type(), lhs.data().usData / Cast::to<unsigned long long>(value)); break;
			case IOTypeUnsignedChar: return IOType(lhs.type(), lhs.data().ucData / Cast::to<unsigned long>(value)); break;
			case IOTypeChar:         return IOType(lhs.type(), lhs.data().cData / Cast::to<unsigned char>(value)); break;
			case IOTypeDIO:          return IOType(lhs.type(), lhs.data().iData / Cast::to<unsigned short>(value)); break;
			default:
				lerr << ("eIOType type is not defined in " + RefFileFunctLine);
				break;
		}
		return IOType(eIOType::eIOTypeInt);

	}*/

//}

