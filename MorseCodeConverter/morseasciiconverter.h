#ifndef MORSEASCII_H
#define MORSEASCII_H

#include <QMap>
#include <QThread>

class MorseAsciiConverter : public QObject{
    Q_OBJECT
public:
    /*!
    * @brief class representing Morse Code converter
    *
    * @param *parent
    * @param _convertToMorse flag indicating the direction of conversion-text to Morse Code or Morse Code to text
    */
    explicit MorseAsciiConverter(QObject *parent = 0, bool _convertToMorse = true);

    /*!
    * @brief Sets up slots for thread
    *
    * @param &cThread
    */
    void DoSetup(QThread  &cThread);

    /*!
    * @brief Converts text to Morse Code
    *
    * @param asciiText human readable text to convert
    * @retval morse code
    */
    void textToMorse(QString asciiText);

    /*!
    * @brief Converts Morse Code to human readable text
    *
    * @param morseCode morse code to convert
    * @retval ascii characters text
    */
    void morseToText(QString morseCode);

    /*! @brief  Ascii Characters - Morse Code map*/
    QMap<QString,QString> asciiMorseMap;
    QString input;
    bool convertToMorse;

signals:
    void conversionComplete(QString output);

public slots:
    void DoWork();
};

#endif // MORSEASCII_H
