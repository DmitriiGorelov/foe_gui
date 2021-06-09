#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSettings>
#include <sstream>
#include <iostream>
#include <QFileDialog>
#include <QtWidgets>

#include "CallBack.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pi()
{
    ui->setupUi(this);

    ui->ePassword->setInputMask("HHHHHHHH;");

    QSettings settings;
    settings.beginGroup("FOE Parameters");
    ui->eIPFoE->setText(settings.value("IP PMAS","192.168.35.10").toString());
    ui->eIPHost->setText(settings.value("IP HOST","192.168.35.5").toString());
    ui->eFileName->setText(settings.value("File name","hello.txt").toString());
    ui->ePassword->setText(settings.value("Password","20000000").toString());
    settings.endGroup();


    settings.beginGroup("SCP Parameters");
    ui->eIPSCP->setText(settings.value("IP PMAS","192.168.35.10").toString());
    ui->eSSHUserName->setText(settings.value("SSH User Name", "user").toString());
    ui->eSSHpassword->setText(settings.value("SSH Password","user").toString());
    ui->eTargetFolder->setText(settings.value("Target folder","/mnt/jffs/usr/").toString());
    ui->eSourceFile->setText(settings.value("Source path","c:/hello.txt").toString());
    settings.endGroup();

    ui->eSSHpassword->setEchoMode(QLineEdit::Password);


    connect(&proc, &QProcess::started, this, &MainWindow::sscStarted);
    connect(&proc, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(sscFinished(int,QProcess::ExitStatus)));
    connect(&proc, &QProcess::readyReadStandardError, this, &MainWindow::sscReadyReadStandardError);
    connect(&proc, &QProcess::readyReadStandardOutput, this, &MainWindow::sscReadyReadStandardOutput);
    connect(&proc, &QProcess::errorOccurred, this, &MainWindow::sscErrorOccurred);

    connect(pmas(), &Controller::onConnect, this, &MainWindow::onConnect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::FOE(foeMode::T mode)
{
    std::string filename(ui->eFileName->text().toStdString());
    bool ok(0);
    int pass=ui->ePassword->text().toUInt(&ok,16);
    qInfo()<<"pass:" << pass;

    int ref=pmas()->GetAxisEthercatIDByName(ui->eName->currentText());
    qInfo() << "axisName=" <<ui->eName->currentText() << ", ID=" << ref;

    MMC_DOWNLOADFOEEX_IN in;
    memset(&in.pcFileName,0,256);
    memcpy(&in.pcFileName, filename.c_str(), filename.length()); // file name to upload/download.
    ui->textEdit->setText(ui->textEdit->toPlainText() + "FileName: " +in.pcFileName);
    in.pwSlaveId[0] = ref; // list of slaves IDs to be executed FoE on.
    in.ucSlavesNum=1; // number of slaves to be executed FoE on.
    in.ucOperation=mode; // 1 = FROM DEVICE , 2 = TO DEVICE
    ui->textEdit->setText(ui->textEdit->toPlainText() + "mode: " + QString::number((int)mode));
    in.ucInitialState = 8; // The Ecat state to move to before the upload/download starts.
    in.ucFinalState = 8; // The Ecat state to move to after the upload/download ends.
    in.ucFileSavedInFlash=1; // 0 = Saved in RAM (/tmp), 1 = Saved in Flash (/mnt/jffs/usr)
    in.ulPassword=pass;
    in.ucDeleteFileAfterDownload=0;
    memset(&in.ucReservedBytes,0,32);
    //memcpy(&(in.ucReservedBytes[0]), filename.c_str(), filename.length()); // file name to upload/download.

    MMC_DOWNLOADFOEEX_OUT out;

    if (int res=pmas()->wrp_MMC_DownloadFoEEx(&in, &out)!=0)
    {
        ui->textEdit->setText(ui->textEdit->toPlainText() + "ERROR UPLOAD #" + QString::number(res) + " " + QString(out.usErrorID-65536));
        MMC_RESET_IN inr;
        MMC_RESET_OUT outr;
        inr.ucExecute=1;
        pmas()->wrp_MMC_ResetAsync(ref,&inr,&outr);
        Sleep(100);
        //return false;
    }

    MMC_GETFOESTATUS_OUT outs;

    while (true)
    {
        if (pmas()->wrp_MMC_GetFoEStatus(&outs)!=0)
        {
            QString report = "FOE STATUS: ERROR " + QString::number(outs.usErrorID);
            qInfo() << report ;
            ui->textEdit->setText(ui->textEdit->toPlainText() + report);
            return false;
        }
        else
        {
            QString report = "FOE STATUS: " + QString::number(outs.sFOEStatus) + " FOE PROGRESS : " +
                                 QString::number(int(outs.ucProgress)) + " FOE STARTED: " + QString::number(int(outs.ucFOEStarted)) +
                                 " FOE SLAVE <" + QString::number(int(outs.pstSlavesErrorID[0].usSlaveID)) + "> ERROR: <" +
                             QString::number(int(outs.pstSlavesErrorID[0].sErrorID))+">";

            qInfo() << report;

            ui->textEdit->setText(ui->textEdit->toPlainText() + report);

            if (int(outs.pstSlavesErrorID[0].sErrorID)!=0 || outs.ucProgress==0)
                break;
        }

        Sleep(100);
        //boost::this_thread::sleep_for(boost::chrono::microseconds(100000));
    }

    return true;
}

void MainWindow::onConnect()
{
    ui->bConnect->setEnabled(false);
    pi.PmasConnect();
    ui->eName->addItems(pmas()->getSlaveNames());
}

void MainWindow::sscFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "Finished: " << exitCode;
}

void MainWindow::sscStarted()
{
    qDebug() << "Proc Started";
}

void MainWindow::sscReadyReadStandardError()
{
    QString StdOut = proc.readAllStandardOutput();  //Reads standard output
    QString StdError = proc.readAllStandardError(); // Reads standard error
    ui->textEdit->setText(ui->textEdit->toPlainText() + "OUT: <" + StdOut + "> ERR: <" + StdError+">");
}

void MainWindow::sscReadyReadStandardOutput()
{
    QString StdOut = proc.readAllStandardOutput();  //Reads standard output
    QString StdError = proc.readAllStandardError(); // Reads standard error
    ui->textEdit->setText(ui->textEdit->toPlainText() + "OUT: <" + StdOut + "> ERR: <" + StdError+">");
}

void MainWindow::sscErrorOccurred(QProcess::ProcessError error)
{
    QString StdOut = proc.readAllStandardOutput();  //Reads standard output
    QString StdError = proc.readAllStandardError(); // Reads standard error
    ui->textEdit->setText(ui->textEdit->toPlainText() + "OUT: <" + StdOut + "> ERR: <" + StdError + "> err: <" + QString::number(error)+">");
}

void MainWindow::stateChanged(QProcess::ProcessState state, MainWindow::QPrivateSignal sig)
{
    QString StdOut = proc.readAllStandardOutput();  //Reads standard output
    QString StdError = proc.readAllStandardError(); // Reads standard error
    ui->textEdit->setText(ui->textEdit->toPlainText() + "OUT: <" + StdOut + "> ERR: <" + StdError+">"+
        " State: <"+QString::number(state)+">");
}

void MainWindow::on_bConnect_clicked()
{
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("IP PMAS",ui->eIPFoE->text());
    settings.setValue("IP HOST",ui->eIPHost->text());
    settings.endGroup();

    pmas()->Connect(ui->eIPHost->text(), ui->eIPFoE->text());
}


void MainWindow::on_bFromSlave_clicked()
{
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name",ui->eFileName->text());
    settings.setValue("Password",ui->ePassword->text());
    settings.endGroup();

    FOE(foeMode::eFromSlave);
}

void MainWindow::on_bToSlave_clicked()
{
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name",ui->eFileName->text());
    settings.setValue("Password",ui->ePassword->text());
    settings.endGroup();

    FOE(foeMode::eToSlave);
}

void MainWindow::on_bOpenFile_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), "/home","Config_Files(*.*)") ;
    ui->eSourceFile->setText(filepath);
    QFileInfo fi(filepath);
    ui->eFileName->setText(fi.fileName());
}

void MainWindow::on_bTextClear_clicked()
{
    ui->textEdit->clear() ;
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked)
        ui->eSSHpassword->setEchoMode(QLineEdit::Normal);
    else
        ui->eSSHpassword->setEchoMode(QLineEdit::Password);
}

void MainWindow::on_bSCPSend_clicked()
{
    QSettings settings;
    settings.beginGroup("SCP Parameters");
    settings.setValue("SSH User Name",ui->eSSHUserName->text());
    settings.setValue("SSH Password",ui->eSSHpassword->text());
    settings.setValue("Target folder",ui->eTargetFolder->text());
    settings.setValue("Source path",ui->eSourceFile->text());
    settings.endGroup();

    QString program = "pscp";
    QStringList arguments;
    QString source_path = ui->eSourceFile->text();
    QString username = ui->eSSHUserName->text();
    QString ip = ui->eIPSCP->text();
    QString dest_path = ui->eTargetFolder->text();
    arguments << "-scp" << "-pw" << "user" << "-P" << "22" <<
        source_path << username+"@"+ip+":"+dest_path;
    proc.start(program , arguments);

    return;
}

void MainWindow::on_bFOELoop_clicked()
{
    for (uint k=0;k<ui->eFOELoopCounter->text().toUInt(); k++)
    {
        on_bFromSlave_clicked();
        on_bToSlave_clicked();
    }
}

void MainWindow::on_actionProcess_Image_triggered()
{
    pi.show();
}

void MainWindow::on_pushButton_clicked()
{
    pmas()->ResetCommDiagnostics();
}

void MainWindow::on_pushButton_2_clicked()
{
    pmas()->ResetCommStatistics();
}
