#ifndef TDLGSTATUS_H
#define TDLGSTATUS_H

#include <QDialog>

namespace Ui {
class TDlgStatus;
}

class TDlgStatus : public QDialog
{
    Q_OBJECT

public:
    explicit TDlgStatus(QWidget *parent = nullptr);
    ~TDlgStatus();
private slots:
    void setStatus(int Status);
private:
    Ui::TDlgStatus *ui;
};

#endif // TDLGSTATUS_H
