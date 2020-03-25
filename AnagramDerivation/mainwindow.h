#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "derivchainfinder.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStringList selectedDictionary;
    QString dictionaryFilePath;
    QString currentWord;
    QString derivChainOutput;
    QThread derivChainSearchThread;
    bool isDictionaryFilePathSet;
    bool userWordValid;
    DerivChainFinder *derivChainFinder;

    void checkIfAllowedToSearch();


private slots:
    void on_pushButtonSelectDictionaryPath_clicked();

    void on_pushButtonStartSearch_clicked();

    void on_lineEditUserWord_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

public slots:
    void onSearchComplete(QString);
};
#endif // MAINWINDOW_H
