#include "Controller.h"
#include "CallBack.h"

Controller::Controller()
    : m_gConnHndl(-1)
{

}

bool Controller::Connect(QString IPHost, QString IP)
{
    m_gConnHndl = cConn.ConnectRPCEx(const_cast<char*>(IPHost.toStdString().c_str()), const_cast<char*>(IP.toStdString().c_str()),
            0x7fffffff, reinterpret_cast<MMC_MB_CLBK>(CallbackFunc));

    cConn.RegisterEventCallback(MMCPP_EMCY,(void*)Emergency_Received) ;

    return true;
}

bool Controller::Connected()
{
    return getConnHndl() > 0;
}

bool Controller::Simulated()
{
    static bool value = false;
    return value;
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

int Controller::getAxisRef(QString name)
{
    MMC_AXISBYNAME_IN in;
    MMC_AXISBYNAME_OUT out;

    strcpy_s(in.cAxisName, name.toStdString().c_str());

    if (pmas()->wrp_MMC_GetAxisByNameCmd(&in, &out) != 0)
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
