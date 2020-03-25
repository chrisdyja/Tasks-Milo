#include "derivchainfinder.h"

#include <QtCore>

DerivChainFinder::DerivChainFinder(QObject *parent, QStringList _dictionary, QString _currentWord){
    alphabet.append("a");
    alphabet.append("b");
    alphabet.append("c");
    alphabet.append("d");
    alphabet.append("e");
    alphabet.append("f");
    alphabet.append("g");
    alphabet.append("h");
    alphabet.append("i");
    alphabet.append("j");
    alphabet.append("k");
    alphabet.append("l");
    alphabet.append("m");
    alphabet.append("n");
    alphabet.append("o");
    alphabet.append("p");
    alphabet.append("q");
    alphabet.append("r");
    alphabet.append("s");
    alphabet.append("t");
    alphabet.append("u");
    alphabet.append("v");
    alphabet.append("w");
    alphabet.append("x");
    alphabet.append("y");
    alphabet.append("z");

    dictionary = _dictionary;
    currentWord = _currentWord;
}

void DerivChainFinder::DoSetup(QThread &derivChainSearchThread){
    connect(&derivChainSearchThread,SIGNAL(started()),this,SLOT(DoWork()));
}

void DerivChainFinder::DoWork(){
    QMutex mutex;
    mutex.lock();

    dictionary = sortList(dictionary,false);
    sortedDictionary = sortList(dictionary,true);

    for(int i=0; i<dictionary.length(); i++){
        if((currentWord.length()+1) == sortedDictionary[i].length()){
            for(int j=0; j<alphabet.length(); j++){
                QString tmp = (currentWord + alphabet[j]);
                std::sort(tmp.begin(), tmp.end());
                if(tmp == sortedDictionary[i]){
                    currentWord = tmp;
                    derivChainOutput.append(dictionary[i] + "->");
                }
            }
        }
    }
    emit searchComplete(derivChainOutput);
    mutex.unlock();
}

QStringList DerivChainFinder::sortList(QStringList list, bool sortLettersInEachItem){
    for (int i=1 ;i<list.length(); i++){
        if(sortLettersInEachItem){
            std::sort(list[i].begin(), list[i].end());
        }
        QString temp = list[i];
        int j = i - 1;
        while (j >= 0 && temp.length() < list[j].length()){
            list[j+1] = list[j];
            j--;
        }
        list[j+1] = temp;
    }
    return list;
}
