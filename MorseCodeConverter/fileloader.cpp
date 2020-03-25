#include "fileloader.h"

#include <QtCore>
#include <QMessageBox>

FileLoader::FileLoader(QObject *parent, QString _filePath) : QObject(parent){
    filePath = _filePath;
}

void FileLoader::DoSetup(QThread &cThread)
{
    connect(&cThread,SIGNAL(started()),this,SLOT(DoWork()));
}

void FileLoader::DoWork(){
    QMutex mutex;
    mutex.lock();
    qDebug() <<"im doing work!!! " ;
    if(!filePath.isEmpty()){
        QFile file(filePath);
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            emit errorOpeningFile();
            qDebug() <<"error" ;
        }else{
            emit fileLoading();
            //this->msleep(5000);
            qDebug() <<"before open" ;
            QTextStream input(&file);
            qDebug() <<"reading" ;
            QString text = input.readAll();
            qDebug() <<"after open" ;
            qDebug() <<"the text: " << text ;
            emit fileUploaded(text);

        }
        file.close();
    }
    mutex.unlock();

}

