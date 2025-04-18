#include "mainwindow.h"
#include "ui_mainwindow.h"

TVars Vars;

MainWindow::MainWindow(QApplication *App,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    a=App;
    clipboard = QApplication::clipboard();
    Sended=false;
    lblImg=new ClickableLabel(this);
    connect(lblImg,SIGNAL(clicked()),this,SLOT(abreImagen()));
    connect(this,SIGNAL(rightClicked()),this,SLOT(nuevoTitulo()));
    connect(this,SIGNAL(descargado()),this,SLOT(continueSendMail()));
    dialogUsed=false;
    lblImg->setMaximumSize(100,100);
    lblImg->setMinimumSize(100,100);
    lblImg->setScaledContents(true);
    ui->lyImg->addWidget(lblImg);
    cargaConfig();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//----------------------------------------------------------

void MainWindow::on_btnSend_clicked()
{
    Sended=false;

    if(!ui->lnEdtUrl->text().isEmpty()||dialogUsed)
    {
        if((dialogUsed)&&(ui->lnEdtSubj->text().isEmpty()))
        {
            ui->lnEdtSubj->setText(QUrl(ui->lstWAttach->item(0)->text()).fileName());
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);
        if(!ui->chkOpen->isChecked())
        {
            DlgStatus=new TDlgStatus(this);
            connect(this,SIGNAL(ProgStatus(int)),DlgStatus,SLOT(setStatus(int)));
            DlgStatus->show();
        }
        else
        {
            Sended=true;
        }
        if(dialogUsed)
        {
            //openImg(true);
            descargaImagen(ui->lstWAttach->item(ui->lstWAttach->count()-1)->text(),true);
        }
        else
        {
            descargaImagen(ui->lnEdtUrl->text(),true);
        }
    }
    //Sended=false;
}
//----------------------------------------------------------

void MainWindow::on_btnAttach_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
    {
        ui->lstWAttach->addItems(dialog.selectedFiles());
        loadMiniLocal(ui->lstWAttach->item(ui->lstWAttach->count()-1)->text());
        //descargaImagen(ui->lstWAttach->item(ui->lstWAttach->count()-1)->text(),false);
        dialogUsed=true;
    }
}
//----------------------------------------------------------
EmailAddress MainWindow::stringToEmail(const QString &str)
{
    int p1 = str.indexOf("<");
    int p2 = str.indexOf(">");

    if (p1 == -1)
    {
        // no name, only email address
        return EmailAddress(str);
    }
    else
    {
        return EmailAddress(str.mid(p1 + 1, p2 - p1 - 1), str.left(p1));
    }

}
//----------------------------------------------------------
void MainWindow::errorMessage(const QString &message)
{
    QErrorMessage err (this);
    err.showMessage(message);
    err.exec();
}
//----------------------------------------------------------
void MainWindow::descargaImagen(QString link,bool send)
{
    if(Vars.PrevTagged)
    {
        link=link.replace("/m3_static_max/","/0/");
        link=link.replace("/p/","/0/");
    }
    QUrl imageUrl(link);
    Url=link;
    m_pImgCtrl = new FileDownloader(imageUrl, this);    
    Send=send;
    connect(m_pImgCtrl, SIGNAL (downloaded()), this, SLOT (loadImage()));
}
//----------------------------------------------------------
void MainWindow::on_btnGet_clicked()
{
    descargaImagen(ui->lnEdtUrl->text(),false);
}
//----------------------------------------------------------
void MainWindow::loadImage()
{
    downloaded=false;
    if(!dialogUsed)  //Si no se cargó una imagen directamente cargar url
        buttonImage.loadFromData(m_pImgCtrl->downloadedData());
    int w = lblImg->width();
    int h = lblImg->height();
    lblImg->setPixmap(buttonImage.scaled(w,h,Qt::KeepAspectRatio));
    url=Url;
    QString nombre=url.fileName();

#if (defined (LINUX) || defined (__linux__))
    QFile archivo("/tmp/"+nombre);
    LocalFile="/tmp/"+nombre;
#endif
#if defined(WIN32)
    ruta=QStandardPaths::writableLocation(QStandardPaths::TempLocation)+"/"+nombre;
    QFile archivo(ruta);
    LocalFile=ruta;    
    if(dialogUsed)
        LocalFile=ui->lstWAttach->item(ui->lstWAttach->count()-1)->text();
#endif
    if (archivo.open(QIODevice::WriteOnly))
    {
        archivo.write(m_pImgCtrl->downloadedData());
        archivo.close();
        downloaded=true;
    }
    if(Vars.extTwitter)
    {
        archivo.rename(LocalFile,LocalFile+".jpg");
        LocalFile=LocalFile+".jpg";
    }
    //openImg(false);
    if(Sended)
    {
        openImg(true);
    }
    else
    {
        if(ui->chkOpen->isChecked())
        {
            openImg(false);
        }
    }
    if(Send)
        emit descargado();
}
//----------------------------------------------------------
void MainWindow::cargaImagen()
{    
    /*if(ui->chkOpen->isChecked())
        loadImage(false);
    else
        loadImage(true);*/
}
//----------------------------------------------------------
void MainWindow::on_btnSave_clicked()
{
    Archivo=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)+"/SendMail.ini";
    QSettings Settings(Archivo,QSettings::IniFormat);
    Settings.setValue("SMTP",ui->lnEdtSMTP->text());
    Settings.setValue("Port",ui->spPort->value());
    Settings.setValue("SSL",ui->chkSSL->isChecked());
    Settings.setValue("AutoOpen",ui->chkOpen->isChecked());
    Settings.setValue("Autenticate",ui->chkAuth->isChecked());
    Settings.setValue("User",ui->lnEdtUser->text());
    Settings.setValue("Password",ui->lnEdtPasswd->text());
    Settings.setValue("Sender",ui->lnEdtSender->text());
    Settings.setValue("Recipient",ui->lnEdtRecip->text());
    QMessageBox::information(this,"SendMail","Configuración guardada exitosamente",QMessageBox::Ok);
}
//----------------------------------------------------------
void MainWindow::cargaConfig()
{
    Archivo=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)+"/SendMail.ini";
    QSettings Settings(Archivo,QSettings::IniFormat);
    ui->lnEdtSMTP->setText(Settings.value("SMTP","").toString());
    ui->spPort->setValue(Settings.value("Port","").toInt());
    ui->chkSSL->setChecked(Settings.value("SSL","").toBool());
    ui->chkOpen->setChecked(Settings.value("AutoOpen","").toBool());
    ui->chkAuth->setChecked(Settings.value("Autenticate","").toBool());
    ui->lnEdtUser->setText(Settings.value("User","").toString());
    ui->lnEdtPasswd->setText(Settings.value("Password","").toString());
    ui->lnEdtSender->setText(Settings.value("Sender","").toString());
    ui->lnEdtRecip->setText(Settings.value("Recipient","").toString());
    Vars.PrevTagged=Settings.value("PrevTagged","false").toBool();
    Vars.SimpleName=Settings.value("SimpleName","false").toBool();
    Vars.extTwitter=Settings.value("ExtTwitter","false").toBool();
    Vars.Tema=Settings.value("Tema","3").toInt();
    cargaTema(Vars.Tema);
}
//----------------------------------------------------------
void MainWindow::openImg(bool showProgress)
{
    DlgImg=new TDlgImg(this,buttonImage,showProgress);
    DlgImg->setWindowFlag(Qt::WindowMaximizeButtonHint, true);
    connect(this,SIGNAL(ProgStatus(int)),DlgImg,SLOT(setStatus(int)));
    DlgImg->showMaximized();
}
//----------------------------------------------------------
void MainWindow::abreImagen()
{
    openImg(false);
}
//----------------------------------------------------------
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton)
    {
        emit rightClicked();
    }
}
//----------------------------------------------------------
void MainWindow::nuevoTitulo()
{
    ui->lnEdtSubj->clear();
}
//----------------------------------------------------------
void MainWindow::on_btnOpt_clicked()
{
    DlgOptions=new TDlgOptions(this);
    DlgOptions->setWindowFlag(Qt::WindowMaximizeButtonHint, true);
    DlgOptions->exec();
}
//----------------------------------------------------------
void MainWindow::on_btnNFile_clicked()
{
    if(!ui->lnEdtUrl->text().isEmpty())
    {
        clipboard->setText(QUrl(ui->lnEdtUrl->text()).fileName());
        ui->lnEdtUrl->clear();
        ui->statusbar->showMessage("Nombre del archivo copiado al porpapapeles exitosamente...",2000);
    }
}
//----------------------------------------------------------
void MainWindow::continueSendMail()
{
    emit ProgStatus(20);

    if(ui->lnEdtSubj->text().isEmpty())
    {
        if(Vars.SimpleName)
        {
            ui->lnEdtSubj->setText(QUrl(ui->lnEdtUrl->text()).fileName());
        }
        else
        {
            ui->lnEdtSubj->setText(ui->lnEdtUrl->text());
        }
    }
    QStringList stringList;
#if (defined (LINUX) || defined (__linux__))
    if(Vars.extTwitter)
    {
        stringList<<LocalFile;
    }
    else
    {
        stringList<<"/tmp/"+QUrl(ui->lnEdtUrl->text()).fileName();
    }
#endif
#if defined(WIN32)
    if(Vars.extTwitter)
    {
        stringList<<LocalFile;
    }
    else
    {
        stringList<<QStandardPaths::writableLocation(QStandardPaths::TempLocation)+"/"+QUrl(ui->lnEdtUrl->text()).fileName();
    }
#endif
    ui->lstWAttach->addItems(stringList);
    QString host = ui->lnEdtSMTP->text();
    int port = ui->spPort->value();
    bool ssl = ui->chkSSL->isChecked();
    bool auth = ui->chkAuth->isChecked();
    QString user = ui->lnEdtUser->text();
    QString password = ui->lnEdtPasswd->text();

    EmailAddress sender = stringToEmail(ui->lnEdtSender->text());

    QStringList rcptStringList = ui->lnEdtRecip->text().split(';');

    QString subject = ui->lnEdtSubj->text();
    QString html = ui->txtMsg->toHtml();

    SmtpClient smtp (host, port, ssl ? SmtpClient::SslConnection : SmtpClient::TcpConnection);

    MimeMessage message;

    message.setSender(sender);
    message.setSubject(subject);

    for (int i = 0; i < rcptStringList.size(); ++i)
        message.addRecipient(stringToEmail(rcptStringList.at(i)));

    MimeHtml content;
    content.setHtml(html);

    message.addPart(&content);

    QList<QFile*> files;
    QList<MimeAttachment*> attachments;
    for (int i = 0; i < ui->lstWAttach->count(); ++i)
    {
        QFile* file = new QFile(ui->lstWAttach->item(i)->text());
        if(file->size()>0)
            files.append(file);

        MimeAttachment* attachment = new MimeAttachment(file);
        attachments.append(attachment);

        message.addPart(attachment);
    }

    smtp.connectToHost();
    emit ProgStatus(30);
    if (!smtp.waitForReadyConnected())
    {
        errorMessage("Conexión fallida.");
        return;
    }

    if (auth)
    {
        smtp.login(user, password);
        emit ProgStatus(50);
        if (!smtp.waitForAuthenticated())
        {
            errorMessage("Autenticación fallida.");
            return;
        }
    }

    smtp.sendMail(message);
    emit ProgStatus(70);
    if (!smtp.waitForMailSent())
    {
        errorMessage("Error al enviar correo.");
        return;
    }
    else
    {
        QApplication::restoreOverrideCursor();
        QMessageBox okMessage (this);
        if(DlgStatus!=nullptr)
        {
            DlgStatus->close();
        }
        emit ProgStatus(100);
        okMessage.setText("Correo enviado exitosamente.");
        okMessage.exec();
    }

    smtp.quit();

    for (auto file : files) {
        delete file;
    }

    for (auto attachment : attachments) {
        delete attachment;
    }
    ui->lstWAttach->clear();
    ui->lnEdtUrl->clear();
    dialogUsed=false;
    QApplication::restoreOverrideCursor();
}
//----------------------------------------------------------
void MainWindow::loadMiniLocal(QString ruta)
{
    buttonImage.load(ruta);
    int w = lblImg->width();
    int h = lblImg->height();
    lblImg->setPixmap(buttonImage.scaled(w,h,Qt::KeepAspectRatio));
}
//----------------------------------------------------------
void MainWindow::cargaTema(int nTema)
{
    // Obtener la ruta del directorio del ejecutable
    QString appDir = QCoreApplication::applicationDirPath();

    // Construir la ruta completa al archivo de estilo
    QString styleFilePath = QDir(appDir).filePath("temas/stylesSkin0"+QString::number(nTema+1)+".qss");
    QFile file(styleFilePath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        a->setStyleSheet(styleSheet);
        file.close();
    } else {
        qWarning("No se pudo abrir el archivo de estilo.");
    }
}
