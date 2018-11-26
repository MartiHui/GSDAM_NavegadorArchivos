#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QWidget>
#include <QFile>

#include "dircontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString formatSize(qint64 fileSize);
    QString formatPermissions(QFile::Permissions permisos);
    QString checkPermission(QString symbol, int flag, QFile::Permissions permisos);

public:
    DirController m_dirController;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void update();

private slots:
    void on_lastDir_clicked();

    void on_dirContents_itemDoubleClicked(QListWidgetItem *item);

    void on_dirContents_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
