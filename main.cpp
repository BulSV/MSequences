#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QThread>

#define UPPER_LIMIT "111111000"
#define LOWER_LIMIT "000001111"

void print(const QVector<bool> &result)
{
    QString tempStr;

    for(int i = 0; i < 9; ++i) {
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
        for(int j = 0; j < 9; ++j) {
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

    if((zeros + 1 == units) || (zeros == units + 1)) {
        return true;
    } else {
        return false;
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

void counter(QVector<QVector<bool> > &results)
{
    QVector<bool> tempResult;

    tempResult.fill(false, 9);

//    bool isWasLowerLimit = false;
    int k = 0;

    while(true) {
        for(int i = 0; i < tempResult.size(); ++i) {
            if(tempResult.at(i)) {
                ++k;
            }
        }

        qDebug() << "K =" << k;

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

        results.push_back(tempResult);
        print(tempResult);
        tempResult.replace(tempResult.size() - 1, true);
        results.push_back(tempResult);
        print(tempResult);
//        QThread::usleep(500000);


//            results.push_back(tempResult);

//        if(tempResult.at(0) && tempResult.at(1) && tempResult.at(2) && tempResult.at(3)
//                && tempResult.at(4) && tempResult.at(5) && tempResult.at(6) && tempResult.at(7)
//                && tempResult.at(8)) {
//            break;
//        }
//        if(tempResult.at(1) && tempResult.at(2) && tempResult.at(3) && tempResult.at(4)
//                && tempResult.at(5) && tempResult.at(6) && tempResult.at(7) && tempResult.at(8)) {
//            tempResult.replace(8, false);
//            tempResult.replace(7, false);
//            tempResult.replace(6, false);
//            tempResult.replace(5, false);
//            tempResult.replace(4, false);
//            tempResult.replace(3, false);
//            tempResult.replace(2, false);
//            tempResult.replace(1, false);
//            tempResult.replace(0, true);
//        }
//        if(tempResult.at(2) && tempResult.at(3) && tempResult.at(4) && tempResult.at(5)
//                && tempResult.at(6) && tempResult.at(7) && tempResult.at(8)) {
//            tempResult.replace(8, false);
//            tempResult.replace(7, false);
//            tempResult.replace(6, false);
//            tempResult.replace(5, false);
//            tempResult.replace(4, false);
//            tempResult.replace(3, false);
//            tempResult.replace(2, false);
//            tempResult.replace(1, true);
//        }
//        if(tempResult.at(3) && tempResult.at(4) && tempResult.at(5) && tempResult.at(6)
//                && tempResult.at(7) && tempResult.at(8)) {
//            tempResult.replace(8, false);
//            tempResult.replace(7, false);
//            tempResult.replace(6, false);
//            tempResult.replace(5, false);
//            tempResult.replace(4, false);
//            tempResult.replace(3, false);
//            tempResult.replace(2, true);
//        }
//        if(tempResult.at(4) && tempResult.at(5) && tempResult.at(6) && tempResult.at(7)
//                && tempResult.at(8)) {
//            tempResult.replace(8, false);
//            tempResult.replace(7, false);
//            tempResult.replace(6, false);
//            tempResult.replace(5, false);
//            tempResult.replace(4, false);
//            tempResult.replace(3, true);
//        }
//        if(tempResult.at(5) && tempResult.at(6) && tempResult.at(7) && tempResult.at(8)) {
//            tempResult.replace(8, false);
//            tempResult.replace(7, false);
//            tempResult.replace(6, false);
//            tempResult.replace(5, false);
//            tempResult.replace(4, true);
//        }
//        if(tempResult.at(6) && tempResult.at(7) && tempResult.at(8)) {
//            tempResult.replace(8, false);
//            tempResult.replace(7, false);
//            tempResult.replace(6, false);
//            tempResult.replace(5, true);
//        }
//        if(tempResult.at(7) && tempResult.at(8)) {
//            tempResult.replace(8, false);
//            tempResult.replace(7, false);
//            tempResult.replace(6, true);
//        }
//        if(tempResult.at(8)) {
//            tempResult.replace(8, false);
//            tempResult.replace(7, true);
//        }

//        qDebug() << "==========>";
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

//        tempResult.replace(8, true);

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
//        print(tempResult);
//        qDebug() << "<==========";
    }
}

void fromBinToHex(const QVector<QVector<bool> > &results)
{
    QString tempStr;
    QString tempStrHex;
    QString strHex;

    for(int i = 0; i < results.size(); ++i) {
        for(int j = 0; j < 9; ++j) {
            if(results.at(i).at(j)) {
                tempStr.append("1");
            } else {
                tempStr.append("0");
            }
        }

        for(int j = 1; j < 9; ++j) {
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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<QVector<bool> > vec;

    counter(vec);
    print(vec);

    qDebug() << "Size" << vec.size();

    fromBinToHex(vec);

    return a.exec();
}
