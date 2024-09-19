#ifndef TDLGIMG_H
#define TDLGIMG_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class TDlgImg;
}

class TDlgImg : public QDialog
{
    Q_OBJECT

public:
    explicit TDlgImg(QWidget *parent = nullptr,QPixmap img=QPixmap(0,0),bool withProgress=false);
    ~TDlgImg();
private slots:
    void receiveImg();
    void setStatus(int Status);
protected:
    void mouseDoubleClickEvent(QMouseEvent* event);
private:
    Ui::TDlgImg *ui;

};

#endif // TDLGIMG_H
