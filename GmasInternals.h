#pragma once

#include <cstddef>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100 4244 4245)
#include <mmcpplib.h>
#pragma warning(pop)
#else
//#include <OS_PlatformDependSetting.hpp>
#include <MMCPPGlobal.h>
#include <MMCMessage.h>
#include <MMCConnection.h>
#include <MMCNetwork.h>
#include <MMCModbusSwapBuffer.h>
#include <MMCModbusBuffer.h>
#include <MMCAxis.h>
#include <MMCNode.h>
#include <MMCSingleAxis.h>
#include <MMCGroupAxis.h>
#include <MMCHostComm.h>
#include <MMCDS401Axis.h>
#include <MMCDS406Axis.h>
#include <MMCEcatIo.h>
#include <MMCBulkRead.h>
#include <MMCEoE.h>
#include <MMCSocket.h>
#include <MMCUdp.h>
#include <MMCTcp.h>
#include <MMCEoE.h>
#include <MMCErrorCorr.h>
#include <MMCMotionAxis.h>
#include <MMCUserParams.h>
#include <MMCPIVar.h>
#include <MMCPIBulk.h>
#endif
#include <MMC_definitions.h>

#define EOE_LEN 		512
#define DRV_PORT		5001

//int HexToInt(const char* s);

//namespace global_namespace {

		namespace cAxisType {
			enum T {
				axisUNKNOWN = -1,
				axis0 = 0,
				axis1 = 1,
				axis2 = 2,
			};
		};


namespace gmas {

	namespace eMotorPhaseAN
	{
		enum T
		{
			phaseUnknown = -1,
			phaseA = 3,
			phaseB = 4,
			phaseC = 5,
		};
	}

	const int gmasErrMsgOffset = 1000;

	namespace eOOType {
		enum T {
			eOOTypeInt = 0,
			eOOTypeFloat = 1,
			eOOTypeSignedShort = 2,
		};
	};

	// IEEE754, makes transformation per ISO 9899:2011 �6.5.2.3 3 footnote 95
	float FloatFromLong(long value, eOOType::T type=eOOType::eOOTypeFloat);
	long LongFromFloat(float value, eOOType::T type=eOOType::eOOTypeFloat);

	namespace eControllerType {
		enum T
		{
			UNKNOWN_CONTROLLER = -1,
			REAL_CONTROLLER = 0,
			VIRTUAL_CONTROLLER = 1,
		};
	}


	/// \brief Definition of the several homing routines
	// FW20170706 comment: the index of a 'method' in a 'homing-action'
	/// For details see MAN-CAN402IG.pdf, chapter 9.4.
	namespace eInternalHomingMethod_API {
		enum T
		{
			EmptyMethod = -3,
			HomingBlockPositiveDirection = -2,
			HomingBlockNegativeDirection= -1,
			RLSFallingEdgeAndIndex = 1,
			FLSFallingEdgeAndIndex = 2,
			HomePositiveSideFallingEdgeAndIndex = 3,
			HomePositiveSideRisingEdgeAndIndex = 4,
			HomeNegativeSideFallingEdgeAndIndex = 5,
			HomeNegativeSideRisingEdgeAndIndex = 6,
			HomePpulseNegativeSideFallingEdgeAndIndexFLSDetection = 7,
			HomePulseNegativeSideRisingEdgeAndIndexFLSDetection = 8,
			HomePulsePositiveSideRisingEdgeIndexFLSDetection = 9,
			HomePulsePositiveSideFallingEdgeAndIndexFLSDetection = 10,
			HomePulsePositiveSideFallingEdgeAndIndexRLSDetection = 11,
			HomePulsePositiveSideRisingEdgeAndIndexRLSDetection = 12,
			HomePulseNegativeSideRisingEdgeAndIndexRLSDetection = 13,
			HomePulseNegativeSideFallingEdgeAndIndexRLSDetection = 14,
			RLSFallingEdge = 17,
			FLSFallingEdge = 18,
			HomePositiveSideFallingEdge = 19,
			HomePositiveSideRisingEdge = 20,
			HomeNegativeSideFallingEdge = 21,
			HomeNegativeSideRisingEdge = 22,
			HomePulseNegativeSideFallingEdgeFLSDetection = 23,
			HomePulseNegativeSideRisingEdgeFLSDetection = 24,
			HomePulsePositiveSideRisingEdgeFLSDetection = 25,
			HomePulsePositiveSideFallingEdgeFLSDetection = 26,
			HomePulsePositiveSideFallingEdgeRLSDetection = 27,
			HomePulsePositiveSideRisingEdgeRLSDetection = 28,
			HomePulseNegativeSideRisingEdgeRLSDetection = 29,
			HomePulseNegativeSideFallingEdgeRLSDetection = 30,
			HomeOnIndexNegativeMove = 33,
			HomeOnIndexPositiveMove = 34,
			HomeImmediateOnCurrentPosition = 35,
		};
	};

	class cMotorSettings
	{
		/*cMotorSettings(const cMotorSettings&) _delete
		cMotorSettings& operator = (const cMotorSettings&) _delete
		cMotorSettings(cMotorSettings&&) _delete
		cMotorSettings& operator = (cMotorSettings&&) _delete*/

	public:
		cMotorSettings()
			: MotionSpeed(-1.0)
			, Acceleration(-1.0)
			, Deceleration(-1.0)
			, Jerk(-1.0)

			, LastMotorSpeed(0)
		{}

		~cMotorSettings() {}

		double MotionSpeed;
		double Acceleration;
		double Deceleration;
		double Jerk;

		double LastMotorSpeed; // is REAL speed, sent to a controller
	};

	class cIOBoardSettings
	{
		/*cMotorSettings(const cMotorSettings&) _delete
		cMotorSettings& operator = (const cMotorSettings&) _delete
		cMotorSettings(cMotorSettings&&) _delete
		cMotorSettings& operator = (cMotorSettings&&) _delete*/

	public:
		cIOBoardSettings()
			: DeviceID(-1)
		{}

		~cIOBoardSettings() {}

		int DeviceID;
	};

	class cControllerSettings
	{
	public:
		cControllerSettings()
			: DeviceID(-1)
			, IPAddress("")
			, HostIPAddress("")
		{}

		~cControllerSettings() {}

		int DeviceID;
		std::string IPAddress;
		std::string HostIPAddress;
	};

    //==============================================================================
    /// \brief Wrapper so we only need to include gmas headers inside the cpp files.
    struct CMmcConnectHandle
    {
        /*CMmcConnectHandle(const CMmcConnectHandle&) _delete
        CMmcConnectHandle& operator = (const CMmcConnectHandle&) _delete
        CMmcConnectHandle(CMmcConnectHandle&&) _delete
        CMmcConnectHandle& operator = (CMmcConnectHandle&&) _delete*/

        CMmcConnectHandle() : m_hndl(0) {}
        ~CMmcConnectHandle() {}

        MMC_CONNECT_HNDL m_hndl;
    };

	struct CMmcMOTIONPARAMSSINGLE
	{
		CMmcMOTIONPARAMSSINGLE() : m_Param() {}
		~CMmcMOTIONPARAMSSINGLE() {}

		MMC_MOVEABSOLUTEEX_IN m_Param;
		cMotorSettings Param;

	};

	class cGroupAxesSettings {
		/*cGroupAxesSettings(const cGroupAxesSettings&) _delete
		cGroupAxesSettings& operator = (const cGroupAxesSettings&) _delete
		cGroupAxesSettings(cGroupAxesSettings&&) _delete
		cGroupAxesSettings& operator = (cGroupAxesSettings&&) _delete*/

	public:
		cGroupAxesSettings()
			: GroupIdx(-1)
		{}

		///gmas Index of Group of Axes
		int GroupIdx;
	};

	class cMotorRefParams {
		/*cMotorRefParams(const cMotorRefParams&)  _delete
		cMotorRefParams& operator = (const cMotorRefParams&) _delete
		cMotorRefParams(cMotorRefParams&&) _delete
		cMotorRefParams& operator = (cMotorRefParams&&) _delete*/

	public:
		cMotorRefParams()
			: RefAxisCode("")
			, AxisType(cAxisType::axisUNKNOWN)
			, Homing(-1)
		{}
		///gmas Name of Group of Axes 
		std::string RefAxisCode;
		///gmas Index of Group of Axes
		cAxisType::T AxisType;
		/// 
		int Homing;
	};
	}


//}
