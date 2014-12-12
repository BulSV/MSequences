#include <QCoreApplication>
#include <QVector>
#include <QTextStream>
#include <QDebug>

#include "Generator.h"

QVector<bool> a; // MSequence
QVector<QVector<bool> > as; // MSequences
bool isExist = false;

void print(const QVector<int> &v)
{
    QTextStream out(stdout);

    for(int i = 0; i < v.size(); ++i) {
        out << v.at(i);
    }
    out << "\n";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Generator generator(29);
    generator.generate();

    qDebug() << "What's all folks!";

    return a.exec();
}
