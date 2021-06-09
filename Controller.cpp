#include "Controller.h"
#include "CallBack.h"


#include <QDebug>

Controller::Controller()
    : QObject(nullptr)
    , cConn()
    , m_gConnHndl(-1)
    , m_slaveEIndexes()
    , m_slaveNames()
    , m_slaveNamesToEIndexes()
{

}

bool Controller::Connect(QString IPHost, QString IP)
{
    m_gConnHndl = cConn.ConnectRPCEx(const_cast<char*>(IPHost.toStdString().c_str()), const_cast<char*>(IP.toStdString().c_str()),
            0x7fffffff, reinterpret_cast<MMC_MB_CLBK>(CallbackFunc));

    cConn.RegisterEventCallback(MMCPP_EMCY,(void*)Emergency_Received) ;

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
    static bool value = false;
    return value;
}

TSlaveNames Controller::getSlaveNames()
{
    return m_slaveNames;
}

TSlaveNames Controller::getSlaveEIndexes()
{
    return m_slaveEIndexes;
}

int Controller::GetAxisEthercatIDByName(const QString& inParam, int result)
{
    if (!Connected())
    {
        return -1;
    }
    if (!Simulated())
    {
        for (auto it= m_slaveNamesToEIndexes.begin(); it!=m_slaveNamesToEIndexes.end(); it++)
        {
            if (inParam==it.key())
            {
                return it.value();
            }
        }
        return -1;
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

void Controller::slavesListUpdate()
{
    m_slaveNames.clear();

    if (!Connected())
    {
        return ;
    }

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
    for (int i=0; i<nActiveNodes; i++)
    {
        pInParam.uiAxisIndex=i;
        if (0==wrp_GetAxisName(&pInParam, &pOutParam))
        {
            QString name(pOutParam.pAxesName);
            m_slaveEIndexes.append(QString::number(i)); // will not be needful when m_slaveNamesToEIndexes below is correctly saved
            m_slaveNames.append(name);
            m_slaveNamesToEIndexes[QString::number(i)]=i; // i is used termporarily. Must be found a way to save Ethercat Pos instead of Idx/ref
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
