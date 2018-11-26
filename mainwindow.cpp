#include <QFileInfoList>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QDateTime>
#include <QFileDevice>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Actualiza el nombre del directorio actual y muestra sus contenidos
void MainWindow::update() {
    QString temp = (m_dirController.m_currentDir == "") ?
                QString("Dispositivos y unidades") : m_dirController.m_currentDir;
    ui->currentDir->setText(temp);
    ui->dirContents->clear();

    QFileInfoList *fileList = &m_dirController.m_currentDirContents;
    for (int i = 0; i < fileList->size(); i++) {
        QFileInfo info = fileList->at(i);
        //ui->dirContents->addItem(info.fileName());
        ui->dirContents->addItem(info.canonicalFilePath());
    }

    for (int i = 0; i < m_dirController.m_dirHistory.size(); i++) {
        qDebug() << m_dirController.m_dirHistory[i];
    }
    qDebug() << "";
}

void MainWindow::on_lastDir_clicked() {
    m_dirController.getLastDir();
    update();
}

void MainWindow::on_dirContents_itemDoubleClicked(QListWidgetItem *item) {
    //QString path = m_dirController.m_currentDir + QString("/") + item->text();
    QString path = item->text();
    QFileInfo info(path);

    if (info.isDir()) {
        m_dirController.accessDir(path);
        update();
    } else {
        QDesktopServices::openUrl(QUrl(QString("file:///") + path, QUrl::TolerantMode));
    } // end if
}

void MainWindow::on_dirContents_itemClicked(QListWidgetItem *item) {
    QString path = item->text();
    QFileInfo info(path);

    ui->nombre_lbl->setText(info.baseName());
    ui->tipo_lbl->setText((info.isDir()) ? QString("Carpeta") : QString("Archivo"));
    ui->size_lbl->setText((info.isDir()) ? "" : formatSize(info.size()));
    ui->acceso_lbl->setText(info.lastRead().toString());
    ui->modificacion_lbl->setText(info.lastModified().toString());
    ui->permisos_lbl->setText(formatPermissions(info.permissions()));
}

QString MainWindow::formatSize(qint64 fileSize) {
    double num;
    QString extension;

    if (fileSize < std::pow(2, 10)) {
        num = fileSize;
        extension = QString(" B");
    } else if (fileSize < std::pow(2, 20)) {
        num = static_cast<double>(fileSize)/std::pow(2, 10);
        extension = QString(" KB");
    } else if (fileSize < std::pow(2, 30)) {
        num = static_cast<double>(fileSize)/std::pow(2, 20);
        extension = QString(" MB");
    } else {
        num = static_cast<double>(fileSize)/std::pow(2, 30);
        extension = QString(" GB");
    }

    num = std::round(num * 100)/100;
    return QString::number(num) + extension;
}

QString MainWindow::formatPermissions(QFile::Permissions permisos) {
    QString str("");
    str += checkPermission("r", QFileDevice::ReadOwner, permisos);
    str += checkPermission("w", QFileDevice::WriteOwner, permisos);
    str += checkPermission("x", QFileDevice::ExeOwner, permisos);
    str += " ";
    str += checkPermission("r", QFileDevice::ReadUser, permisos);
    str += checkPermission("w", QFileDevice::WriteUser, permisos);
    str += checkPermission("x", QFileDevice::ExeUser, permisos);
    str += " ";
    str += checkPermission("r", QFileDevice::ReadGroup, permisos);
    str += checkPermission("w", QFileDevice::WriteGroup, permisos);
    str += checkPermission("x", QFileDevice::ExeGroup, permisos);
    str += " ";
    str += checkPermission("r", QFileDevice::ReadOther, permisos);
    str += checkPermission("w", QFileDevice::WriteOther, permisos);
    str += checkPermission("x", QFileDevice::ExeOther, permisos);

    return str;
}

QString MainWindow::checkPermission(QString symbol, int flag, QFile::Permissions permisos) {
    QString temp;
    if (permisos & flag) {
        temp = symbol;
    } else {
        temp = "-";
    }
    return temp;
}

