#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <sstream>
#include <iostream>

#include <QDebug>
#include <QSettings>
#include <QFileDialog>
#include <QtWidgets>

#include "CallBack.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pi()
    , sdos()
    , m_action(eActions::aUnknown)
    , m_ProcessResultFile("")
{
    ui->setupUi(this);

    ui->eSDOAddressHeader->setInputMask("HHHH;");
    ui->eSDOAddressBody->setInputMask("HHHH;");

    ui->ePasswordTo->setInputMask("HHHHHHHH;");
    ui->ePasswordTo_2->setInputMask("HHHHHHHH;");
    ui->ePasswordTo_3->setInputMask("HHHHHHHH;");
    ui->ePasswordTo_4->setInputMask("HHHHHHHH;");
    ui->ePasswordTo_5->setInputMask("HHHHHHHH;");
    ui->ePasswordFrom->setInputMask("HHHHHHHH;");
    ui->ePasswordFrom_2->setInputMask("HHHHHHHH;");
    ui->ePasswordFrom_3->setInputMask("HHHHHHHH;");
    ui->ePasswordFrom_4->setInputMask("HHHHHHHH;");
    ui->ePasswordFrom_5->setInputMask("HHHHHHHH;");

    ui->eSDOPasswordTo->setInputMask("HHHHHHHH;");
    ui->eSDOPasswordTo_2->setInputMask("HHHHHHHH;");
    ui->eSDOPasswordTo_3->setInputMask("HHHHHHHH;");
    ui->eSDOPasswordTo_4->setInputMask("HHHHHHHH;");
    ui->eSDOPasswordTo_5->setInputMask("HHHHHHHH;");
    ui->eSDOPasswordFrom->setInputMask("HHHHHHHH;");
    ui->eSDOPasswordFrom_2->setInputMask("HHHHHHHH;");
    ui->eSDOPasswordFrom_3->setInputMask("HHHHHHHH;");
    ui->eSDOPasswordFrom_4->setInputMask("HHHHHHHH;");
    ui->eSDOPasswordFrom_5->setInputMask("HHHHHHHH;");

    QSettings settings;
    settings.beginGroup("PMAS Parameters");
    ui->eIPFoE->setText(settings.value("IP PMAS","192.168.35.10").toString());
    ui->eIPHost->setText(settings.value("IP HOST","192.168.35.4").toString());
    settings.endGroup();

    settings.beginGroup("FOE Parameters");
    ui->eFileNameTo->setText(settings.value("File name to","hello.txt").toString());
    ui->eFileNameTo_2->setText(settings.value("File name to 2","hello.txt").toString());
    ui->eFileNameTo_3->setText(settings.value("File name to 3","hello.txt").toString());
    ui->eFileNameTo_4->setText(settings.value("File name to 4","hello.txt").toString());
    ui->eFileNameTo_5->setText(settings.value("File name to 5","hello.txt").toString());
    ui->ePasswordTo->setText(settings.value("Password to","20000000").toString());
    ui->ePasswordTo_2->setText(settings.value("Password to 2","20000000").toString());
    ui->ePasswordTo_3->setText(settings.value("Password to 3","20000000").toString());
    ui->ePasswordTo_4->setText(settings.value("Password to 4","20000000").toString());
    ui->ePasswordTo_5->setText(settings.value("Password to 5","20000000").toString());
    ui->eFileNameFrom->setText(settings.value("File name from","hello.txt").toString());
    ui->eFileNameFrom_2->setText(settings.value("File name from 2","hello.txt").toString());
    ui->eFileNameFrom_3->setText(settings.value("File name from 3","hello.txt").toString());
    ui->eFileNameFrom_4->setText(settings.value("File name from 4","hello.txt").toString());
    ui->eFileNameFrom_5->setText(settings.value("File name from 5","hello.txt").toString());
    ui->ePasswordFrom->setText(settings.value("Password from","20000000").toString());
    ui->ePasswordFrom_2->setText(settings.value("Password from 2","20000000").toString());
    ui->ePasswordFrom_3->setText(settings.value("Password from 3","20000000").toString());
    ui->ePasswordFrom_4->setText(settings.value("Password from 4","20000000").toString());
    ui->ePasswordFrom_5->setText(settings.value("Password from 5","20000000").toString());
    settings.endGroup();

    settings.beginGroup("SDO Parameters");
    ui->eSDOFileNameTo->setText(settings.value("File name to","hello.txt").toString());
    ui->eSDOFileNameTo_2->setText(settings.value("File name to 2","hello.txt").toString());
    ui->eSDOFileNameTo_3->setText(settings.value("File name to 3","hello.txt").toString());
    ui->eSDOFileNameTo_4->setText(settings.value("File name to 4","hello.txt").toString());
    ui->eSDOFileNameTo_5->setText(settings.value("File name to 5","hello.txt").toString());
    ui->eSDOPasswordTo->setText(settings.value("Password to","20000000").toString());
    ui->eSDOPasswordTo_2->setText(settings.value("Password to 2","20000000").toString());
    ui->eSDOPasswordTo_3->setText(settings.value("Password to 3","20000000").toString());
    ui->eSDOPasswordTo_4->setText(settings.value("Password to 4","20000000").toString());
    ui->eSDOPasswordTo_5->setText(settings.value("Password to 5","20000000").toString());
    ui->eSDOFileNameFrom->setText(settings.value("File name from","hello.txt").toString());
    ui->eSDOFileNameFrom_2->setText(settings.value("File name from 2","hello.txt").toString());
    ui->eSDOFileNameFrom_3->setText(settings.value("File name from 3","hello.txt").toString());
    ui->eSDOFileNameFrom_4->setText(settings.value("File name from 4","hello.txt").toString());
    ui->eSDOFileNameFrom_5->setText(settings.value("File name from 5","hello.txt").toString());
    ui->eSDOPasswordFrom->setText(settings.value("Password from","20000000").toString());
    ui->eSDOPasswordFrom_2->setText(settings.value("Password from 2","20000000").toString());
    ui->eSDOPasswordFrom_3->setText(settings.value("Password from 3","20000000").toString());
    ui->eSDOPasswordFrom_4->setText(settings.value("Password from 4","20000000").toString());
    ui->eSDOPasswordFrom_5->setText(settings.value("Password from 5","20000000").toString());
    settings.endGroup();

    settings.beginGroup("SDO Parameters");
    ui->eSDOAddressHeader->setText(settings.value("AddressHeader","0").toString());
    ui->eSDOSubAddressHeader->setValue(settings.value("SubAddressHeader","0").toInt());
    ui->eSDOAddressBody->setText(settings.value("AddressBody","0").toString());
    ui->eSDOSubAddressBody->setValue(settings.value("SubAddressBody","0").toInt());
    settings.endGroup();

    settings.beginGroup("SCP Parameters");
    ui->eIPSCP->setText(settings.value("IP PMAS","192.168.35.10").toString());
    ui->eSSHUserName->setText(settings.value("SSH User Name", "user").toString());
    ui->eSSHpassword->setText(settings.value("SSH Password","user").toString());
    ui->eTargetFolder->setText(settings.value("Target folder","/mnt/jffs/usr/").toString());
    ui->eSourceFile->setText(settings.value("Source path","c:/hello.txt").toString());
    ui->eDestDir->setText(settings.value("Dest path", "d:/").toString());
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

bool MainWindow::FOE(QString slave, eFOEDirection::E mode, QString filePath, QString password)
{
    QFileInfo fi(filePath);

    std::string filename(fi.fileName().toStdString());
    bool ok(0);
    int pass=password.toUInt(&ok,16);
    qInfo()<<"pass:" << pass;

    int ref=pmas()->getAxisRef(slave);
    int ePos=pmas()->GetAxisEthercatIDByName(slave);
    qInfo() << "axisName=" <<slave << ", ePos=" << ePos << ", ref=" << ref;

    MMC_DOWNLOADFOEEX_IN in;
    memset(&in.pcFileName,0,256);
    memcpy(&in.pcFileName, filename.c_str(), filename.length()); // file name to upload/download.
    in.pwSlaveId[0] = ePos; // list of slaves IDs to be executed FoE on.
    in.ucSlavesNum=1; // number of slaves to be executed FoE on.
    in.ucOperation=mode; // 1 = FROM DEVICE , 2 = TO DEVICE
    in.ucInitialState = 8; // The Ecat state to move to before the upload/download starts.
    in.ucFinalState = 8; // The Ecat state to move to after the upload/download ends.
    in.ucFileSavedInFlash=1; // 0 = Saved in RAM (/tmp), 1 = Saved in Flash (/mnt/jffs/usr)
    in.ulPassword=pass;
    in.ucDeleteFileAfterDownload=0;
    memset(&in.ucReservedBytes,0,32);

    MMC_DOWNLOADFOEEX_OUT out;

    if (int res=pmas()->wrp_MMC_DownloadFoEEx(&in, &out)!=0)
    {
        ui->textEdit->setText(ui->textEdit->toPlainText() + "ERROR UPLOAD #" + QString::number(res) + " " + QString::number(out.usErrorID-65536));
        MMC_RESET_IN inr;
        MMC_RESET_OUT outr;
        inr.ucExecute=1;
        pmas()->wrp_MMC_ResetAsync(ref,&inr,&outr);
        Sleep(100);
        return false;
    }

    MMC_GETFOESTATUS_OUT outs;

    ui->textEdit->setText(ui->textEdit->toPlainText() +"\r\n");

    while (true)
    {
        if (0!=pmas()->wrp_MMC_GetFoEStatus(&outs))
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

            ui->textEdit->setText(ui->textEdit->toPlainText() + report+"\r\n");

            if (int(outs.pstSlavesErrorID[0].sErrorID)!=0 || outs.ucProgress==0)
            {                
                break;
            }
        }

        Sleep(100);
        //boost::this_thread::sleep_for(boost::chrono::microseconds(100000));
    }

    return true;
}

bool MainWindow::SDO(QString slave, eSDODirection::E mode, QString filePath, QString password)
{
    bool ok(0);
    int pass=password.toUInt(&ok,16);
    qInfo()<<"pass:" << pass;

    unsigned short alias_Header=ui->eSDOAddressHeader->text().toUInt(&ok,16);
    unsigned short subAddressHeader=ui->eSDOSubAddressHeader->value();
    unsigned short alias_Body=ui->eSDOAddressBody->text().toUInt(&ok,16);
    unsigned short subAddressBody=ui->eSDOSubAddressBody->value();

    // used for sending sdo
    int dataSize;

    tuData udata;

    // -------------------------------- send header
    QFileInfo fi(filePath);
    QString fname = fi.fileName();
    if (fname.size()>12)
        return false;

    memcpy(udata.pData, , min(static_cast<size_t>(dataSize-k), blockSize));
    memcpy(udata.pData+4, , min(static_cast<size_t>(dataSize-k), blockSize));
    if(!pmas()->SendSDO(slave, udata, alias_Body, subAddressBody, blockSize, true, eSDODirection::WRITE))
    {
        report("SDO ERROR!");
        return false;
    }

    // -------------------------------- send data
    QFile CurrentFile(filePath);
    if(!CurrentFile.open(QIODevice::ReadOnly))
    {
        report("Wrong file name! " + filePath);
    }
    QByteArray Data = CurrentFile.readAll();
    CurrentFile.close();
    dataSize = Data.size();

    size_t blockSize=NODE_ASCII_ARRAY_MAX_LENGTH;
    for (int k = 0; k<dataSize; k+=blockSize)
    {
        memcpy(udata.pData, Data.data()+k, min(static_cast<size_t>(dataSize-k), blockSize));
        if(!pmas()->SendSDO(slave, udata, alias_Body, subAddressBody, blockSize, true, eSDODirection::WRITE))
        {
            report("SDO ERROR!");
            return false;
        }
        else
        {
            report("SDO #"+QString::number(k)+" OK!");
        }
    }

    return true;
}

void MainWindow::onConnect()
{
    ui->bConnect->setEnabled(false);
    pi.PmasConnected();

    for (auto it: sdos)
        it->PmasConnected();

    ui->eSlaveName->addItems(pmas()->getSlaveNames());
}

void MainWindow::fileToMemo(QString path)
{
    QFile file(path);

    file.open(QFile::ReadOnly | QFile::Text);

    QTextStream ReadFile(&file);
    ui->textEdit->setText(ui->textEdit->toPlainText() +ReadFile.readAll());
}

void MainWindow::report(QString text)
{
    qInfo() << text;
    ui->textEdit->setText(ui->textEdit->toPlainText() + text+"\r\n");
}

void MainWindow::sscFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    switch (m_action)
    {
        case eActions::aSCPRead:
        {
            if (exitCode==0)
            {
                fileToMemo(m_ProcessResultFile);
            }
            break;
        }

        default:
            //ui->textEdit->setText(ui->textEdit->toPlainText()+StdOut);
            break;
    }

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
    ui->textEdit->setText(ui->textEdit->toPlainText()+"\r\n");
    switch (m_action)
    {
        case eActions::aSCPListRemoteFiles:
        {
            ui->eRemoteFile->clear();
            QStringList s=StdOut.split("\r\n");
            for (auto& it : s)
            {
                QStringList items=it.split(" ");
                if (items.size()>0 && items.back().size()>2)
                {
                    ui->eRemoteFile->addItem(items.back());
                    qInfo() << items.back();
                    ui->textEdit->setText(ui->textEdit->toPlainText() + items.back()+"\r\n");
                }
            }
            break;
        }
        default:
            ui->textEdit->setText(ui->textEdit->toPlainText()+StdOut);
            break;
    }
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
    settings.beginGroup("PMAS Parameters");
    settings.setValue("IP PMAS",ui->eIPFoE->text());
    settings.setValue("IP HOST",ui->eIPHost->text());
    settings.endGroup();

    pmas()->Connect(ui->eIPHost->text(), ui->eIPFoE->text());
}

void MainWindow::TakeFOEFromSlave(const QString& slave, const QString& fpath, const QString& password)
{
    QFileInfo fi(fpath);
    QString fname=fi.fileName();
    m_action=eActions::aFOERead;
    if (FOE(slave,eFOEDirection::READ, fname, password))
    {
        SCPFromPMAS("D:/tmp", fname, "SCPTemp.txt");
    }
}

void MainWindow::on_bOpenFile_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), "","Config_Files(*.*)") ;
    if (filepath.isEmpty())
        return;

    ui->eSourceFile->setText(filepath);
    //QFileInfo fi(filepath);
    //ui->eFileNameTo->setText(fi.fileName());
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
    m_action=eActions::aSCPSend;

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
    QString pass = ui->eSSHpassword->text();
    QString ip = ui->eIPSCP->text();
    QString dest_path = ui->eTargetFolder->text();
    arguments << "-scp" << "-pw" << pass << "-P" << "22" <<
        source_path << username+"@"+ip+":"+dest_path;

    ui->textEdit->setText(ui->textEdit->toPlainText()+"\r\n"+program+" "+arguments.join(" "));
    qInfo() << program << " " << arguments.join(" ");

    proc.start(program , arguments);
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

void MainWindow::SCPFromPMAS(QString dest_path, QString remote_file_name, QString local_file_name)
{
    QSettings settings;
    settings.beginGroup("SCP Parameters");
    settings.setValue("SSH User Name",ui->eSSHUserName->text());
    settings.setValue("SSH Password",ui->eSSHpassword->text());
    settings.setValue("Target folder",ui->eTargetFolder->text());
    settings.setValue("Dest path",ui->eDestDir->text());
    settings.endGroup();    

    QString program = "pscp";
    QStringList arguments;
    QString username = ui->eSSHUserName->text();
    QString pass = ui->eSSHpassword->text();
    QString ip = ui->eIPSCP->text();
    QString source_path = ui->eTargetFolder->text();
    m_ProcessResultFile=dest_path +"/"+ local_file_name;

    arguments << "-scp" << "-pw" << pass << "-P" << "22" << username+"@"+ip+":"+source_path+"/"+remote_file_name <<
        m_ProcessResultFile;

    ui->textEdit->setText(ui->textEdit->toPlainText()+"\r\n"+program+" "+arguments.join(" "));
    qInfo() << program << " " << arguments.join(" ");

    m_action=eActions::aSCPRead;
    proc.start(program , arguments);
}

void MainWindow::SCPToPMAS(const QString& fpath)
{
    QString program = "pscp";
    QStringList arguments;
    QString source_path = fpath;
    QString username = ui->eSSHUserName->text();
    QString pass = ui->eSSHpassword->text();
    QString ip = ui->eIPSCP->text();
    QString dest_path = ui->eTargetFolder->text();
    arguments << "-scp" << "-pw" << pass << "-P" << "22" <<
        source_path << username+"@"+ip+":"+dest_path;

    report(program+" "+arguments.join(" "));
    qInfo() << program << " " << arguments.join(" ");

    m_action=eActions::aSCPSend;
    proc.start(program , arguments);
}

void MainWindow::on_bSCPRead_clicked()
{
    SCPFromPMAS(ui->eDestDir->text(), ui->eRemoteFile->currentText(), ui->eRemoteFile->currentText());
}

void MainWindow::on_bSaveFile_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Existing dir to save file")) ;
    ui->eDestDir->setText(path);
    QFileInfo fi(path);
}

void MainWindow::on_eListOfRemoteFiles_clicked()
{
    m_action=eActions::aSCPListRemoteFiles;

    QString program = "pscp";
    QStringList arguments;
    QString username = ui->eSSHUserName->text();
    QString pass = ui->eSSHpassword->text();
    QString ip = ui->eIPSCP->text();
    QString source_path = ui->eTargetFolder->text();
    arguments << "-scp" << "-pw" << pass << "-P" << "22" << "-ls" << username+"@"+ip+":"+source_path;

    ui->textEdit->setText(ui->textEdit->toPlainText()+"\r\n"+program+" "+arguments.join(" "));
    qInfo() << program << " " << arguments.join(" ");

    proc.start(program , arguments);
}

void MainWindow::on_bSCPDelete_clicked()
{
    m_action=eActions::aSCPDelete;

    QSettings settings;
    settings.beginGroup("SCP Parameters");
    settings.setValue("SSH User Name",ui->eSSHUserName->text());
    settings.setValue("SSH Password",ui->eSSHpassword->text());
    settings.setValue("Target folder",ui->eTargetFolder->text());
    settings.setValue("Dest path",ui->eDestDir->text());
    settings.endGroup();

    QString program = "pscp";
    QStringList arguments;
    QString dest_path = ui->eDestDir->text();
    QString remote_file_name = ui->eRemoteFile->currentText();
    QString username = ui->eSSHUserName->text();
    QString pass = ui->eSSHpassword->text();
    QString ip = ui->eIPSCP->text();
    QString source_path = ui->eTargetFolder->text();
    arguments << "-sftp" << "-pw" << pass << "-P" << "22" << username+"@"+ip+"\"rm -rf"+source_path+"/"+remote_file_name+"\"";

    ui->textEdit->setText(ui->textEdit->toPlainText()+"\r\n"+program+" "+arguments.join(" "));
    qInfo() << program << " " << arguments.join(" ");

    proc.start(program , arguments);
}

void MainWindow::on_bResetSystem_clicked()
{
    pmas()->ResetSystemErrors();
}

void MainWindow::on_bToSlave_clicked()
{
    m_action=eActions::aFOESend;
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name to",ui->eFileNameTo->text());
    settings.setValue("Password to",ui->ePasswordTo->text());
    settings.endGroup();

    FOE(ui->eSlaveName->currentText(),eFOEDirection::WRITE, ui->eFileNameTo->text(), ui->ePasswordTo->text());
}

void MainWindow::on_bToSlave_2_clicked()
{
    m_action=eActions::aFOESend;
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name to 2",ui->eFileNameTo_2->text());
    settings.setValue("Password to 2",ui->ePasswordTo_2->text());
    settings.endGroup();

    FOE(ui->eSlaveName->currentText(),eFOEDirection::WRITE, ui->eFileNameTo_2->text(), ui->ePasswordTo_2->text());
}

void MainWindow::on_bToSlave_3_clicked()
{
    m_action=eActions::aFOESend;
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name to 3",ui->eFileNameTo_3->text());
    settings.setValue("Password to 3",ui->ePasswordTo_3->text());
    settings.endGroup();

    FOE(ui->eSlaveName->currentText(),eFOEDirection::WRITE, ui->eFileNameTo_3->text(), ui->ePasswordTo_3->text());
}

void MainWindow::on_bToSlave_4_clicked()
{
    m_action=eActions::aFOESend;
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name to 4",ui->eFileNameTo_4->text());
    settings.setValue("Password to 4",ui->ePasswordTo_4->text());
    settings.endGroup();

    FOE(ui->eSlaveName->currentText(),eFOEDirection::WRITE, ui->eFileNameTo_4->text(), ui->ePasswordTo_4->text());
}

void MainWindow::on_bToSlave_5_clicked()
{
    m_action=eActions::aFOESend;
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name to 5",ui->eFileNameTo_5->text());
    settings.setValue("Password to 5",ui->ePasswordTo_5->text());
    settings.endGroup();

    FOE(ui->eSlaveName->currentText(),eFOEDirection::WRITE, ui->eFileNameTo_5->text(), ui->ePasswordTo_5->text());
}

void MainWindow::on_bFromSlave_clicked()
{
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name from",ui->eFileNameFrom->text());
    settings.setValue("Password from",ui->ePasswordFrom->text());
    settings.endGroup();

    TakeFOEFromSlave(ui->eSlaveName->currentText(), ui->eFileNameFrom->text(), ui->ePasswordFrom->text());
}

void MainWindow::on_bFromSlave_2_clicked()
{
    m_action=eActions::aFOERead;
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name from 2",ui->eFileNameFrom_2->text());
    settings.setValue("Password from 2",ui->ePasswordFrom_2->text());
    settings.endGroup();

    TakeFOEFromSlave(ui->eSlaveName->currentText(), ui->eFileNameFrom_2->text(), ui->ePasswordFrom_2->text());
}

void MainWindow::on_bFromSlave_3_clicked()
{
    m_action=eActions::aFOERead;
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name from 3",ui->eFileNameFrom_3->text());
    settings.setValue("Password from 3",ui->ePasswordFrom_3->text());
    settings.endGroup();

    TakeFOEFromSlave(ui->eSlaveName->currentText(), ui->eFileNameFrom_3->text(), ui->ePasswordFrom_3->text());
}

void MainWindow::on_bFromSlave_4_clicked()
{
    m_action=eActions::aFOERead;
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name from 4",ui->eFileNameFrom_4->text());
    settings.setValue("Password from 4",ui->ePasswordFrom_4->text());
    settings.endGroup();

    TakeFOEFromSlave(ui->eSlaveName->currentText(), ui->eFileNameFrom_4->text(), ui->ePasswordFrom_4->text());
}

void MainWindow::on_bFromSlave_5_clicked()
{
    m_action=eActions::aFOERead;
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name from 5",ui->eFileNameFrom_5->text());
    settings.setValue("Password from 5",ui->ePasswordFrom_5->text());
    settings.endGroup();

    TakeFOEFromSlave(ui->eSlaveName->currentText(), ui->eFileNameFrom_5->text(), ui->ePasswordFrom_5->text());
}

void MainWindow::on_actionSDO_triggered()
{
    sdos.push_back(QSharedPointer<FormSDO>(new FormSDO()));
    sdos[sdos.size()-1]->PmasConnected();
    sdos[sdos.size()-1]->show();
}

void MainWindow::on_bToOpenFile_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), ui->eFileNameTo->text(), "Config_Files(*.*)") ;
    if (filepath.isEmpty())
        return;

    ui->eFileNameTo->setText(filepath);

    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name to",ui->eFileNameTo->text());
    settings.endGroup();
}

void MainWindow::on_bToSCP_clicked()
{
    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name to",ui->eFileNameTo->text());
    settings.setValue("Password to",ui->ePasswordTo->text());
    settings.endGroup();

    SCPToPMAS(ui->eFileNameTo->text());
}


void MainWindow::on_bToOpenFile_2_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), ui->eFileNameTo_2->text(), "Config_Files(*.*)") ;
    if (filepath.isEmpty())
        return;

    ui->eFileNameTo_2->setText(filepath);

    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name to 2",ui->eFileNameTo_2->text());
    settings.endGroup();
}


void MainWindow::on_bToOpenFile_3_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), ui->eFileNameTo_3->text(), "Config_Files(*.*)") ;
    if (filepath.isEmpty())
        return;

    ui->eFileNameTo_3->setText(filepath);

    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name to 3",ui->eFileNameTo_3->text());
    settings.endGroup();
}


void MainWindow::on_bToOpenFile_4_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), ui->eFileNameTo_4->text(), "Config_Files(*.*)") ;
    if (filepath.isEmpty())
        return;

    ui->eFileNameTo_4->setText(filepath);

    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name to 4",ui->eFileNameTo_4->text());
    settings.endGroup();
}


void MainWindow::on_bToOpenFile_5_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), ui->eFileNameTo_5->text(), "Config_Files(*.*)") ;
    if (filepath.isEmpty())
        return;

    ui->eFileNameTo_5->setText(filepath);

    QSettings settings;
    settings.beginGroup("FOE Parameters");
    settings.setValue("File name to 5",ui->eFileNameTo_5->text());
    settings.endGroup();
}

void MainWindow::on_bFromSCP_clicked()
{
    SCPFromPMAS("D:/tmp", ui->eFileNameFrom->text(), "SCPTemp.txt");
}



void MainWindow::on_bFromSCP_2_clicked()
{
    SCPFromPMAS("D:/tmp", ui->eFileNameFrom_2->text(), "SCPTemp.txt");
}


void MainWindow::on_bFromSCP_3_clicked()
{
    SCPFromPMAS("D:/tmp", ui->eFileNameFrom_3->text(), "SCPTemp.txt");
}


void MainWindow::on_bFromSCP_4_clicked()
{
    SCPFromPMAS("D:/tmp", ui->eFileNameFrom_4->text(), "SCPTemp.txt");
}


void MainWindow::on_bFromSCP_5_clicked()
{
    SCPFromPMAS("D:/tmp", ui->eFileNameFrom_5->text(), "SCPTemp.txt");
}

void MainWindow::on_bSDOToSlave_clicked()
{
    m_action=eActions::aSDOSend;
    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name to",ui->eSDOFileNameTo->text());
    settings.setValue("Password to",ui->eSDOPasswordTo->text());
    settings.endGroup();

    SDO(ui->eSlaveName->currentText(),eSDODirection::WRITE, ui->eSDOFileNameTo->text(), ui->eSDOPasswordTo->text());
}

void MainWindow::on_bSDOToSlave_2_clicked()
{
    m_action=eActions::aSDOSend;
    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name to 2",ui->eSDOFileNameTo_2->text());
    settings.setValue("Password to 2",ui->eSDOPasswordTo_2->text());
    settings.endGroup();

    SDO(ui->eSlaveName->currentText(),eSDODirection::WRITE, ui->eSDOFileNameTo_2->text(), ui->eSDOPasswordTo_2->text());
}


void MainWindow::on_bSDOToSlave_3_clicked()
{
    m_action=eActions::aSDOSend;
    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name to 3",ui->eSDOFileNameTo_3->text());
    settings.setValue("Password to 3",ui->eSDOPasswordTo_3->text());
    settings.endGroup();

    SDO(ui->eSlaveName->currentText(),eSDODirection::WRITE, ui->eSDOFileNameTo_3->text(), ui->eSDOPasswordTo_3->text());
}

void MainWindow::on_bSDOToSlave_4_clicked()
{
    m_action=eActions::aSDOSend;
    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name to 4",ui->eSDOFileNameTo_4->text());
    settings.setValue("Password to 4",ui->eSDOPasswordTo_4->text());
    settings.endGroup();

    SDO(ui->eSlaveName->currentText(),eSDODirection::WRITE, ui->eSDOFileNameTo_4->text(), ui->eSDOPasswordTo_4->text());
}


void MainWindow::on_bSDOToSlave_5_clicked()
{
    m_action=eActions::aSDOSend;
    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name to 5",ui->eSDOFileNameTo_5->text());
    settings.setValue("Password to 5",ui->eSDOPasswordTo_5->text());
    settings.endGroup();

    SDO(ui->eSlaveName->currentText(),eSDODirection::WRITE, ui->eSDOFileNameTo_5->text(), ui->eSDOPasswordTo_5->text());
}


void MainWindow::on_bSDOFromSlave_clicked()
{
    m_action=eActions::aSDORead;
    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name from",ui->eSDOFileNameFrom->text());
    settings.setValue("Password from",ui->eSDOPasswordFrom->text());
    settings.endGroup();

    SDO(ui->eSlaveName->currentText(),eSDODirection::READ, ui->eSDOFileNameFrom->text(), ui->eSDOPasswordFrom->text());
}


void MainWindow::on_bSDOFromSlave_2_clicked()
{
    m_action=eActions::aSDORead;
    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name from 2",ui->eSDOFileNameFrom_2->text());
    settings.setValue("Password from 2",ui->eSDOPasswordFrom_2->text());
    settings.endGroup();

    SDO(ui->eSlaveName->currentText(),eSDODirection::READ, ui->eSDOFileNameFrom_2->text(), ui->eSDOPasswordFrom_2->text());
}


void MainWindow::on_bSDOFromSlave_3_clicked()
{
    m_action=eActions::aSDORead;
    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name from 3",ui->eSDOFileNameFrom_3->text());
    settings.setValue("Password from 3",ui->eSDOPasswordFrom_3->text());
    settings.endGroup();

    SDO(ui->eSlaveName->currentText(),eSDODirection::READ, ui->eSDOFileNameFrom_3->text(), ui->eSDOPasswordFrom_3->text());
}


void MainWindow::on_bSDOFromSlave_4_clicked()
{
    m_action=eActions::aSDORead;
    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name from 4",ui->eSDOFileNameFrom_4->text());
    settings.setValue("Password from 4",ui->eSDOPasswordFrom_4->text());
    settings.endGroup();

    SDO(ui->eSlaveName->currentText(),eSDODirection::READ, ui->eSDOFileNameFrom_4->text(), ui->eSDOPasswordFrom_4->text());
}


void MainWindow::on_bSDOFromSlave_5_clicked()
{
    m_action=eActions::aSDORead;
    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name from 5",ui->eSDOFileNameFrom_5->text());
    settings.setValue("Password from 5",ui->eSDOPasswordFrom_5->text());
    settings.endGroup();

    SDO(ui->eSlaveName->currentText(),eSDODirection::READ, ui->eSDOFileNameFrom_5->text(), ui->eSDOPasswordFrom_5->text());
}


void MainWindow::on_bSDOToOpenFile_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), ui->eSDOFileNameTo->text(), "Config_Files(*.*)") ;
    if (filepath.isEmpty())
        return;

    ui->eSDOFileNameTo->setText(filepath);

    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name to",ui->eSDOFileNameTo->text());
    settings.endGroup();
}


void MainWindow::on_bSDOToOpenFile_2_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), ui->eSDOFileNameTo_2->text(), "Config_Files(*.*)") ;
    if (filepath.isEmpty())
        return;

    ui->eSDOFileNameTo_2->setText(filepath);

    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name to 2",ui->eSDOFileNameTo_2->text());
    settings.endGroup();
}


void MainWindow::on_bSDOToOpenFile_3_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), ui->eSDOFileNameTo_3->text(), "Config_Files(*.*)") ;
    if (filepath.isEmpty())
        return;

    ui->eSDOFileNameTo_3->setText(filepath);

    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name to 3",ui->eSDOFileNameTo_3->text());
    settings.endGroup();
}

void MainWindow::on_bSDOToOpenFile_4_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), ui->eSDOFileNameTo_4->text(), "Config_Files(*.*)") ;
    if (filepath.isEmpty())
        return;

    ui->eSDOFileNameTo_4->setText(filepath);

    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name to 4",ui->eSDOFileNameTo_4->text());
    settings.endGroup();
}

void MainWindow::on_bSDOToOpenFile_5_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), ui->eSDOFileNameTo_5->text(), "Config_Files(*.*)") ;
    if (filepath.isEmpty())
        return;

    ui->eSDOFileNameTo_5->setText(filepath);

    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("File name to 5",ui->eSDOFileNameTo_5->text());
    settings.endGroup();
}


void MainWindow::on_pushButton_3_clicked()
{
    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("AddressHeader",ui->eSDOAddressHeader->text());
    settings.setValue("SubAddressHeader",ui->eSDOSubAddressHeader->text());
    settings.endGroup();
}


void MainWindow::on_pushButton_4_clicked()
{
    QSettings settings;
    settings.beginGroup("SDO Parameters");
    settings.setValue("AddressBody",ui->eSDOAddressBody->text());
    settings.setValue("SubAddressBody",ui->eSDOSubAddressBody->text());
    settings.endGroup();
}

