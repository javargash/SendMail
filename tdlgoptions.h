#ifndef TDLGOPTIONS_H
#define TDLGOPTIONS_H

#include <QDialog>
#include <QStandardPaths>
#include <QSettings>
#include <QMessageBox>
#include "tvars.h"

namespace Ui {
class TDlgOptions;
}

class TVars;

class TDlgOptions : public QDialog
{
    Q_OBJECT

public:
    explicit TDlgOptions(QWidget *parent = nullptr);
    ~TDlgOptions();

private slots:
    void on_btnExit_clicked();
    void cargaOtherConfig();
    void guardaOtherConfig();

    void on_btnSave_clicked();

private:
    Ui::TDlgOptions *ui;
    QString Archivo;
};

#endif // TDLGOPTIONS_H
