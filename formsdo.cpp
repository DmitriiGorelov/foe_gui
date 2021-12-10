#include "formsdo.h"

#include <QDebug>
#include <QMap>
#include <QMessageBox>
#include <QFileDialog>

#include "ui_formsdo.h"

#include "IOType.h"

QMap<QString, int> labelsTypes{{"4 Integer", eIOType::eIOTypeInt},
                            {"4 Float", eIOType::eIOTypeFloat},
                            {"2 Signed Short", eIOType::eIOTypeSignedShort},
                            {"8 Double", eIOType::eIOTypeDouble},
                            {"8 ULL", eIOType::eIOTypeULL},
                            {"8 LL", eIOType::eIOTypeLL},
                            {"4 UL", eIOType::eIOTypeULong},
                            {"4 Long", eIOType::eIOTypeLong},
                            {"4 UInteger", eIOType::eIOTypeUI},
                            {"2 UShort", eIOType::eIOTypeUShort},
                            {"1 UChar", eIOType::eIOTypeUnsignedChar},
                            {"1 Char", eIOType::eIOTypeChar},
                            {"x Char[80]", eIOType::eIOTypeDIO},
                           };

FormSDO::FormSDO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSDO)
{
    ui->setupUi(this);
    for (auto it : labelsTypes.keys())
    {
        ui->cbDataType->addItem(it);
    }
}

FormSDO::~FormSDO()
{
    delete ui;
}

void FormSDO::PmasConnected()
{
    if (!pmas()->Connected())
        return;

    ui->eName->addItems(pmas()->getSlaveNames());
    //timerIn.start(1000);
}

void FormSDO::on_bSendSDO_clicked()
{
    auto it = labelsTypes.find(ui->cbDataType->currentText());
    if (it==labelsTypes.end())
    {
        return;
    }

    QString val=ui->eData->text();
    tuData udata;
    bool ok;
    unsigned short address=ui->eAddress->text().toUInt(&ok,16);// toStdString().c_str());
    unsigned char subAddress = ui->eSubAddress->value();
    int dataSize = val.size();
    QByteArray Data;

    auto copydata=[&](){
         Data=QByteArray::fromRawData(reinterpret_cast<char*>(udata.pData), dataSize);
    };

    switch(it.value())
    {
        case IOTypeInt: udata.iData = val.toInt(); dataSize = 4; copydata(); break;
        case IOTypeFloat: udata.fData = val.toFloat(); dataSize = 4; copydata(); break;
        case IOTypeSignedShort: udata.sData = val.toShort(); dataSize = 2; copydata();	break;
        case IOTypeDouble: udata.dbData = val.toDouble(); dataSize = 8; copydata();	break;
        case IOTypeULL: udata.ullData = val.toULongLong(); dataSize = 8; copydata(); break;
        case IOTypeLL: udata.llData = val.toLongLong();	 dataSize = 8; copydata(); break;
        case IOTypeULong: udata.ulData = val.toULong(); dataSize = 8; copydata(); break;
        case IOTypeLong: udata.lData = val.toLong(); dataSize = 4; copydata();	break;
        case IOTypeUI: udata.uiData = val.toUInt();	dataSize = 4; copydata(); break;
        case IOTypeUShort: udata.usData = val.toShort(); dataSize = 2; copydata(); break;
        case IOTypeUnsignedChar: udata.ucData = val.toShort(); dataSize = 1; copydata(); break;
        case IOTypeChar: udata.cData = val.toShort(); dataSize = 1; copydata(); break;
        case IOTypeDIO:
            {
                QFile CurrentFile(val);
                if(!CurrentFile.open(QIODevice::ReadOnly))
                {
                    ui->eData->setText("Wrong file name! " + val);
                }
                Data = CurrentFile.readAll();
                dataSize = Data.size();

                break;
            }
        default:
            //DEBUG_MESSAGE("eIOType type is not defined in " + QString(__FILE__) + " " + Cast::to_str(__LINE__));
            //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
            //typ = IOTypeUnknown;
            break;
    }

    size_t blockSize=ui->eDataSize->value();
    for (int k = 0; k<dataSize; k+=blockSize)
    {
        memcpy(udata.pData, Data.data()+k, min(static_cast<size_t>(dataSize-k),blockSize));
        if(!pmas()->SendSDO(ui->eName->currentText(), udata, address, subAddress, blockSize, true, eSDODirection::WRITE))
        {
            ui->eResult->setText("ERROR!");
            break;
        }
        else
        {
            ui->eResult->setText("OK!");
        }
    }
}

void FormSDO::on_bReadSDO_clicked()
{
    auto it = labelsTypes.find(ui->cbDataType->currentText());
    if (it==labelsTypes.end())
    {
        return;
    }

    auto dataType=it.value();
    QString val=ui->eData->text();
    tuData udata;
    bool ok;
    unsigned short address=ui->eAddress->text().toUInt(&ok,16);//.toStdString().c_str());
    unsigned char subAddress = ui->eSubAddress->value();
    int dataSize = val.size();

    switch(dataType)
    {
        case IOTypeInt: udata.iData = val.toInt(); dataSize = 4;	break;
        case IOTypeFloat: udata.fData = val.toFloat(); dataSize = 4; break;
        case IOTypeSignedShort: udata.sData = val.toShort(); dataSize = 2;	break;
        case IOTypeDouble: udata.dbData = val.toDouble(); dataSize = 8;	break;
        case IOTypeULL: udata.ullData = val.toULongLong(); dataSize = 8; break;
        case IOTypeLL: udata.llData = val.toLongLong();	 dataSize = 8; break;
        case IOTypeULong: udata.ulData = val.toULong(); dataSize = 8; break;
        case IOTypeLong: udata.lData = val.toLong(); dataSize = 4;	break;
        case IOTypeUI: udata.uiData = val.toUInt();	dataSize = 4; break;
        case IOTypeUShort: udata.usData = val.toShort(); dataSize = 2; break;
        case IOTypeUnsignedChar: udata.ucData = val.toShort(); dataSize = 1; break;
        case IOTypeChar: udata.cData = val.toShort(); dataSize = 1; break;
        case IOTypeDIO: dataSize=ui->eDataSize->value(); break;
        default:
            //DEBUG_MESSAGE("eIOType type is not defined in " + QString(__FILE__) + " " + Cast::to_str(__LINE__));
            //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
            //typ = IOTypeUnknown;
            break;
    }

    if (!pmas()->SendSDO(ui->eName->currentText(), udata, address, subAddress, dataSize, true, eSDODirection::READ))
    {
        ui->eResult->setText("ERROR!");
        return;
    }

    switch(it.value())
    {
        case IOTypeInt: val=QString::number(udata.iData); break;
        case IOTypeFloat:  val=QString::number(udata.fData); break;
        case IOTypeSignedShort:  val=QString::number(udata.sData); break;
        case IOTypeDouble:  val=QString::number(udata.dbData); break;
        case IOTypeULL:  val=QString::number(udata.ullData); break;
        case IOTypeLL:  val=QString::number(udata.llData);	 break;
        case IOTypeULong:  val=QString::number(udata.ulData); break;
        case IOTypeLong:  val=QString::number(udata.lData); break;
        case IOTypeUI:  val=QString::number(udata.uiData);	break;
        case IOTypeUShort:  val=QString::number(udata.usData); break;
        case IOTypeUnsignedChar:  val=QString::number(udata.ucData); break;
        case IOTypeChar:  val=QString::number(udata.cData); break;
        case IOTypeDIO: val=QString(reinterpret_cast< char* >(udata.pData)); break;
        default:
            //DEBUG_MESSAGE("eIOType type is not defined in " + QString(__FILE__) + " " + Cast::to_str(__LINE__));
            //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
            //typ = IOTypeUnknown;
            break;
    }
    ui->eResult->setText(val);
}

void FormSDO::on_bOpenFile_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), "","Config_Files(*.*)") ;
    if (filepath.isEmpty())
        return;

    ui->eData->setText(filepath);

}

void FormSDO::on_cbDataType_activated(const QString &arg1)
{
    auto it = labelsTypes.find(arg1);
    if (it==labelsTypes.end())
    {
        return;
    }

    auto dataType=it.value();
    QString val=ui->eData->text();
    int dataSize = val.size();

    ui->eDataSize->setEnabled(false);
    switch(dataType)
    {
        case IOTypeInt: dataSize = 4;	break;
        case IOTypeFloat: dataSize = 4; break;
        case IOTypeSignedShort: dataSize = 2;	break;
        case IOTypeDouble: dataSize = 8;	break;
        case IOTypeULL: dataSize = 8; break;
        case IOTypeLL: dataSize = 8; break;
        case IOTypeULong: dataSize = 4; break;
        case IOTypeLong: dataSize = 4;	break;
        case IOTypeUI: dataSize = 4; break;
        case IOTypeUShort: dataSize = 2; break;
        case IOTypeUnsignedChar: dataSize = 1; break;
        case IOTypeChar: dataSize = 1; break;
        case IOTypeDIO: dataSize=NODE_ASCII_ARRAY_MAX_LENGTH; ui->eDataSize->setEnabled(true); break;
        default:
            //DEBUG_MESSAGE("eIOType type is not defined in " + QString(__FILE__) + " " + Cast::to_str(__LINE__));
            //lerr << ("eIOType type is not defined in " + RefFileFunctLine);
            //typ = IOTypeUnknown;
            break;
    }
    ui->eDataSize->setValue(dataSize);
}

