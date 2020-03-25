#ifndef LOADFILETHREAD_H
#define LOADFILETHREAD_H

#include <QThread>
#include <QFile>


class FileLoader : public QObject{
    Q_OBJECT
public:
    explicit FileLoader(QObject *parent = 0, QString _filePath = "");
    void DoSetup(QThread  &cThread);

    QString filePath;

signals:
    void errorOpeningFile();
    void fileLoading();
    void fileUploaded(QString text);

public slots:
    void DoWork();

};

#endif // LOADFILETHREAD_H
