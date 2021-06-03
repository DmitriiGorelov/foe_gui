#include "formpi.h"
#include "ui_formpi.h"

#include <QDebug>
#include <QKeyEvent>

QStringList labelsIn{"Name","Type", "Bit Size", "PI Offset", "Value", "Var Offset", "Alias"};
QStringList labelsOut{"Name","Type", "Bit Size", "PI Offset", "Value", "Var Offset", "Alias"};

#define infoIdxName 0
#define infoIdxType 1
#define infoIdxBitSize 2
#define infoIdxPiOffset 3
#define infoIdxValue 4
#define infoIdxVarOffset 5
#define infoIdxAlias 6


FormPI::FormPI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormPI)
    , node_initialized(false)
    , node(nullptr)
    , timerIn()
    , m_itemsIn()
    , m_itemsOut()
{
    ui->setupUi(this);

    //ui->tWrite->installEventFilter(this);
    connect(ui->tWrite, &QTableWidget::itemChanged, this, &FormPI::on_ItemChanged);
    connect(&timerIn, &QTimer::timeout, this, &FormPI::on_Timer);
    //timerIn.start(1000);

}

FormPI::~FormPI()
{
    delete ui;
}

void FormPI::PmasConnect()
{
    if (!pmas()->Connected())
        return;

    ui->eName->addItems(pmas()->getSlaves());
    timerIn.start(1000);
}


void FormPI::on_bUpdate_clicked()
{
    clear();
    update();
}

QString FormPI::readPIVar(bool out, int varOffset, int varType)
{
    try
    {
        switch (varType)
        {
            case ePI_SIGNED_SHORT: short sVar;                      node->EthercatReadPIVar(varOffset, out, sVar);      return(QString::number(sVar)); break;
            case ePI_UNSIGNED_SHORT: unsigned short usVar;          node->EthercatReadPIVar(varOffset, out, usVar);     return(QString::number(usVar)); break;
            case ePI_SIGNED_INT: int iVar;                          node->EthercatReadPIVar(varOffset, out, iVar);      return(QString::number(iVar)); break;
            case ePI_UNSIGNED_INT: unsigned int uiVar;              node->EthercatReadPIVar(varOffset, out, uiVar);     return(QString::number(uiVar)); break;
            case ePI_BOOL: bool bVar;                               node->EthercatReadPIVar(varOffset, out, bVar);      return(QString::number(bVar)); break;
            case ePI_SIGNED_CHAR: signed char cVar;                 node->EthercatReadPIVar(varOffset, out, cVar);      return(QString::number(cVar)); break;
            case ePI_UNSIGNED_CHAR: unsigned char ucVar;            node->EthercatReadPIVar(varOffset, out, ucVar);     return(QString::number(ucVar)); break;
            case ePI_SIGNED_LONG_LONG: long long llVar;             node->EthercatReadPIVar(varOffset, out, llVar);     return(QString::number(llVar)); break;
            case ePI_UNSIGNED_LONG_LONG: unsigned long long ullVar; node->EthercatReadPIVar(varOffset, out, ullVar);    return(QString::number(ullVar)); break;
            case ePI_FLOAT: float fVar;                             node->EthercatReadPIVar(varOffset, out, fVar);      return(QString::number(fVar)); break;
            case ePI_DOUBLE: double dVar;                           node->EthercatReadPIVar(varOffset, out, dVar);      return(QString::number(dVar)); break;
            /*case ePI_BITWISE: short outVar; node->EthercatReadPIVar(it[infoIdxVarOffset]->text().toInt(), 0, outVar); break;
            case ePI_8MULTIPLE: short outVar; node->EthercatReadPIVar(it[infoIdxVarOffset]->text().toInt(), 0, outVar); break;
            case ePI_INVALID:  short outVar; node->EthercatReadPIVar(it[infoIdxVarOffset]->text().toInt(), 0, outVar); break;*/
        }
    }
    catch (exception& e)
    {
        qInfo() << "exception";
    }
    return "";
}

void FormPI::writePIVar(int varOffset, int varType, QString value)
{
    try
    {
        switch (varType)
        {
            case ePI_SIGNED_SHORT: {short sVar=value.toShort();              node->EthercatWritePIVar(varOffset, sVar); break;}
            case ePI_UNSIGNED_SHORT: {unsigned short usVar=value.toUShort(); node->EthercatWritePIVar(varOffset, usVar); break;}
            case ePI_SIGNED_INT: {int iVar=value.toInt();                    node->EthercatWritePIVar(varOffset, iVar);   break;}
            case ePI_UNSIGNED_INT: {unsigned int uiVar=value.toUInt();       node->EthercatWritePIVar(varOffset, uiVar); break;}
            case ePI_BOOL: {bool bVar=value.toInt();                         node->EthercatWritePIVar(varOffset, bVar);   break;}
            case ePI_SIGNED_CHAR: {signed char cVar=value.toInt();           node->EthercatWritePIVar(varOffset, cVar);   break;}
            case ePI_UNSIGNED_CHAR: {unsigned char ucVar=value.toUInt();     node->EthercatWritePIVar(varOffset, ucVar); break;}
            case ePI_SIGNED_LONG_LONG: {long long llVar=value.toLongLong();  node->EthercatWritePIVar(varOffset, llVar); break;}
            case ePI_UNSIGNED_LONG_LONG: {unsigned long long ullVar=value.toULongLong();node->EthercatWritePIVar(varOffset, ullVar); break;}
            case ePI_FLOAT: {float fVar= value.toFloat();                     node->EthercatWritePIVar(varOffset, fVar);   break;}
            case ePI_DOUBLE: {double dVar=value.toDouble();                   node->EthercatWritePIVar(varOffset, dVar);   break;}
            /*case ePI_BITWISE: short outVar; node->EthercatReadPIVar(it[infoIdxVarOffset]->text().toInt(), 0, outVar); break;
            case ePI_8MULTIPLE: short outVar; node->EthercatReadPIVar(it[infoIdxVarOffset]->text().toInt(), 0, outVar); break;
            case ePI_INVALID:  short outVar; node->EthercatReadPIVar(it[infoIdxVarOffset]->text().toInt(), 0, outVar); break;*/
        }
    }
    catch (exception& e)
    {
        qInfo() << "exception";
    }
}

void FormPI::on_Timer()
{
    if (!pmas()->Connected())
        return;

    if (!node_initialized || !node)
    {
        return;
    }

    for (auto it: m_itemsIn)
    {
        it[infoIdxValue]->setText(readPIVar(false,it[infoIdxVarOffset]->text().toInt(),StrToIOType(it[infoIdxType]->text())));
    }
}

void FormPI::on_ItemChanged(QTableWidgetItem *item)
{
    if (!item)
        return;
    int row=ui->tWrite->row(item);
    int col=ui->tWrite->column(item);
    auto itemName=ui->tWrite->item(row,0);
    if (!itemName)
        return;

    QString name=itemName->text();

    if (m_itemsOut.find(name)==m_itemsOut.end())
        return;

    writePIVar(m_itemsOut[name][infoIdxVarOffset]->text().toInt(),StrToIOType(m_itemsOut[name][infoIdxType]->text()),item->text());
}

void FormPI::clear()
{
    ui->tRead->clear();
    ui->tRead->setRowCount(0);
    ui->tRead->setColumnCount(labelsIn.size());
    ui->tRead->setHorizontalHeaderLabels(labelsIn);
    ui->tRead->verticalHeader()->hide();
    m_itemsIn.clear();


    ui->tWrite->clear();
    ui->tWrite->setRowCount(0);
    ui->tWrite->setColumnCount(labelsOut.size());
    ui->tWrite->setHorizontalHeaderLabels(labelsOut);
    ui->tWrite->verticalHeader()->hide();
    m_itemsOut.clear();
}

void FormPI::showEvent(QShowEvent *event)
{
    ui->eName->clear();

    if (!pmas()->Connected())
    {
        return ;
    }
}

int StrToIOType(QString value)
{
    if (value=="SHORT")      return ePI_SIGNED_SHORT;
    if (value=="U SHORT")    return ePI_UNSIGNED_SHORT;
    if (value=="INT")        return ePI_SIGNED_INT;
    if (value=="U INT")      return ePI_UNSIGNED_INT;
    if (value=="BOOL")       return ePI_BOOL;
    if (value=="S CHAR")     return ePI_SIGNED_CHAR;
    if (value=="U CHAR")     return ePI_UNSIGNED_CHAR;
    if (value=="LONG LONG")  return ePI_SIGNED_LONG_LONG;
    if (value=="U LONG LONG")return ePI_UNSIGNED_LONG_LONG;
    if (value=="FLOAT")      return ePI_FLOAT;
    if (value=="DOUBLE")     return ePI_DOUBLE;
    if (value=="BITWISE")    return ePI_BITWISE;
    if (value=="8 MULTIPLE") return ePI_8MULTIPLE;
    if (value=="INVALID")    return ePI_INVALID;

    return ePI_INVALID;
}

QString ioTypeToStr(char ucVarType)
{
    switch (ucVarType)
    {
        case ePI_SIGNED_SHORT:          return "SHORT"      ;
        case ePI_UNSIGNED_SHORT:        return "U SHORT"    ;
        case ePI_SIGNED_INT:            return "INT"        ;
        case ePI_UNSIGNED_INT:          return "U INT"      ;
        case ePI_BOOL:                  return "BOOL"       ;
        case ePI_SIGNED_CHAR:           return "S CHAR"     ;
        case ePI_UNSIGNED_CHAR:         return "U CHAR"     ;
        case ePI_SIGNED_LONG_LONG:      return "LONG LONG"  ;
        case ePI_UNSIGNED_LONG_LONG	:   return "U LONG LONG";
        case ePI_FLOAT:                 return "FLOAT"      ;
        case ePI_DOUBLE:                return "DOUBLE"     ;
        case ePI_BITWISE:               return "BITWISE"    ;
        case ePI_8MULTIPLE:             return "8 MULTIPLE" ;
        case ePI_INVALID:               return "INVALID"    ;
        default: return "INVALID";
    }
}

void FormPI::update()
{
    node_initialized=false;
    delete node;

    try
    {
        node = new CMMCNode();
        node->InitAxisData(ui->eName->currentText().toStdString().c_str(),pmas()->getConnHndl());
    }
    catch (exception& e)
    {
        return;
    }

    QString name=ui->eName->currentText();
    int ref = pmas()->getAxisRef(name);

    if (ref < 0)
    {
        return;
    }

    bool oldState = ui->tWrite->blockSignals(true);


    int it=-1;
    while (true)
    {
        it++;
        MMC_GETPIVARSRANGEINFO_IN PIVarsRangeInfoIn;
        PIVarsRangeInfoIn.ucDirection = ePI_INPUT;
        PIVarsRangeInfoIn.usFirstIndex = it;
        PIVarsRangeInfoIn.usLastIndex = it;
        MMC_GETPIVARSRANGEINFO_OUT PIVarsRangeInfoOut;

        int rc = pmas()->wrp_MMC_GetPIVarsRangeInfo(ref, &PIVarsRangeInfoIn, &PIVarsRangeInfoOut);
        if (rc != 0)
        {
            break;
        }
        QString PIAlias(PIVarsRangeInfoOut.pVarInfo[0].pAliasing);
        unsigned int uiBitSize=PIVarsRangeInfoOut.pVarInfo[0].uiBitSize;
        unsigned int uiBitOffset=PIVarsRangeInfoOut.pVarInfo[0].uiBitOffset;
        unsigned short usCanOpenIndex=PIVarsRangeInfoOut.pVarInfo[0].usCanOpenIndex;
        unsigned char ucCanOpenSubIndex=PIVarsRangeInfoOut.pVarInfo[0].ucCanOpenSubIndex;
        unsigned char ucVarType=PIVarsRangeInfoOut.pVarInfo[0].ucVarType;


        MMC_GETPIVARINFOBYALIAS_IN PIVarInfoByAliasIn;
        MMC_GETPIVARINFOBYALIAS_OUT PIVarInfoByAliasOut;

        strcpy_s(PIVarInfoByAliasIn.pAliasing, PIAlias.toStdString().c_str());

        rc = pmas()->wrp_MMC_GetPIVarInfoByAlias(ref, &PIVarInfoByAliasIn, &PIVarInfoByAliasOut);
        if (rc != 0)
        {
            break;
        }

        unsigned short usPIVarOffset = PIVarInfoByAliasOut.VarInfo.usPIVarOffset;


        int row=ui->tRead->rowCount();
        ui->tRead->insertRow(row);

        for(int i =0; i < labelsIn.size(); i++)
        {
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
            ui->tRead->setItem(row,i,item);

            m_itemsIn[PIAlias][i] = item;
            switch(i)
            {
                case infoIdxName: item->setText(PIAlias); break;
                case infoIdxType: item->setText(ioTypeToStr(ucVarType)); break;
                case infoIdxBitSize: item->setText(QString::number(uiBitSize)); break;
                case infoIdxPiOffset: item->setText(QString::number(uiBitOffset)); break;
                case infoIdxValue:  item->setText(QString::number(0)); break;
                case infoIdxVarOffset:  item->setText(QString::number(usPIVarOffset)); break;
                case infoIdxAlias: item->setText(PIAlias); break;
            }
        }
    }

    it=-1;
    while (true)
    {
        it++;
        MMC_GETPIVARSRANGEINFO_IN PIVarsRangeInfoIn;
        PIVarsRangeInfoIn.ucDirection = ePI_OUTPUT;
        PIVarsRangeInfoIn.usFirstIndex = it;
        PIVarsRangeInfoIn.usLastIndex = it;
        MMC_GETPIVARSRANGEINFO_OUT PIVarsRangeInfoOut;

        int rc = pmas()->wrp_MMC_GetPIVarsRangeInfo(ref, &PIVarsRangeInfoIn, &PIVarsRangeInfoOut);
        if (rc != 0)
        {
            break;
        }
        QString PIAlias(PIVarsRangeInfoOut.pVarInfo[0].pAliasing);
        unsigned int uiBitSize=PIVarsRangeInfoOut.pVarInfo[0].uiBitSize;
        unsigned int uiBitOffset=PIVarsRangeInfoOut.pVarInfo[0].uiBitOffset;
        unsigned short usCanOpenIndex=PIVarsRangeInfoOut.pVarInfo[0].usCanOpenIndex;
        unsigned char ucCanOpenSubIndex=PIVarsRangeInfoOut.pVarInfo[0].ucCanOpenSubIndex;
        unsigned char ucVarType=PIVarsRangeInfoOut.pVarInfo[0].ucVarType;

        MMC_GETPIVARINFOBYALIAS_IN PIVarInfoByAliasIn;
        MMC_GETPIVARINFOBYALIAS_OUT PIVarInfoByAliasOut;

        strcpy_s(PIVarInfoByAliasIn.pAliasing, PIAlias.toStdString().c_str());

        rc = pmas()->wrp_MMC_GetPIVarInfoByAlias(ref, &PIVarInfoByAliasIn, &PIVarInfoByAliasOut);
        if (rc != 0)
        {
            break;
        }

        unsigned short usPIVarOffset = PIVarInfoByAliasOut.VarInfo.usPIVarOffset;

        int row=ui->tWrite->rowCount();
        ui->tWrite->insertRow(row);

        for(int i =0; i < labelsIn.size(); i++)
        {
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
            ui->tWrite->setItem(row,i,item);

            m_itemsOut[PIAlias][i] = item;
            switch(i)
            {
                case infoIdxName: item->setText(PIAlias); break;
                case infoIdxType: item->setText(ioTypeToStr(ucVarType)); break;
                case infoIdxBitSize: item->setText(QString::number(uiBitSize)); break;
                case infoIdxPiOffset: item->setText(QString::number(uiBitOffset)); break;
                //case infoIdxValue:  item->setText(QString::number(0)); item->setFlags(item->flags() | Qt::ItemIsEditable); break;
                case infoIdxValue:  item->setText(readPIVar(true,usPIVarOffset,ucVarType)); item->setFlags(item->flags() | Qt::ItemIsEditable); break;
                case infoIdxVarOffset:  item->setText(QString::number(usPIVarOffset)); break;
                case infoIdxAlias: item->setText(PIAlias); break;
            }
        }
    }

    // do some stuff
    ui->tWrite->blockSignals(oldState);

    node_initialized=true;

}

