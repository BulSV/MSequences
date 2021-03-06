#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QRegExp>

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

    QString tempStr = "1";

    qDebug() << "tempStr.at(0):" << tempStr.at(0);

    qDebug() << "source1:";
    print(source1);
    qDebug() << "source2:";
    qDebug() << source2;
//    qDebug() << source2.at(0) << source2.at(1) << source2.at(2) << source2.at(3)
//                 << source2.at(4) << source2.at(5) << source2.at(6) << source2.at(7)
//                     << source2.at(8);

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

    bool isWasLowerLimit = false;
    bool isWasUpperLimit = false;

    while(true) {
        if(tempResult.at(8) && tempResult.at(7) && tempResult.at(6) && tempResult.at(5)
                && tempResult.at(4) && tempResult.at(3) && tempResult.at(2) && tempResult.at(1)
                && tempResult.at(0)) {
            break;
        }
        if(tempResult.at(7) && tempResult.at(6) && tempResult.at(5) && tempResult.at(4)
                && tempResult.at(3) && tempResult.at(2) && tempResult.at(1) && tempResult.at(0)) {
            tempResult.replace(0, false);
            tempResult.replace(1, false);
            tempResult.replace(2, false);
            tempResult.replace(3, false);
            tempResult.replace(4, false);
            tempResult.replace(5, false);
            tempResult.replace(6, false);
            tempResult.replace(7, false);
            tempResult.replace(8, true);
        }
        if(tempResult.at(6) && tempResult.at(5) && tempResult.at(4) && tempResult.at(3)
                && tempResult.at(2) && tempResult.at(1) && tempResult.at(0)) {
            tempResult.replace(0, false);
            tempResult.replace(1, false);
            tempResult.replace(2, false);
            tempResult.replace(3, false);
            tempResult.replace(4, false);
            tempResult.replace(5, false);
            tempResult.replace(6, false);
            tempResult.replace(7, true);
        }
        if(tempResult.at(5) && tempResult.at(4) && tempResult.at(3) && tempResult.at(2)
                && tempResult.at(1) && tempResult.at(0)) {
            tempResult.replace(0, false);
            tempResult.replace(1, false);
            tempResult.replace(2, false);
            tempResult.replace(3, false);
            tempResult.replace(4, false);
            tempResult.replace(5, false);
            tempResult.replace(6, true);
        }
        if(tempResult.at(4) && tempResult.at(3) && tempResult.at(2) && tempResult.at(1)
                && tempResult.at(0)) {
            tempResult.replace(0, false);
            tempResult.replace(1, false);
            tempResult.replace(2, false);
            tempResult.replace(3, false);
            tempResult.replace(4, false);
            tempResult.replace(5, true);
        }
        if(tempResult.at(3) && tempResult.at(2) && tempResult.at(1) && tempResult.at(0)) {
            tempResult.replace(0, false);
            tempResult.replace(1, false);
            tempResult.replace(2, false);
            tempResult.replace(3, false);
            tempResult.replace(4, true);
        }
        if(tempResult.at(2) && tempResult.at(1) && tempResult.at(0)) {
            tempResult.replace(0, false);
            tempResult.replace(1, false);
            tempResult.replace(2, false);
            tempResult.replace(3, true);
        }
        if(tempResult.at(1) && tempResult.at(0)) {
            tempResult.replace(0, false);
            tempResult.replace(1, false);
            tempResult.replace(2, true);
        }
        if(tempResult.at(0)) {
            tempResult.replace(0, false);
            tempResult.replace(1, true);
        }

        qDebug() << "==========>";
        print(tempResult);
        qDebug() << "<==========";

        if(isEqual(tempResult, "111100000")) {
            qDebug() << "isWasLowerLimit" << isWasLowerLimit;
            isWasLowerLimit = true;
        }

        if(isEqual(tempResult, "100011111")) {
            qDebug() << "isWasUpperLimit" << isWasUpperLimit;
            isWasUpperLimit = true;
        }

        if(/*isWasLowerLimit && !isWasUpperLimit && */isValid(tempResult)) {
            results.push_back(tempResult);
        }

        tempResult.replace(0, true);

        if(/*isWasLowerLimit && !isWasUpperLimit && */isValid(tempResult)) {
            results.push_back(tempResult);
        }
    }
}

void fromBinToHex(const QVector<QVector<bool> > &results)
{
    QString tempStr;
    QString tempStrHex;
    QString strHex;

    for(int i = 0; i < results.size(); ++i) {
        for(int j = 8; j > -1; --j) {
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
