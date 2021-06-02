#ifndef FORMPI_H
#define FORMPI_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QTimer>

#include "Controller.h"

int StrToIOType(QString value);
QString ioTypeToStr(char ucVarType);

namespace Ui {
class FormPI;
}

class FormPI : public QWidget
{
    Q_OBJECT

public:
    explicit FormPI(QWidget *parent = nullptr);
    ~FormPI();

protected:
    void clear();
    void update();

    bool CheckControllerMode();

    QString readPIVar(bool out, int varOffset, int varType);
    void writePIVar(int varOffset, int varType, QString value);

    void showEvent(QShowEvent *event) override;

private slots:
    void on_bUpdate_clicked();
    void on_Timer();    
    void on_ItemChanged(QTableWidgetItem *item);

private:
    Ui::FormPI *ui;

    bool node_initialized;
    CMMCNode* node;

    QTimer timerIn;

    QMap<QString,  QMap<int, QTableWidgetItem* > > m_itemsIn;
    QMap<QString,  QMap<int, QTableWidgetItem* > > m_itemsOut;
};

#endif // FORMPI_H
