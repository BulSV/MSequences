#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QtMath>


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

QByteArray fromBoolToBinByteArray(const QVector<bool> &result)
{
    QByteArray arr;

    for(int i = 0; i < result.size(); ++i) {
        if(result.at(i)) {
            arr.append("1");
        } else {
            arr.append("0");
        }
    }

    return arr;
}

QByteArray fromBinToHex(const QVector<bool> &result)
{
    QByteArray binBa = fromBoolToBinByteArray(result);
    QByteArray tempBinBa;
    QByteArray hexBa;

    // Complements the bits with zeros
    if(binBa.size() % 4) {
        for(int i = 0; i < binBa.size() % 4; ++i) {
            binBa.push_front("0");
        }
    }

    for(int i = 0; i < binBa.size(); ++i) {
        tempBinBa += binBa.at(i);
        if(!((i + 1) % 4)) {
            if(tempBinBa == "0000") {
                hexBa += "0";
            }
            if(tempBinBa == "0001") {
                hexBa += "1";
            }
            if(tempBinBa == "0010") {
                hexBa += "2";
            }
            if(tempBinBa == "0011") {
                hexBa += "3";
            }
            if(tempBinBa == "0100") {
                hexBa += "4";
            }
            if(tempBinBa == "0101") {
                hexBa += "5";
            }
            if(tempBinBa == "0110") {
                hexBa += "6";
            }
            if(tempBinBa == "0111") {
                hexBa += "7";
            }
            if(tempBinBa == "1000") {
                hexBa += "8";
            }
            if(tempBinBa == "1001") {
                hexBa += "9";
            }
            if(tempBinBa == "1010") {
                hexBa += "A";
            }
            if(tempBinBa == "1011") {
                hexBa += "B";
            }
            if(tempBinBa == "1100") {
                hexBa += "C";
            }
            if(tempBinBa == "1101") {
                hexBa += "D";
            }
            if(tempBinBa == "1110") {
                hexBa += "E";
            }
            if(tempBinBa == "1111") {
                hexBa += "F";
            }
            tempBinBa.clear();
        }
    }

    return hexBa;
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
            qDebug() << "Error! The sequence" << ba << "has not HEX format!";
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
            qDebug() << "Error! The sequence" << ba << "has not BIN format!";
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
        qDebug() << "Error! The sequence" << ba << "is not valid!";
        qDebug() << "For HEX-format sequence write in file at the begin of line: HEX";
        qDebug() << "For BIN-format sequence write in file at the begin of line: BIN";

        return false;
    }

    return true;
}

float ProtectRate(const int &ACF_0, const int &ACF_max)
{
    return (20.0*qLn(qAbs((float)ACF_0/(float)ACF_max)))/qLn(10.0);
}

void ACFSmax()
{
    QFile resultsOutputFile("ACFOutput.txt");
    if(!resultsOutputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qErrnoWarning("ERROR!\nCan't create file: \"ACFOutput.txt\"");
    }

    QTextStream out(&resultsOutputFile);

    qDebug() << "==========START_ACF_TEST==========";
    out << "==========START_ACF_TEST==========\n";

    QVector<bool> vec;
    int pos = 0;
    QFile file("ACFInput.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qErrnoWarning("ERROR!\nCan't open file: \"ACFInput.txt\"");
    }

    while(mSequenceReader(file, vec, pos)) {
        if(!vec.isEmpty()) {

            qDebug() << "===========SUB_ACF_TEST===========";
            out << "===========SUB_ACF_TEST===========\n";

            print(vec);
            printToFile(resultsOutputFile, vec);

            qDebug() << "HEX format:" << fromBinToHex(vec);
            qDebug() << "Size of sequence:" << vec.size();
            out << "HEX format: " << fromBinToHex(vec) << "\n";
            out << "Size of sequence: " << vec.size() << "\n";

            QVector<int> acfs_phases;

            for(int i = 1; i < vec.size(); ++i) {
                acfs_phases.push_back(ACFphase(vec, i));

                qDebug() << "ACF(" << i << ") =" << acfs_phases.at(i - 1);
                out << "ACF(" << i << ") = " << acfs_phases.at(i - 1) << "\n";
            }

            int ACF_max = ACFmax(acfs_phases);
            qDebug() << "MAX ACF(phase) = " << ACF_max;
            qDebug() << "Protection rate:" << ProtectRate(vec.size(), ACF_max);
            out << "MAX ACF(phase) = " << ACF_max << "\n";
            out << "Protection rate: " << ProtectRate(vec.size(), ACF_max) << "\n";

            vec.clear();
        }
    }

    qDebug() << "===========END_ACF_TEST===========";
    out << "===========END_ACF_TEST===========\n";

    file.close();
    resultsOutputFile.close();
}

int CCFphase(const QVector<bool> &sequence1, const QVector<bool> &sequence2, const int &phase)
{
    int result = 0;

    if((phase < 0 && sequence1.size() >= sequence2.size()) || (phase >= 0 && sequence2.size() > sequence1.size())){
        for(int i = 0; i < sequence1.size() - qAbs(phase); ++i) {
            result += fromBoolToInt(sequence1.at(i))*fromBoolToInt(sequence2.at(i + qAbs(phase)));
        }
    } else {
        for(int i = 0; i < sequence2.size() - qAbs(phase); ++i) {
            result += fromBoolToInt(sequence1.at(i + qAbs(phase)))*fromBoolToInt(sequence2.at(i));
        }
    }

    return result;
}

int CCFmax(const QVector<int> &ccfs_phases)
{
    return ACFmax(ccfs_phases);
}

void CCFSmax()
{
    QFile resultsOutputFile("CCFOutput.txt");
    if(!resultsOutputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qErrnoWarning("ERROR!\nCan't create file: \"CCFOutput.txt\"");
    }

    QTextStream out(&resultsOutputFile);

    qDebug() << "==========START_CCF_TEST==========";
    out << "==========START_CCF_TEST==========\n";

    QVector<bool> vec;
    QVector<bool> vec1;
    QVector<bool> vec2;
    int pos = 0;
    QFile file("CCFInput.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qErrnoWarning("ERROR!\nCan't open file: \"CCFInput.txt\"");
    }

    qDebug() << "===========SUB_CCF_TEST===========";
    out << "===========SUB_CCF_TEST===========\n";

    while(mSequenceReader(file, vec, pos)) {
        if(!vec.isEmpty()) {
            print(vec);
            printToFile(resultsOutputFile, vec);

            qDebug() << "HEX format:" << fromBinToHex(vec);
            qDebug() << "Size of sequence:" << vec.size();
            out << "HEX format:" << fromBinToHex(vec) << "\n";
            out << "Size of sequence: " << vec.size() << "\n";

            if(vec1.isEmpty()) {
                vec1 = vec;
            } else {
                vec2 = vec;
            }
            vec.clear();
        }
    }

    QVector<int> ccfs_phases;

    for(int i = 1 - vec1.size(); i <  vec2.size(); ++i) {
        ccfs_phases.push_back(CCFphase(vec1, vec2, i));

        qDebug() << "CCF(" << i << ") =" << ccfs_phases.last();
        out << "CCF(" << i << ") = " << ccfs_phases.last() << "\n";
    }

    int CCF_max = CCFmax(ccfs_phases);
    int CCF_0 = 0;
    vec1.size() > vec2.size() ? CCF_0 = vec2.size() : CCF_0 = vec1.size();
    qDebug() << "MAX CCF(phase) = " << CCFmax(ccfs_phases);
    qDebug() << "Protection rate:" << ProtectRate(CCF_0, CCF_max);
    out << "MAX CCF(phase) = " << CCFmax(ccfs_phases) << "\n";
    out << "Protection rate: " << ProtectRate(CCF_0, CCF_max) << "\n";

    vec1.clear();
    vec2.clear();

    qDebug() << "===========END_CCF_TEST===========";
    out << "===========END_CCF_TEST===========\n";

    file.close();
    resultsOutputFile.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ACFSmax();

    CCFSmax();

    return a.exec();
}
