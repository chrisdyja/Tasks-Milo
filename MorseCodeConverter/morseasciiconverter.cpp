#include "morseasciiconverter.h"

#include <QtCore>

MorseAsciiConverter::MorseAsciiConverter(QObject *parent, bool _convertToMorse) : QObject(parent){
    convertToMorse = _convertToMorse;

    /*! @brief Alphabet */
    asciiMorseMap.insert("A",".-");
    asciiMorseMap.insert("B","-...");
    asciiMorseMap.insert("C","-.-.");
    asciiMorseMap.insert("D","-..");
    asciiMorseMap.insert("E",".");
    asciiMorseMap.insert("F","..-.");
    asciiMorseMap.insert("G","--.");
    asciiMorseMap.insert("H","....");
    asciiMorseMap.insert("I","..");
    asciiMorseMap.insert("J",".---");
    asciiMorseMap.insert("K","-.-");
    asciiMorseMap.insert("L",".-..");
    asciiMorseMap.insert("M","--");
    asciiMorseMap.insert("N","-.");
    asciiMorseMap.insert("O","---");
    asciiMorseMap.insert("P",".--.");
    asciiMorseMap.insert("Q","--.-");
    asciiMorseMap.insert("R",".-.");
    asciiMorseMap.insert("S","...");
    asciiMorseMap.insert("T","-");
    asciiMorseMap.insert("U","..-");
    asciiMorseMap.insert("V","...-");
    asciiMorseMap.insert("W",".--");
    asciiMorseMap.insert("X","-..-");
    asciiMorseMap.insert("Y","-.--");
    asciiMorseMap.insert("Z","--..");

    /*! @brief Numbers */
    asciiMorseMap.insert("1",".----");
    asciiMorseMap.insert("2","..---");
    asciiMorseMap.insert("3","...--");
    asciiMorseMap.insert("4","....-");
    asciiMorseMap.insert("5",".....");
    asciiMorseMap.insert("6","-....");
    asciiMorseMap.insert("7","--...");
    asciiMorseMap.insert("8","---..");
    asciiMorseMap.insert("9","----.");
    asciiMorseMap.insert("0","-----");

    /*! @brief Special Characters */
    asciiMorseMap.insert(",","--..--");
    asciiMorseMap.insert("/","-..-.");
    asciiMorseMap.insert(".",".-.-.-");
    asciiMorseMap.insert(";","-.-.-.");
    asciiMorseMap.insert(":","---...");
    asciiMorseMap.insert("(","-.--.");
    asciiMorseMap.insert(")","-.--.-");
    asciiMorseMap.insert("@",".--.-.");
    asciiMorseMap.insert("=","···-··");
    asciiMorseMap.insert("'",".----.");
    asciiMorseMap.insert("+",".-.-.");
    asciiMorseMap.insert("-","-....-");
    asciiMorseMap.insert("_","..--.-");
    asciiMorseMap.insert("?","..--..");
}


void MorseAsciiConverter::DoSetup(QThread &cThread){
    connect(&cThread,SIGNAL(started()),this,SLOT(DoWork()));
}

void MorseAsciiConverter::DoWork(){
    QMutex mutex;
    mutex.lock();
        if(convertToMorse){
            textToMorse(input);
        }else{
            morseToText(input);
        }
    mutex.unlock();
}

void MorseAsciiConverter::textToMorse(QString asciiText){
    QString output = "";
    char asciiTextChars[asciiText.size()];
    int asciiTextCharsLength = (*(&asciiTextChars + 1) - asciiTextChars);
    memcpy(asciiTextChars, asciiText.toStdString().c_str(), asciiText.size());

    for(int letterIndex = 0; letterIndex < asciiTextCharsLength; letterIndex++){
        if(((QChar::fromLatin1(asciiTextChars[letterIndex])).toUpper() == ' ')){
            output.append(" ");
        }else{
            output.append(asciiMorseMap.value((QChar::fromLatin1(asciiTextChars[letterIndex])).toUpper()));
            if(letterIndex < (asciiTextCharsLength-1)){     ///<if haven't reached end of array
                output.append(" ");
            }
        }
    }
    emit conversionComplete(output);
}

void MorseAsciiConverter::morseToText(QString morseCode){
    QString output = "";
    QString asciiCharAsMorse = "";
    char morseChars[morseCode.size()];
    int morseCharsLength = (*(&morseChars + 1) - morseChars);
    memcpy(morseChars, morseCode.toStdString().c_str(), morseCode.size());

    for(int morseCharIndex = 0; morseCharIndex < morseCharsLength; morseCharIndex++){
        if(morseChars[morseCharIndex] != ' '){
            asciiCharAsMorse.append(morseChars[morseCharIndex]);
            if(morseCharIndex >= (morseCharsLength - 1)){
                 output.append(asciiMorseMap.key(asciiCharAsMorse));
            }
        }else{
            output.append(asciiMorseMap.key(asciiCharAsMorse));
            asciiCharAsMorse = "";
            if(morseCharIndex < (morseCharsLength - 1)){
                if(morseChars[morseCharIndex+1] == ' '){    ///<if found space between words
                    output.append(" ");
                    asciiCharAsMorse = "";
                    morseCharIndex++;
                }
            }
        }
    }
    emit conversionComplete(output);
}
