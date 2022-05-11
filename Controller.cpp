#include "Controller.h"
#include "CallBack.h"

#include <QString>

#include <QDebug>

Controller::Controller()
    : QObject(nullptr)
    , cConn()
    , m_gConnHndl(0)
    , network()
    , m_slaveNames()
{

}

bool Controller::Connect(QString IPHost, QString IP)
{
    if (Simulated())
    {
        m_gConnHndl=777;
        network.SetConnHndl(m_gConnHndl);

        emit onConnect();

        return true;
    }

    m_gConnHndl = cConn.ConnectRPCEx(const_cast<char*>(IPHost.toStdString().c_str()), const_cast<char*>(IP.toStdString().c_str()),
            0x7fffffff, reinterpret_cast<MMC_MB_CLBK>(CallbackFunc));

    cConn.RegisterEventCallback(MMCPP_EMCY,(void*)Emergency_Received) ;

    network.SetConnHndl(m_gConnHndl);

    qInfo() << "Connected!";

    slavesListUpdate();

    emit onConnect();

    return true;
}

bool Controller::Connected()
{
    if (getConnHndl())
        return true;
    else
        return false;
}

bool Controller::Simulated()
{
    return false;
#if _DEBUG
    static bool value = true;
#else
    static bool value = false;
#endif

    return value;
}

TSlaveNames Controller::getSlaveNames()
{
    return m_slaveNames;
}

int Controller::GetAxisEthercatIDByName(const QString& inParam, int result)
{
    if (!Connected())
    {
        return -1;
    }
    if (!Simulated())
    {
        int ref=getAxisRef(inParam);

        MMC_READBOOLPARAMETER_IN sReadParamIn;   // IN parameter for MMC_ReadBoolParameter
        MMC_READBOOLPARAMETER_OUT sReadParamOut; // OUT parameter for MMC_ReadBoolParameter

        sReadParamIn.eParameterNumber = (MMC_PARAMETER_LIST_ENUM)MMC_DRIVE_ID_PARAM;  // Set parameter to read – DRIVE_ID is the EtherCAT slave position
        sReadParamIn.iParameterArrIndex = 0; //Set 0
        sReadParamIn.ucEnable = 1; //Enable

        // This function read a parameter
        //     sNameOut.usAxisIdx – Axis ID that we read by MMC_GetAxisByNameCmd
        if (0 != MMC_ReadBoolParameter(getConnHndl(), ref, &sReadParamIn, &sReadParamOut))
        {
            qInfo() << "ERROR - MMC_ReadBoolParameter failed" << endl;
            return -1;
        }

        return sReadParamOut.lValue;
    }
    else
    {
        // outParam shall already keep default value, we do not need to change it in simulation mode.
        return result;
    }
}

int Controller::wrp_MMC_GetAxisByNameCmd(MMC_AXISBYNAME_IN *pInParam, MMC_AXISBYNAME_OUT *pOutParam, int result)
{
    if (!Connected())
    {
        pOutParam->usErrorID = -2000;
        return -1;
    }
    if (!Simulated())
    {
        memset(pOutParam, 0, sizeof(*pOutParam));
        return MMC_GetAxisByNameCmd(getConnHndl(), pInParam, pOutParam);
    }
    else
    {
        if (pOutParam->usAxisIdx<0)
            pOutParam->usAxisIdx = 0;// device.DeviceID(); // for Simulated we use UP index as AxisRef
        return result;
    }
}

int Controller::wrp_MMC_DownloadFoEEx(MMC_DOWNLOADFOEEX_IN *pInParam, MMC_DOWNLOADFOEEX_OUT *pOutParam, int result)
{
    if (!Connected())
    {
        pOutParam->usErrorID = -2000;
        return -1;
    }
    if (!Simulated())
    {
        memset(pOutParam, 0, sizeof(*pOutParam));
        return MMC_DownloadFoEEx(getConnHndl(), pInParam, pOutParam);
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return result;
    }
}

int Controller::wrp_MMC_GetFoEStatus(MMC_GETFOESTATUS_OUT *pOutParam, int result)
{
    if (!Connected())
    {
        pOutParam->usErrorID = -2000;
        return -1;
    }
    if (!Simulated())
    {
        memset(pOutParam, 0, sizeof(*pOutParam));
        return MMC_GetFoEStatus(getConnHndl(), pOutParam);
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return result;
    }
}

int Controller::wrp_MMC_ResetAsync(int hAxisRef, MMC_RESET_IN *pInParam, MMC_RESET_OUT *pOutParam, int result)
{
    if (!Connected())
    {
        pOutParam->usErrorID = -2000;
        return -1;
    }
    if (!Simulated())
    {
        memset(pOutParam, 0, sizeof(*pOutParam));
        return MMC_ResetAsync(getConnHndl(), static_cast<MMC_AXIS_REF_HNDL>(hAxisRef), pInParam, pOutParam);
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return result;
    }
}

int Controller::wrp_MMC_GetGMASOperationMode(MMC_GET_GMASOP_MODE_OUT *pOutParam, int result)
{
    if (!Connected())
    {
        pOutParam->usErrorID = -2000;
        return -1;
    }
    if (!Simulated())
    {
        memset(pOutParam, 0, sizeof(*pOutParam));
        return MMC_GetGMASOperationMode(getConnHndl(), pOutParam);
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return result;
    }
}

int Controller::wrp_MMC_ChangeToOperationMode(MMC_SET_GMAS_OP_OUT *pOutParam, int result)
{
    if (!Connected())
    {
        pOutParam->usErrorID = -2000;
        return -1;
    }
    if (!Simulated())
    {
        memset(pOutParam, 0, sizeof(*pOutParam));
        return MMC_ChangeToOperationMode(getConnHndl(), pOutParam);
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return result;
    }
}

int Controller::wrp_GetAxesName(MMC_GETAXESNAME_IN *pInParam, MMC_GETAXESNAME_OUT *pOutParam, int result)
{
    if (!Connected())
    {
        pOutParam->sErrorID = -2000;
        return -1;
    }
    if (!Simulated())
    {
        memset(pOutParam, 0, sizeof(*pOutParam));
        //return GetAxesName(getConnHndl(), pInParam, pOutParam); // not available in lib
        return -1;
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return result;
    }
}

int Controller::wrp_GetAxisName(MMC_GETAXISNAME_IN *pInParam, MMC_GETAXISNAME_OUT *pOutParam, int result)
{
    if (!Connected())
    {
        pOutParam->sErrorID = -2000;
        return -1;
    }
    if (!Simulated())
    {
        memset(pOutParam, 0, sizeof(*pOutParam));
        return GetAxisName(getConnHndl(), pInParam, pOutParam);
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return result;
    }
}

int Controller::wrp_MMC_GetCommStatistics(MMC_AXIS_REF_HNDL hAxisRef, MMC_GETCOMMSTATISTICS_OUT *pOutParam, int result)
{
    if (!Connected())
    {
        pOutParam->usErrorID = -2000;
        return -1;
    }
    if (!Simulated())
    {
        memset(pOutParam, 0, sizeof(*pOutParam));
        return MMC_GetCommStatistics(getConnHndl(), hAxisRef, pOutParam);
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return result;
    }
}

int Controller::wrp_MMC_GetPIVarsRangeInfo(MMC_AXIS_REF_HNDL hAxisRef, MMC_GETPIVARSRANGEINFO_IN *pInParam, MMC_GETPIVARSRANGEINFO_OUT *pOutParam, int result)
{
    if (!Connected())
    {
        pOutParam->usErrorID = -2000;
        return -1;
    }
    if (!Simulated())
    {
        memset(pOutParam, 0, sizeof(*pOutParam));
        return MMC_GetPIVarsRangeInfo(getConnHndl(), hAxisRef, pInParam, pOutParam);
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return result;
    }
}

int Controller::wrp_MMC_GetPIVarInfoByAlias(MMC_AXIS_REF_HNDL hAxisRef, MMC_GETPIVARINFOBYALIAS_IN *pInParam, MMC_GETPIVARINFOBYALIAS_OUT *pOutParam, int result)
{
    if (!Connected())
    {
        pOutParam->usErrorID = -2000;
        return -1;
    }
    if (!Simulated())
    {
        memset(pOutParam, 0, sizeof(*pOutParam));
        return MMC_GetPIVarInfoByAlias(getConnHndl(), hAxisRef, pInParam, pOutParam);
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return result;
    }
}

int Controller::wrp_MMC_SendSdoExCmd(
            IN MMC_AXIS_REF_HNDL hAxisRef,
            IN MMC_SENDSDOEX_IN* pInParam,
            OUT MMC_SENDSDOEX_OUT* pOutParam,
            int result)
{
    if (!Connected())
    {
        pOutParam->usErrorID = -2000;
        return -1;
    }
    if (!Simulated())
    {
        memset(pOutParam, 0, sizeof(*pOutParam));
        int res = MMC_SendSdoExCmd(getConnHndl(), static_cast<MMC_AXIS_REF_HNDL>(hAxisRef), pInParam, pOutParam);
        qInfo() << "IN: gmasref_" << QString::number(hAxisRef) << " Request: ucService " << QString(pInParam->ucService) <<
            ", usIndex " << QString::number(pInParam->usIndex) << ", ucSubIndex " << QString::number(pInParam->ucSubIndex) <<
            ", DataSize" << QString::number(pInParam->ucDataLength) <<
            ", lData " << QString::number(pInParam->uData.lData) <<
            ", Data " << QByteArray(reinterpret_cast<char*>(pInParam->uData.pData),80).toHex();
        qInfo() << "OUT: gmasref_" << QString::number(hAxisRef) << " Reponse: res " << res << ", usErrorID " << QString::number(pOutParam->usErrorID) <<
            ", lData " << QString::number(pOutParam->uData.lData) <<
            ", Data " << QByteArray(reinterpret_cast<char*>(pOutParam->uData.pData),80).toHex();
        return res;
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return result;
    }
}

int Controller::wrp_MMC_SendSdoCAv1Cmd(
            IN MMC_AXIS_REF_HNDL hAxisRef,
            IN MMC_SENDSDOCAv1_IN * pInParam,
            OUT MMC_SENDSDOCAv1_OUT* pOutParam,
            int result)
{
    if (!Connected())
    {
        pOutParam->usErrorID = -2000;
        return -1;
    }
    if (!Simulated())
    {
        memset(pOutParam, 0, sizeof(*pOutParam));
        int res = MMC_SendSdoCAv1Cmd(getConnHndl(), static_cast<MMC_AXIS_REF_HNDL>(hAxisRef), pInParam, pOutParam);
        qInfo() << "IN: gmasref_" << QString::number(hAxisRef) << " Request: ucService " << QString(pInParam->ucService) <<
            ", usIndex " << QString::number(pInParam->usIndex) << ", ucSubIndex " << QString::number(pInParam->ucSubIndex) <<
            ", DataSize" << QString::number(pInParam->ucDataLength);
            //", lData " << QString::number(pInParam->uData.lData) <<
            //", Data " << QByteArray(reinterpret_cast<char*>(pInParam->uData.pData),80).toHex();
        qInfo() << "OUT: gmasref_" << QString::number(hAxisRef) << " Reponse: res " << res << ", usErrorID " << QString::number(pOutParam->usErrorID) <<
            ", usStatus " << QString::number(pOutParam->usStatus) <<
            ", ucDataLength " <<  QString::number(pOutParam->ucDataLength);
        return res;
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return result;
    }
}


bool Controller::SendSDO(const QString& axisName, tuData& data, unsigned short address, unsigned char subAddress, int dataSize, bool reportIfError, eSDODirection::E direction)
{
    if (!pmas()->Connected())
        return false;

    int ref = getAxisRef(axisName);
    if (ref < 0)
        return false;

    MMC_SENDSDOEX_IN sin;
    MMC_SENDSDOEX_OUT sout;
    sin.uData = data;
    sin.ucDataLength = dataSize;
    sin.usIndex = address;
    sin.ucSubIndex = subAddress;
    sin.ucService = direction; // Write

    if (wrp_MMC_SendSdoExCmd(ref, &sin, &sout) != 0)
    {
        if (reportIfError)
            qInfo() << sout.usErrorID;
        return false;
    }

    if (direction==eSDODirection::READ)
    {
        memcpy(data.pData, sout.uData.pData, NODE_ASCII_ARRAY_MAX_LENGTH);
    }

    return true;
}

bool Controller::SendSDO_CAv1(const QString& axisName, SEND_SDO_DATA_CAv1& data, unsigned short address, unsigned char subAddress, int dataSize, bool reportIfError, eSDODirection::E direction)
{
    if (!pmas()->Connected())
        return false;

    int ref = getAxisRef(axisName);
    if (ref < 0)
        return false;

    MMC_SENDSDOCAv1_IN sin;
    MMC_SENDSDOCAv1_OUT sout;
    memset(&sin, 0, sizeof(sin));
    sin.uData = data;
    sin.ucDataLength = dataSize;
    sin.usIndex = address;
    sin.ucSubIndex = subAddress;
    sin.ucService = direction;

    if (wrp_MMC_SendSdoCAv1Cmd(ref, &sin, &sout) != 0)
    {
        if (reportIfError)
            qInfo() << sout.usErrorID;
        return false;
    }

    if (direction == eSDODirection::READ_Array)
    {
        memcpy(data.pData, sout.uData.pData, NODE_CAv1_ARRAY_MAX_LENGTH);
    }

    return true;
}

bool Controller::ResetCommDiagnostics()
{
    if (!Connected())
    {
        return false;
    }
    if (!Simulated())
    {
        MMC_RESETCOMMDIAGNOSTICS_OUT pOutParam;
        memset(&pOutParam, 0, sizeof(pOutParam));
        network.ResetCommDiagnostics(pOutParam);

        qInfo() << pOutParam.usErrorID;
        return 0==pOutParam.usErrorID;
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return true;
    }
}

bool Controller::ResetCommStatistics()
{
    if (!Connected())
    {
        return false;
    }
    if (!Simulated())
    {
        MMC_RESETCOMMSTATISTICS_OUT pOutParam;
        memset(&pOutParam, 0, sizeof(pOutParam));
        network.ResetCommStatistics(pOutParam);

        qInfo() << pOutParam.usErrorID;
        return 0==pOutParam.usErrorID;
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return true;
    }
}

bool Controller::ResetSystemErrors()
{
    if (!Connected())
    {
        return false;
    }
    if (!Simulated())
    {
        MMC_RESETSYSTEM_IN pInParam;
        MMC_RESETSYSTEM_OUT pOutParam;
        memset(&pOutParam, 0, sizeof(pOutParam));
        if (0!=MMC_ResetSystem(getConnHndl(),&pInParam, &pOutParam))
        {
            qInfo() << pOutParam.sErrorID;
            return false;
        }

        qInfo() << pOutParam.sErrorID;
        return 0==pOutParam.sErrorID;
    }
    else
    {
        //pOutParam->ulValue = ; //used as default value
        return true;
    }
}

void Controller::slavesListUpdate()
{
    m_slaveNames.clear();

    if (!Connected())
    {
        return ;
    }

    qInfo() << "Call for GETCOMMSTATISTICS...";

    MMC_AXIS_REF_HNDL hAxisRef = 0;
    MMC_GETCOMMSTATISTICS_OUT CommStatisticsOut;
    if (0!=wrp_MMC_GetCommStatistics(hAxisRef, &CommStatisticsOut))
    {
        qInfo() << "GETCOMMSTATISTICS() returned with internal error";
        return;
    }
    const int nActiveNodes(CommStatisticsOut.usNumOfSlaves);

    MMC_GETAXISNAME_IN pInParam;
    MMC_GETAXISNAME_OUT pOutParam;
    for (int i=0; i<nActiveNodes; i++) // by some reason <= works . Otherwise the last slave is not in the list
    {
        pInParam.uiAxisIndex=i;
        if (0==wrp_GetAxisName(&pInParam, &pOutParam))
        {
            QString name(pOutParam.pAxesName);
            m_slaveNames.append(name);
        }
        else
            break;
    }
}

bool Controller::checkMode()
{
    bool result = true;
    MMC_GET_GMASOP_MODE_OUT Opmode;
    Opmode.ucResult = 0;
    memset(&Opmode, 0, sizeof(Opmode));

    int rc = wrp_MMC_GetGMASOperationMode(&Opmode);
    if (rc < 0)
    {
        qInfo() << "ERROR MMC_GetGMASOperationMode " << Opmode.usErrorID;
        result = false;
    }
    else
    {
        if (Opmode.ucResult != 0) // GMAS is not in operational mode.
        {
            qInfo() << "GMAS was NOT in operational mode...";

            MMC_SET_GMAS_OP_IN Inparam;
            MMC_SET_GMAS_OP_OUT Outparam;
            Inparam.ucDummy = 1;
            rc = wrp_MMC_ChangeToOperationMode(&Outparam);
            if (rc != 0)
            {
                qInfo() << "operational mode set ERROR " << Outparam.usErrorID;
                result = false;
            }
            qInfo() << "GMAS mode changed to OP";
        }
    }
    return result;
}

int Controller::getAxisRef(QString name)
{
    MMC_AXISBYNAME_IN in;
    MMC_AXISBYNAME_OUT out;

    strcpy_s(in.cAxisName, name.toStdString().c_str());

    if (wrp_MMC_GetAxisByNameCmd(&in, &out) != 0)
    {
        return -1;
    }

    return out.usAxisIdx;
}

Controller* pmas()
{
    static Controller* pmas = new Controller();
    return pmas;
}
