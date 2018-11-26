#ifndef DIRCONTROLLER_H
#define DIRCONTROLLER_H

#include <QVector>
#include <QString>
#include <QFileInfo>

class DirController {
private:
    void getDrives();

public:
    QVector<QString> m_dirHistory; // Contenedor con las rutas de los directorios visitados
    QString m_currentDir;   // EL directorio actual
    QFileInfoList m_currentDirContents; // Contenido del directorio actual

    DirController();
    void getLastDir();
    void accessDir(QString path);
};

#endif // DIRCONTROLLER_H
