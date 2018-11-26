#include "dircontroller.h"

#include <QDir>
#include <QDebug>

DirController::DirController() {
    getLastDir();
}

// Obtenemos el último directorio a el que hemos accedido. En caso de no haber, se obtienen los discos del sistema
void DirController::getLastDir() {
    if (m_dirHistory.isEmpty()) {
        getDrives();
    } else {
        QString temp = m_dirHistory.takeLast();
        if (temp == "") {
            getDrives();
        } else {
            QDir dir(temp);
            m_currentDirContents = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);

            m_currentDir = dir.path();
        }
    }
}

void DirController::getDrives() {
    m_currentDirContents = QDir::drives();

    m_currentDir = "";
}

// Se obtienen los contenidos del directorio path, omitiendo las carpetas especiales . y ..
void DirController::accessDir(QString path) {
    m_dirHistory.push_back(m_currentDir);

    m_currentDir = path;

    QDir dir(m_currentDir);
    m_currentDirContents = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
}
