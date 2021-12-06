#ifndef FORMSDO_H
#define FORMSDO_H

#include <QWidget>

#include "Controller.h"
#include "enums.h"

namespace Ui {
    class FormSDO;
}

class FormSDO : public QWidget
{
    Q_OBJECT

public:
    explicit FormSDO(QWidget *parent = nullptr);
    ~FormSDO();

    void PmasConnected();

private slots:
    void on_bSendSDO_clicked();

    void on_bReadSDO_clicked();

    void on_bOpenFile_clicked();

    void on_cbDataType_activated(const QString &arg1);

private:
    //bool SendSDO(tuData& data, unsigned short address, unsigned char subAddress, int dataSize, bool reportIfError, eSDODirection::E direction);

private:
    Ui::FormSDO *ui;
};

#endif // FORMSDO_H
