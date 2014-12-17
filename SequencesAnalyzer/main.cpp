#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QFile>
//#include <iostream>

#define UPPER_LIMIT "111111000"
#define LOWER_LIMIT "000001111"

void print(const QVector<bool> &result)
{
    QString tempStr;

    for(int i = 0; i < result.size(); ++i) {
        if(result.at(i)) {
            tempStr.append("1");
        } else {
            tempStr.append("0");
        }
    }

    qDebug() << tempStr;
}

void printToFile(QFile &file, const QVector<bool> &result)
{   
    file.close();

//    std::cin.get();
    if(!file.open(QIODevice::Append | QIODevice::Text)) {
        qErrnoWarning(QString(QString("void printToFile(): ERROR!\nCan't create file: ") +
                              QString("\"") +
                              file.fileName() +
                              QString("\"")).toStdString().c_str());
    }

    QTextStream out(&file);

    for(int i = 0; i < result.size(); ++i) {
        if(result.at(i)) {
            out << "1";
        } else {
            out << "0";
        }
    }

    out << "\n";
}

void printToFile(QFile &file, const QVector<QVector<bool> > &results)
{
    file.close();

    if(!file.open(QIODevice::Append | QIODevice::Text)) {
        qErrnoWarning(QString(QString("void printToFile(): ERROR!\nCan't create file: ") +
                              QString("\"") +
                              file.fileName() +
                              QString("\"")).toStdString().c_str());
    }

    QTextStream out(&file);

    for(int i = 0; i < results.size(); ++i) {
        for(int j = 0; j < results.at(i).size(); ++j) {
            if(results.at(i).at(j)) {
                out << "1";
            } else {
                out << "0";
            }
        }

        out << "\n";
    }
}

void print(const QVector<QVector<bool> > &results)
{
    QString tempStr;

    for(int i = 0; i < results.size(); ++i) {
        for(int j = 0; j < results.at(i).size(); ++j) {
            if(results.at(i).at(j)) {
                tempStr.append("1");
            } else {
                tempStr.append("0");
            }
        }

        qDebug() << tempStr;
        tempStr.clear();
    }
}

bool isValid(const QVector<bool>  &result)
{
    bool temp;
    int zeros = 0;
    int units = 0;

    for(int i = 0; i < result.size(); ++i) {
        temp = result.value(i);

        if(temp) {
            ++units;
        } else {
            ++zeros;
        }
    }

    if(result.size() % 2) {
        if((zeros + 1 == units) || (zeros == units + 1)) {
            return true;
        } else {
            return false;
        }
    } else {
        if(zeros == units) {
            return true;
        } else {
            return false;
        }
    }
}

bool isEqual(const QVector<bool> &source1, const QString &source2) {
    if(source1.size() != source2.size()) {
        qDebug() << "don't match";
        return false;
    }

    QString tempStr = "0";

    qDebug() << "source1:";
    print(source1);
    qDebug() << "source2:";
    qDebug() << source2;

    bool stringSymbol = false;

    for(int i = 0; i < source1.size(); ++i) {
        if(source2.at(i) == tempStr.at(0)) {
            stringSymbol = false;
        } else {
            stringSymbol = true;
        }

        if(source1.at(i) != stringSymbol) {
            return false;
        }
    }

    qDebug() << "TRUE!!!";

    return true;
}

void counter(QVector<QVector<bool> > &results, const int &digits)
{
    QVector<bool> tempResult;

    tempResult.fill(false, digits);

//    bool isWasLowerLimit = false;
    int k = 0;

    while(true) {
        qDebug() << "digits =" << digits;
        for(int i = 0; i < tempResult.size(); ++i) {
            if(tempResult.at(i)) {
                ++k;
            }
        }

        if(k == tempResult.size()) {
            break;
        }

        k = 0;

        for(int m = 1; m < tempResult.size(); ++m) {
            for(int i = m; i < tempResult.size(); ++i) {
                if(tempResult.at(i)) {
                    ++k;
                }
            }

            if(k == tempResult.size() - m) {
                for(int i = m; i < tempResult.size(); ++i) {
                    tempResult.replace(i, false);
                }

                tempResult.replace(m - 1, true);
            }

            k = 0;
        }

        if(/*isWasLowerLimit && */isValid(tempResult)) {
            results.push_back(tempResult);
            print(tempResult);
        }
//        results.push_back(tempResult);
//        print(tempResult);
        tempResult.replace(tempResult.size() - 1, true);
//        results.push_back(tempResult);
//        print(tempResult);

//        if(isEqual(tempResult, LOWER_LIMIT)) {
//            isWasLowerLimit = true;
//            qDebug() << "isWasLowerLimit" << isWasLowerLimit;
//        }

//        if(isEqual(tempResult, UPPER_LIMIT)) {
//            qDebug() << "isWasUpperLimit";
//            return;
//        }

//        if(isWasLowerLimit && isValid(tempResult)) {
//            results.push_back(tempResult);
//        }

//        if(isEqual(tempResult, LOWER_LIMIT)) {
//            isWasLowerLimit = true;
//            qDebug() << "isWasLowerLimit" << isWasLowerLimit;
//        }

//        if(isEqual(tempResult, UPPER_LIMIT)) {
//            qDebug() << "isWasUpperLimit";
//            return;
//        }

        if(/*isWasLowerLimit && */isValid(tempResult)) {
            results.push_back(tempResult);
            print(tempResult);
        }
    }
}

void fromBinToHex(const QVector<QVector<bool> > &results)
{
    QString tempStr;
    QString tempStrHex;
    QString strHex;

    for(int i = 0; i < results.size(); ++i) {
        for(int j = 0; j < results.at(i).size(); ++j) {
            if(results.at(i).at(j)) {
                tempStr.append("1");
            } else {
                tempStr.append("0");
            }
        }

        for(int j = 1; j < tempStr.size(); ++j) {
            tempStrHex += tempStr.at(j);
            if(!(j % 4)) {
                if(tempStrHex == "0000") {
                    strHex += "0";
                }
                if(tempStrHex == "0001") {
                    strHex += "1";
                }
                if(tempStrHex == "0010") {
                    strHex += "2";
                }
                if(tempStrHex == "0011") {
                    strHex += "3";
                }
                if(tempStrHex == "0100") {
                    strHex += "4";
                }
                if(tempStrHex == "0101") {
                    strHex += "5";
                }
                if(tempStrHex == "0110") {
                    strHex += "6";
                }
                if(tempStrHex == "0111") {
                    strHex += "7";
                }
                if(tempStrHex == "1000") {
                    strHex += "8";
                }
                if(tempStrHex == "1001") {
                    strHex += "9";
                }
                if(tempStrHex == "1010") {
                    strHex += "A";
                }
                if(tempStrHex == "1011") {
                    strHex += "B";
                }
                if(tempStrHex == "1100") {
                    strHex += "C";
                }
                if(tempStrHex == "1101") {
                    strHex += "D";
                }
                if(tempStrHex == "1110") {
                    strHex += "E";
                }
                if(tempStrHex == "1111") {
                    strHex += "F";
                }
                tempStrHex.clear();
            }
        }
        strHex.push_front(tempStr.at(0));

        qDebug() << tempStr << strHex;
        tempStr.clear();
        strHex.clear();
    }
}

int fromBoolToInt(const bool &boolValue)
{
    if(boolValue) {
        return 1;
    } else {
        return -1;
    }
}

bool fromIntToBool(const int &intValue)
{
    return intValue ? true : false;
}

QVector<bool> subSequence(const QVector<bool> &source, const int &offset, const int &digits)
{
    if(offset + digits > source.size()) {
        qDebug() << "exception";
    }

    QVector<bool> result;

    for(int i = offset; i < offset + digits; ++i) {
        result.append(source.at(i));
    }

    return result;
}

int ACFphase(const QVector<bool> &source, const int &phase)
{
    int result = 0;

    for(int i = 0; i < source.size(); ++i) {
        if(i >= phase) {
            result += fromBoolToInt(source.at(i))*fromBoolToInt(source.at(i - phase));
        }
    }

    return result;
}

// #2
int ACFmax(const QVector<int> &acfs_phases)
{
    int result = 0;

    for(int i = 0; i < acfs_phases.size(); ++i) {
        if(qAbs(result) < qAbs(acfs_phases.at(i))) {
            result = acfs_phases.at(i);
        }
    }

    return result;
}

// #3
int ACFmin_max(const QVector<int> &acfs_maxs)
{
    int result = 0;

    for(int i = 0; i < acfs_maxs.size(); ++i) {
        if(qAbs(result) > qAbs(acfs_maxs.at(i))) {
            result += acfs_maxs.at(i);
        }
    }

    return result;
}

bool mSequenceReaderHEX(const QByteArray &ba, QVector<bool> &vec)
{
    for(int i = 0; i < ba.size(); ++i) {
        if(ba.at(i) != '\n' && ((ba.at(i) >= '0' && ba.at(i) <= '9') || (ba.at(i) >= 'A' && ba.at(i) <= 'F'))) {
            switch(ba.at(i)) {
            case '0':
                vec.push_back(false);
                vec.push_back(false);
                vec.push_back(false);
                vec.push_back(false);
                break;
            case '1':
                vec.push_back(false);
                vec.push_back(false);
                vec.push_back(false);
                vec.push_back(true);
                break;
            case '2':
                vec.push_back(false);
                vec.push_back(false);
                vec.push_back(true);
                vec.push_back(false);
                break;
            case '3':
                vec.push_back(false);
                vec.push_back(false);
                vec.push_back(true);
                vec.push_back(true);
                break;
            case '4':
                vec.push_back(false);
                vec.push_back(true);
                vec.push_back(false);
                vec.push_back(false);
                break;
            case '5':
                vec.push_back(false);
                vec.push_back(true);
                vec.push_back(false);
                vec.push_back(true);
                break;
            case '6':
                vec.push_back(false);
                vec.push_back(true);
                vec.push_back(true);
                vec.push_back(false);
                break;
            case '7':
                vec.push_back(false);
                vec.push_back(true);
                vec.push_back(true);
                vec.push_back(true);
                break;
            case '8':
                vec.push_back(true);
                vec.push_back(false);
                vec.push_back(false);
                vec.push_back(false);
                break;
            case '9':
                vec.push_back(true);
                vec.push_back(false);
                vec.push_back(false);
                vec.push_back(true);
                break;
            case 'A':
                vec.push_back(true);
                vec.push_back(false);
                vec.push_back(true);
                vec.push_back(false);
                break;
            case 'B':
                vec.push_back(true);
                vec.push_back(false);
                vec.push_back(true);
                vec.push_back(true);
                break;
            case 'C':
                vec.push_back(true);
                vec.push_back(true);
                vec.push_back(false);
                vec.push_back(false);
                break;
            case 'D':
                vec.push_back(true);
                vec.push_back(true);
                vec.push_back(false);
                vec.push_back(true);
                break;
            case 'E':
                vec.push_back(true);
                vec.push_back(true);
                vec.push_back(true);
                vec.push_back(false);
                break;
            case 'F':
                vec.push_back(true);
                vec.push_back(true);
                vec.push_back(true);
                vec.push_back(true);
                break;
            default:
                qDebug() << "Error! Not HEX format!";
                return false;
            }
        } else {
            qDebug() << "Error! Not HEX format!";
            return false;
        }
    }

    return true;
}

bool mSequenceReaderBIN(const QByteArray &ba, QVector<bool> &vec)
{    
    for(int i = 0; i < ba.size(); ++i) {
        if(ba.at(i) != '\n' && (ba.at(i) == '0' || ba.at(i) == '1')) {
            vec.push_back(fromIntToBool(ba.at(i) - '0'));
        } else {
            qDebug() << "Error! Not BIN format!";
            return false;
        }
    }

    return true;
}

bool mSequenceReader(QFile &file, QVector<bool> &vec, int &pos)
{    
    QByteArray ba;

    if(!file.atEnd()) {
        file.seek(pos);
        ba = file.readLine();
        pos = file.pos();
    } else {
        return false;
    }

    // Without empty line at the end of file
    if(ba.at(ba.size() - 1) == '\n') {
        ba.truncate(ba.size() - 1);
    }

    if(ba.contains("BIN ")) {
        ba.remove(0, 4);        
        mSequenceReaderBIN(ba, vec);
    } else if(ba.contains("HEX ")) {
        ba.remove(0, 4);        
        mSequenceReaderHEX(ba, vec);
    } else {        
        qDebug() << "Error! File formating no valid!";
        qDebug() << "For HEX-format sequence write in file at the begin line: HEX";
        qDebug() << "For BIN-format sequence write in file at the begin line: BIN";

        return false;
    }

    return true;
}

void ACFSmax()
{
    QFile resultsOutputFile("ACFOutput.txt");
    if(!resultsOutputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qErrnoWarning("ERROR!\nCan't create file: \"ACFOutput.txt\"");
    }

    QTextStream out(&resultsOutputFile);

    qDebug() << "==========START_TEST==========";
    out << "==========START_TEST==========\n";

    QVector<bool> vec;
    int pos = 0;
    QFile file("MSequences.txt");
    bool isWasSpace = false;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qErrnoWarning("ERROR!\nCan't open file: \"MSequences.txt\"");
    }

    while(mSequenceReader(file, vec, pos)) {
        if(!vec.isEmpty()) {
            isWasSpace = false;

            qDebug() << "===========SUB_TEST===========";
            out << "===========SUB_TEST===========\n";

            print(vec);
            printToFile(resultsOutputFile, vec);

            qDebug() << "Size of sequence:" << vec.size();
            out << "Size of sequence: " << vec.size() << "\n";

            QVector<int> acfs_phases;

            for(int i = 1; i < vec.size(); ++i) {
                acfs_phases.push_back(ACFphase(vec, i));

                qDebug() << "ACF(" << i << ") =" << acfs_phases.at(i - 1);
                out << "ACF(" << i << ") = " << acfs_phases.at(i - 1) << "\n";
            }

            qDebug() << "MAX ACF(phase) = " << ACFmax(acfs_phases);
            out << "MAX ACF(phase) = " << ACFmax(acfs_phases) << "\n";

            vec.clear();
        } else {
            if(!isWasSpace) {
                isWasSpace = true;

                qDebug() << "*******NEXT_GROUP_TESTS*******";
                out << "*******NEXT_GROUP_TESTS*******\n";
            }
        }
    }

    qDebug() << "===========END_TEST===========";
    out << "===========END_TEST===========\n";

    file.close();
    resultsOutputFile.close();
}

int CCFphase(const QVector<bool> &origin, const QVector<bool> &part, const int &phase)
{
    int result = 0;
    for(int i = 0; i < origin.size() - phase; ++i) {
        result += fromBoolToInt(origin.at(i))*fromBoolToInt(part.at(i));
    }

    return result;
}

int CCFmax(const QVector<int> &ccfs_phases)
{
    return ACFmax(ccfs_phases);
}

void CCFSmax(const int &offset, const int &lenght)
{
    QFile resultsOutputFile("CCFOutput.txt");
    if(!resultsOutputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qErrnoWarning("ERROR!\nCan't create file: \"CCFOutput.txt\"");
    }

    QTextStream out(&resultsOutputFile);

    qDebug() << "==========START_TEST==========";
    out << "==========START_TEST==========\n";

    QVector<bool> vec;
    int pos = 0;
    QFile file("MSequences.txt");
    bool isWasSpace = false;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qErrnoWarning("ERROR!\nCan't open file: \"MSequences.txt\"");
    }

    while(mSequenceReader(file, vec, pos)) {
        if(!vec.isEmpty()) {
            isWasSpace = false;

            qDebug() << "===========SUB_TEST===========";
            out << "===========SUB_TEST===========\n";

            print(vec);

            qDebug() << "Size of sequence:" << vec.size();
            out << "Size of sequence: " << vec.size() << "\n";

            QVector<int> ccfs_phases;

            for(int i = 1; i < vec.size(); ++i) {
                ccfs_phases.push_back(CCFphase(vec, subSequence(vec, 0, 6), i));

                qDebug() << "ACF(" << i << ") =" << ccfs_phases.at(i - 1);
                out << "ACF(" << i << ") = " << ccfs_phases.at(i - 1) << "\n";
            }

            qDebug() << "MAX CCF(phase) = " << CCFmax(ccfs_phases);
            out << "MAX CCF(phase) = " << CCFmax(ccfs_phases) << "\n";

            vec.clear();
        } else {
            if(!isWasSpace) {
                isWasSpace = true;

                qDebug() << "*******NEXT_GROUP_TESTS*******";
                out << "*******NEXT_GROUP_TESTS*******\n";
            }
        }
    }

    qDebug() << "===========END_TEST===========";
    out << "===========END_TEST===========\n";

    file.close();
    resultsOutputFile.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ACFSmax();

//    CCFSmax();

    return a.exec();
}
