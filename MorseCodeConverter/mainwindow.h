#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "morseasciiconverter.h"
#include "fileloader.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    FileLoader *fileLoader;
    QThread cThread, cThread2;
    MorseAsciiConverter *morseAscii;
    QString filePath;

private slots:
    void on_pushButtonOpenFile_clicked();

    void on_pushButtonConvert_clicked();

    void on_pushButtonSelectPath_clicked();

    void on_pushButtonExport_clicked();

    void on_lineEditExportFileName_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

public slots:
    void onErrorOpeningFile();
    void onFileLoading();
    void onFileUploaded(QString);
    void onConversionComplete(QString);
};
#endif // MAINWINDOW_H
