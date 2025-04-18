#include "tdlgoptions.h"
#include "ui_tdlgoptions.h"

extern TVars Vars;

TDlgOptions::TDlgOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TDlgOptions)
{
    ui->setupUi(this);
    cargaOtherConfig();
}
//--------------------------------------------
TDlgOptions::~TDlgOptions()
{
    delete ui;
}
//--------------------------------------------
void TDlgOptions::on_btnExit_clicked()
{
    this->close();
}
//--------------------------------------------
void TDlgOptions::cargaOtherConfig()
{
    /*Archivo=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)+"/SendMail.ini";
    QSettings Settings(Archivo,QSettings::IniFormat);
    ui->chkPrevTagged->setChecked(Settings.value("PrevTagged","false").toBool());
    Vars.PrevTagged=ui->chkPrevTagged->isChecked();*/
    ui->chkPrevTagged->setChecked(Vars.PrevTagged);
    ui->chkSimpleName->setChecked(Vars.SimpleName);
    ui->chkTwitter->setChecked(Vars.extTwitter);
    ui->cmbTema->setCurrentIndex(Vars.Tema);
}
//--------------------------------------------
void TDlgOptions::guardaOtherConfig()
{
    Archivo=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)+"/SendMail.ini";
    QSettings Settings(Archivo,QSettings::IniFormat);
    Settings.setValue("PrevTagged",ui->chkPrevTagged->isChecked());
    Vars.PrevTagged=ui->chkPrevTagged->isChecked();
    Settings.setValue("extTwitter",ui->chkTwitter->isChecked());
    Vars.extTwitter=ui->chkTwitter->isChecked();
    Settings.setValue("SimpleName",ui->chkSimpleName->isChecked());
    Vars.SimpleName=ui->chkSimpleName->isChecked();
    Settings.setValue("Tema",ui->cmbTema->currentIndex());
    Vars.Tema=ui->cmbTema->currentIndex();
    QMessageBox::information(this,"SendMail","Configuración guardada exitosamente",QMessageBox::Ok);
}
//--------------------------------------------
void TDlgOptions::on_btnSave_clicked()
{
    guardaOtherConfig();
}

