#include "tdlgstatus.h"
#include "ui_tdlgstatus.h"

TDlgStatus::TDlgStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TDlgStatus)
{
    ui->setupUi(this);
}
//--------------------------------------------
TDlgStatus::~TDlgStatus()
{
    delete ui;
}
//--------------------------------------------
void TDlgStatus::setStatus(int Status)
{
    ui->progressBar->setValue(Status);
}
