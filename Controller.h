#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include <QString>
#include <QMap>


#include "GmasInternals.h"

class Controller;

Controller* pmas();

typedef QList<QString> TSlaveNames;
typedef QMap<QString, int> TSlaves; // key is axis name, value is axis index in ethercat order (NOT axis ref!)

class Controller : public QObject
{
    Q_OBJECT
    friend Controller* pmas();
protected:
    Controller();        
public:

signals:
    void onConnect();

public:

    ~Controller() {}

    bool Connect(QString IPHost, QString IP);
    bool Connected();
    bool Simulated();

    TSlaveNames getSlaveNames();

    MMC_CONNECT_HNDL& getConnHndl() // TODO: make it  private!!! call wrp_ functions to access API, call singleton() to access controller!!!
    {
        return m_gConnHndl;
    }

    int getAxisRef(QString name);
    int GetAxisEthercatIDByName(const QString& inParam, int result = -1); // result is a default value for case of simulated mode.

    int wrp_MMC_GetAxisByNameCmd(
                    IN MMC_AXISBYNAME_IN* pInParam,
                    OUT MMC_AXISBYNAME_OUT* pOutParam,
                    int result = 0) ;
    int wrp_MMC_DownloadFoEEx(
                    IN MMC_DOWNLOADFOEEX_IN* pInParam,
                    OUT MMC_DOWNLOADFOEEX_OUT* pOutParam,
                    int result = 0);
    int wrp_MMC_GetFoEStatus(
                    OUT MMC_GETFOESTATUS_OUT* pOutParam,
                    int result = 0);
    int wrp_MMC_ResetAsync(
                    IN int hAxisRef,
                    IN MMC_RESET_IN* pInParam,
                    OUT MMC_RESET_OUT* pOutParam,
                    int result = 0) ;
    int wrp_MMC_GetGMASOperationMode(
                    OUT MMC_GET_GMASOP_MODE_OUT* pOutParam,
                    int result = 0) ;
    int wrp_MMC_ChangeToOperationMode(
                    OUT MMC_SET_GMAS_OP_OUT* pOutParam,
                    int result = 0) ;

    int wrp_GetAxesName(
                    IN MMC_GETAXESNAME_IN* pInParam,
                    OUT MMC_GETAXESNAME_OUT* pOutParam,
                    int result = 0);
    int wrp_GetAxisName(
                    IN MMC_GETAXISNAME_IN* pInParam,
                    OUT MMC_GETAXISNAME_OUT* pOutParam,
                    int result = 0);
    int wrp_MMC_GetCommStatistics(
                    IN MMC_AXIS_REF_HNDL hAxisRef,
                    OUT MMC_GETCOMMSTATISTICS_OUT* pOutParam,
                    int result = 0) ;
    int wrp_MMC_GetPIVarsRangeInfo(
                    IN MMC_AXIS_REF_HNDL hAxisRef,
                    IN MMC_GETPIVARSRANGEINFO_IN* pInParam,
                    OUT MMC_GETPIVARSRANGEINFO_OUT* pOutParam,
                    int result = 0);
    int wrp_MMC_GetPIVarInfoByAlias(
                    IN MMC_AXIS_REF_HNDL hAxisRef,
                    IN MMC_GETPIVARINFOBYALIAS_IN* pInParam,
                    OUT MMC_GETPIVARINFOBYALIAS_OUT* pOutParam,
                    int result = 0);

    bool ResetCommDiagnostics();
    bool ResetCommStatistics();
    bool ResetSystemErrors();

protected:
    void slavesListUpdate();
    bool checkMode();

private:
    CMMCConnection cConn ;
    MMC_CONNECT_HNDL m_gConnHndl;
    CMMCNetwork network;

    TSlaveNames m_slaveNames;
    TSlaves m_slaves;
};



#endif // CONTROLLER_H
