#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

#include "GmasInternals.h"

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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int getAxisRef(std::string name);

    bool FOE(foeMode::T mode);

private slots:
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

private:
    Ui::MainWindow *ui;

    MMC_CONNECT_HNDL gConnHndl ;
    CMMCConnection cConn ;

    QProcess proc;
};
#endif // MAINWINDOW_H