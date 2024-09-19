#include "tdlgimg.h"
#include "ui_tdlgimg.h"

TDlgImg::TDlgImg(QWidget *parent, QPixmap img,bool withProgress) :
    QDialog(parent),
    ui(new Ui::TDlgImg)
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);
    ui->lblImg->setPixmap(img);
    ui->scrollArea->setWidget(ui->lblImg);
    ui->progressBar->setVisible(withProgress);
}
//----------------------------------
TDlgImg::~TDlgImg()
{
    delete ui;
}
//----------------------------------
void TDlgImg::receiveImg()
{

}
//----------------------------------
void TDlgImg::mouseDoubleClickEvent(QMouseEvent* event)
{
    this->close();
}
//----------------------------------
void TDlgImg::setStatus(int Status)
{
    ui->progressBar->setValue(Status);
}
