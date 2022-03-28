#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QSharedPointer>
#include <QVector>

#include "MD5.h"

#include "Controller.h"
#include "enums.h"

#include "formpi.h"
#include "formsdo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

bool md5FromFile(const QString& path, tMD5& arr);

class MainWindow : public QMainWindow
{    
    Q_OBJECT

        enum class eActions {
            aUnknown=0,
            aSCPSend=1,
            aSCPRead=2,
            aSCPListRemoteFiles=3,
            aFOESend=4,
            aFOERead=5,
            //aSCPReadTemp=6,
            aSCPDelete=7,
            aSDOSend=8,
            aSDORead=9,
        };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool FOE(QString slave, eFOEDirection::E mode, QString filePath, QString password);
    void SCPFromPMAS(QString dest_path, QString remote_file_name, QString local_file_name);
    void SCPToPMAS(const QString& fpath);

    void SDOSendMD5(const QString& slave, const QString& filePath, const QString& pass);
    bool SDOSendData(QString slave, eSDODirection::E mode, QString filePath, QByteArray Data, QString password);
    bool SDOSendFile(QString slave, eSDODirection::E mode, QString filePath, QString password);
    bool SDOReadFile(QString slave, eSDODirection::E mode, QString filePath, QString password);
    bool SDOReadFileCAv1(QString slave, eSDODirection::E mode, QString filePath, QString password);

    void fileToMemo(QString path);

    void report(QString text);    

private slots:
    void onConnect();

    void sscFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void sscReadyReadStandardError();
    void sscReadyReadStandardOutput();
    void sscStarted();
    void sscErrorOccurred(QProcess::ProcessError error);
    void stateChanged(QProcess::ProcessState state, QPrivateSignal sig);

    void on_bFromSlave_clicked();

    void on_bToSlave_clicked();

    void on_bConnect_clicked();

    void on_bOpenFile_clicked();

    void on_bTextClear_clicked();

    void on_checkBox_clicked(bool checked);

    void on_bSCPSend_clicked();

    void on_bFOELoop_clicked();

    void on_actionProcess_Image_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_bSCPRead_clicked();

    void on_bSaveFile_clicked();

    void on_eListOfRemoteFiles_clicked();

    void on_bSCPDelete_clicked();

    void on_bResetSystem_clicked();

    void on_bFromSlave_2_clicked();

    void on_bToSlave_2_clicked();

    void on_bToSlave_3_clicked();

    void on_bToSlave_4_clicked();

    void on_bToSlave_5_clicked();

    void on_bFromSlave_3_clicked();

    void on_bFromSlave_4_clicked();

    void on_bFromSlave_5_clicked();

    void on_actionSDO_triggered();

    void on_bSDOToSlave_clicked();

    void on_bToOpenFile_clicked();

    void on_bToSCP_clicked();

    void on_bToOpenFile_2_clicked();

    void on_bToOpenFile_3_clicked();

    void on_bToOpenFile_4_clicked();

    void on_bToOpenFile_5_clicked();


    void on_bFromSCP_clicked();


    void on_bFromSCP_2_clicked();

    void on_bFromSCP_3_clicked();

    void on_bFromSCP_4_clicked();

    void on_bFromSCP_5_clicked();

    void on_bSDOToSlave_2_clicked();

    void on_bSDOToSlave_3_clicked();

    void on_bSDOToSlave_4_clicked();

    void on_bSDOToSlave_5_clicked();

    void on_bSDOFromSlave_clicked();

    void on_bSDOFromSlave_2_clicked();

    void on_bSDOFromSlave_3_clicked();

    void on_bSDOFromSlave_4_clicked();

    void on_bSDOFromSlave_5_clicked();

    void on_bSDOToOpenFile_clicked();

    void on_bSDOToOpenFile_2_clicked();

    void on_bSDOToOpenFile_3_clicked();

    void on_bSDOToOpenFile_4_clicked();

    void on_bSDOToOpenFile_5_clicked();

    void on_bTmpFolder_clicked();

    void on_bSDOSendHeaderSave_clicked();

    void on_bSDOSendBodySave_clicked();

    void on_bSDOReadHeaderSave_clicked();

    void on_bSDOReadBodySave_clicked();

    void on_bSDOFromSlaveMD5_clicked();

    void on_bSDOFromSlaveMD5_2_clicked();

    void on_bSDOFromSlaveMD5_3_clicked();

    void on_bSDOFromSlaveMD5_4_clicked();

    void on_bSDOFromSlaveMD5_5_clicked();

private:
    void TakeFOEFromSlave(const QString& slave, const QString& fname, const QString& password);
    void TakeSDOromSlave(const QString& slave, const QString& fname, const QString& password);

private:
    Ui::MainWindow *ui;    

    QProcess proc;

    FormPI pi;
    QVector<QSharedPointer<FormSDO> > sdos;

    eActions m_action;
    QString m_ProcessResultFile;
};
#endif // MAINWINDOW_H
