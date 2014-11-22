#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QFile>

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

int correlation(const QVector<bool> &source1, const QVector<bool> &source2)
{
    int tempI = 0;
    int summa = 0;

    for(int i = 0; i < source1.size() + source2.size() - 1; ++i) {
        for(int j = 0; j < source2.size(); ++j) {
            if(i < source1.size()) {
                tempI = i;
            } else {
                tempI = source1.size() - 1;
            }

            summa += fromBoolToInt(source1.at(tempI))*fromBoolToInt(source2.at(source2.size() - 1 - j));
            --tempI;

            if(tempI < 0 || (source2.size() - 1 - j < 0)) {
                break;
            }
        }
    }

    return summa;
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

bool mSequenceReader(const QString &fileName, QVector<bool> &vec, const int &lineNumber = 1)
{
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray ba;

    for(int i = 0; i < lineNumber; ++i) {
        if(!file.atEnd()) {
            ba = file.readLine();
        } else {
            file.close();

            return false;
        }
    }

    file.close();

    for(int i = 0; i < ba.size(); ++i) {
        if(ba.at(i) != '\n') {
            vec.push_back(fromIntToBool(ba.at(i) - '0'));
        }
    }

    return true;
}

void ACFSmax()
{
    qDebug() << "==========START_TEST==========";

    QVector<bool> vec;
    int line = 1;

    while(mSequenceReader("MSequence.txt", vec, line++)) {
        if(!vec.isEmpty()) {
            qDebug() << "===========SUB_TEST===========";
            print(vec);
            QVector<int> acfs_phases;
            for(int i = 1; i < vec.size(); ++i) {
                acfs_phases.push_back(ACFphase(vec, i));
                qDebug() << "ACF(" << i << ") =" << acfs_phases.at(i - 1);
            }
            qDebug() << "MAX ACF(phase) =" << ACFmax(acfs_phases);
            vec.clear();
        } else {
            qDebug() << "******************************";
        }
    }

    qDebug() << "===========END_TEST===========";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ACFSmax();

    return a.exec();
}
