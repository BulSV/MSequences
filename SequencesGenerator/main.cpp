#include <QCoreApplication>
#include <QVector>
#include <QtMath>
#include <QTextStream>
#include <QDebug>

int scatter = 0; // maximum scattering
int v[4][2] = {
    {-1, -1},
    {-1, 1},
    {1, -1},
    {1, 1}
};
QVector<bool> a; // MSequence
QVector<QVector<bool> > as; // MSequences
bool isExist = false;

QVector<int> ia;
void generator(const int &scatter, const int &seqSize)
{
    QTextStream out(stdout);

    ia.fill(0, seqSize);
    int summa = 0;

    for(int phase = seqSize-1; phase > seqSize/2 - 1; --phase) {
        for(int m = 0; m < seqSize - phase; ++m) {
            if(m == seqSize - 1 - phase) {
                for(int i = 0; i < 4; ++i) {
                    for(int j = 0; j < 2; ++j) {
                        summa += v[i][j]*v[i][j+1];

                        if(qAbs(summa) <= scatter) {
                            ia[m] = v[i][j]; // convert v[j] to bool before assignment
                            ia[m+phase] = v[i][j+1]; // convert v[j+1] to bool before assignment
                            isExist = true; // is exist solution of aquation
                            break;
                        } else {
                            summa -= v[i][j]*v[i][j+1];
                        }
                        isExist = false;
                    }
                }
            }
            summa += ia.at(m)*ia.at(m+phase);
            qDebug() << "ia[" << m << "] =" << ia[m] << "| ia[" << m+phase << "] =" << ia[m + phase];
            qDebug() << "qAbs(summa):" << qAbs(summa);
        }
    }

    out.flush(); // to set visible output in console
}

void testV()
{
    QTextStream out(stdout);

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 2; ++j) {
            out << "v[" << i << "][" << j << "]: " << v[i][j] << "\t";
            if(!((j + 1) % 2)) {
                out << "\n";
            }
        }
    }
    out.flush();
}

void print(const QVector<int> &v)
{
    QTextStream out(stdout);

    for(int i = 0; i < v.size(); ++i) {
        out << v.at(i);
    }
    out << "\n";
}
int indexGenIn = 0;
int indexGenOut = 0;
void generator2(const int &scatter, int phase, int summa)
{
    QTextStream out(stdout);

    if(!phase) {
        return;
    }
    for(int m = 0; m < 29 - phase; ++m) {
        if(m == 29 - 1 - phase) {
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 2; ++j) {
                    summa += v[i][j]*v[i][j+1];

                    if(qAbs(summa) <= scatter) {
                        ia[m] = v[i][j]; // convert v[j] to bool before assignment
                        ia[m+phase] = v[i][j+1]; // convert v[j+1] to bool before assignment
qDebug() << ++indexGenIn;
                        generator2(scatter, summa, --phase);
qDebug() << --indexGenOut;
                    } else {
                        summa -= v[i][j]*v[i][j+1];
                    }
                }
            }
        }
        qDebug() << "ia[" << m << "] =" << ia[m] << "| ia[" << m+phase << "] =" << ia[m + phase];
//        summa += ia.at(m)*ia.at(m+phase);
        qDebug() << "qAbs(summa):" << qAbs(summa);
    }

    out.flush(); // to set visible output in console
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    generator(1, 29);
    ia.fill(0, 29);
    generator2(1, 28, 0);

    print(ia);

    qDebug() << "What's all folks!";

    return a.exec();
}
