#ifndef DERIVCHAINFINDER_H
#define DERIVCHAINFINDER_H

#include <QThread>

class DerivChainFinder : public QObject
{
    Q_OBJECT
public:
    DerivChainFinder(QObject *parent = 0, QStringList _list = QStringList(), QString _currentWord = "");

    QStringList alphabet;
    QStringList dictionary, sortedDictionary;
    QString currentWord, derivChainOutput;

    void DoSetup(QThread  &cThread);

private:
    QStringList sortList(QStringList list, bool sortLettersInEachItem);

signals:
    void searchComplete(QString output);

public slots:
    void DoWork();

};

#endif // DERIVCHAINFINDER_H
