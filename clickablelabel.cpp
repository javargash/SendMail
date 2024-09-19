#include "clickablelabel.h"
#include "qapplication.h"

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}

void ClickableLabel::mouseMoveEvent(QMouseEvent* event)
{
    //QWidget *underMouse = QApplication::widgetAt(QCursor::pos())
}
