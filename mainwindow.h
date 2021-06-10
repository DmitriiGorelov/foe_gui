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
        };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool FOE(foeMode::T mode);

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

    private:
    Ui::MainWindow *ui;    

    QProcess proc;

    FormPI pi;

    eActions m_action;
};
#endif // MAINWINDOW_H
