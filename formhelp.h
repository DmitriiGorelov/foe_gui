#ifndef FORMHELP_H
#define FORMHELP_H

#include <QWidget>

namespace Ui {
class FormHelp;
}

class FormHelp : public QWidget
{
    Q_OBJECT

public:
    explicit FormHelp(QWidget *parent = nullptr);
    ~FormHelp();

private slots:
    void on_btnClose_clicked();

private:
    Ui::FormHelp *ui;
};

#endif // FORMHELP_H
