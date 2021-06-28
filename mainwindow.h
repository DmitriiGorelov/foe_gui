#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

#include "Controller.h"

#include "formpi.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace foeMode
{
    enum T{
        eFromSlave=1,
        eToSlave=2,
    };
}

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
            aSCPReadTemp=6,
            aSCPDelete=7,
        };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool FOE(QString slave, foeMode::T mode, QString fileName, QString password);
    void ReadFromPMAS(QString dest_path, QString remote_file_name, QString local_file_name);

    void fileToMemo(QString path);

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

    private:
    Ui::MainWindow *ui;    

    QProcess proc;

    FormPI pi;

    eActions m_action;
};
#endif // MAINWINDOW_H
