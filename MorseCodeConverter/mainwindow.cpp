#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->radioButtonTextToMorse->setChecked(true);
    filePath = QDir::homePath();
    ui->labelExportPath->setText(filePath+"/");
    morseAscii = new MorseAsciiConverter();
    fileLoader = new FileLoader(0,filePath);
}

MainWindow::~MainWindow(){
    fileLoaderThread.terminate();
    converterThread.terminate();
    delete ui;
}


void MainWindow::on_pushButtonOpenFile_clicked(){
    QString filePath_ = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    fileLoader->filePath = filePath_;
    fileLoader->DoSetup(fileLoaderThread);
    connect(fileLoader,SIGNAL(errorOpeningFile()), this, SLOT(onErrorOpeningFile()));
    connect(fileLoader,SIGNAL(fileLoading()), this, SLOT(onFileLoading()));
    connect(fileLoader,SIGNAL(fileUploaded(QString)), this, SLOT(onFileUploaded(QString)));
    fileLoader->moveToThread(&fileLoaderThread);
    fileLoaderThread.start();
}

void MainWindow::on_pushButtonConvert_clicked(){
    QString textToConvert = ui->plainTextEditInput->toPlainText();
    morseAscii->input = textToConvert;
    if(ui->radioButtonMorseToText->isChecked()){
        morseAscii->convertToMorse = false;
        morseAscii->DoSetup(converterThread);
        connect(morseAscii,SIGNAL(conversionComplete(QString)), this, SLOT(onConversionComplete(QString)));
        morseAscii->moveToThread(&converterThread);
        converterThread.start();

         //ui->textBrowserOutput->setText(morseAscii->morseToAscii(textToConvert));
    }else{
        morseAscii->convertToMorse = true;
        morseAscii->DoSetup(converterThread);
        connect(morseAscii,SIGNAL(conversionComplete(QString)), this, SLOT(onConversionComplete(QString)));
        morseAscii->moveToThread(&converterThread);
        converterThread.start();
         //ui->textBrowserOutput->setText(morseAscii->asciiToMorse(textToConvert));
    }
}

void MainWindow::on_pushButtonSelectPath_clicked(){
    filePath = QFileDialog::getExistingDirectory(this, "Choose directory", QDir::homePath(),QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //filePath +=  "/" + ui->lineEditExportFileName->text() + ".txt";
    ui->labelExportPath->setText(filePath+ "/" + ui->lineEditExportFileName->text() + ".txt");
}

void MainWindow::on_pushButtonExport_clicked(){
    QRegularExpression re("[A-Za-z0-9_-]*\\.*[A-Za-z0-9]{3,4}");

    if(re.match(ui->lineEditExportFileName->text()).hasMatch()){
    qDebug()<<"has match";
        if(QFileInfo::exists(filePath + "/"  +ui->lineEditExportFileName->text() + ".txt")){
            qDebug()<<"exists";
            QMessageBox msgBox;
            msgBox.setText("File with this name already exists.");
            msgBox.setInformativeText("Do you want to overwrite it?");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            int ret = msgBox.exec();
            if(ret == QMessageBox::Ok){
                qDebug()<<"exportuje";
                QFile file(filePath + "/" + ui->lineEditExportFileName->text() + ".txt");
                if(!file.open(QFile::WriteOnly | QFile::Text)){
                    QMessageBox::warning(this,"Error","Failed to open file.");
                }
                QTextStream output(&file);
                QString text = ui->textBrowserOutput->toPlainText();
                output << text;
                file.flush();
                file.close();
            }
        }else{
            QFile file(filePath + "/" + ui->lineEditExportFileName->text() + ".txt");
            if(!file.open(QFile::WriteOnly | QFile::Text)){
                QMessageBox::warning(this,"Error","Failed to open file.");
            }
            QTextStream output(&file);
            QString text = ui->textBrowserOutput->toPlainText();
            output << text;
            file.flush();
            file.close();
        }
    }else{
        QMessageBox::warning(this,"Warning!","Invalid characters in file name!");
    }
}

void MainWindow::on_lineEditExportFileName_textChanged(const QString &arg1){
    ui->labelExportPath->setText(filePath+ "/" + arg1 + ".txt");
}

void MainWindow::onErrorOpeningFile(){
    QMessageBox::warning(this,"Error","Failed to open file.");
}

void MainWindow::onFileUploaded(QString text){
    ui->labelFileOpenStatus->setText("");
    ui->plainTextEditInput->setPlainText(text);
    fileLoaderThread.terminate();
}
void MainWindow::onFileLoading(){
    ui->labelFileOpenStatus->setText("Loading...");
}

void MainWindow::onConversionComplete(QString output){
    ui->textBrowserOutput->setText(output);
    converterThread.terminate();
}
