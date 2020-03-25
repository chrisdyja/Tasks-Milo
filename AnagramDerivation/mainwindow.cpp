#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->pushButtonStartSearch->setEnabled(false);
    derivChainOutput = "";
    dictionaryFilePath = "";
    isDictionaryFilePathSet = false;
    derivChainFinder = new DerivChainFinder();
    derivChainFinder->currentWord = "";
}

MainWindow::~MainWindow(){
    derivChainSearchThread.terminate();
    delete ui;
}

void MainWindow::on_pushButtonSelectDictionaryPath_clicked(){
    dictionaryFilePath = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    QFile file(dictionaryFilePath);

     if(QFileInfo::exists(dictionaryFilePath)){
         if(!file.open(QFile::ReadOnly | QFile::Text)){
             QMessageBox::warning(this,"title","File not open");
         }
         QTextStream in(&file);
         while (!in.atEnd()){
             QString line = in.readLine();
             selectedDictionary.append(line);
         }
         file.close();

         ui->labelDictinaryPath->setText(dictionaryFilePath);
         isDictionaryFilePathSet = true;
     }
     checkIfAllowedToSearch();
}

void MainWindow::on_pushButtonStartSearch_clicked(){
    ui->textBrowserDerivationChain->setText("");
    derivChainFinder->derivChainOutput = "";
    derivChainFinder->currentWord = currentWord;
    derivChainFinder->dictionary = selectedDictionary;
    derivChainFinder->DoSetup(derivChainSearchThread);
    connect(derivChainFinder,SIGNAL(searchComplete(QString)), this, SLOT(onSearchComplete(QString)));
    derivChainFinder->moveToThread(&derivChainSearchThread);
    derivChainSearchThread.start();
    ui->pushButtonStartSearch->setDisabled(true);
}

void MainWindow::on_lineEditUserWord_textChanged(const QString &arg1){
    if(arg1.length() == 3){
        userWordValid = true;
        currentWord = arg1;
    }else{
        userWordValid = false;
        derivChainFinder->currentWord = "";
    }
    checkIfAllowedToSearch();
}

void MainWindow::onSearchComplete(QString output){
    ui->textBrowserDerivationChain->setText(output);
    derivChainSearchThread.terminate();
    ui->pushButtonStartSearch->setDisabled(false);
}

void MainWindow::checkIfAllowedToSearch(){
    if(userWordValid && isDictionaryFilePathSet){
        ui->pushButtonStartSearch->setEnabled(true);
    }else{
        ui->pushButtonStartSearch->setEnabled(false);
    }
}




