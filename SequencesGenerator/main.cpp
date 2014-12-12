#include <QCoreApplication>
#include <QVector>
#include <QTextStream>
#include <QDebug>

#include "Generator.h"
#include "ConsoleView.h"

QVector<bool> a; // MSequence
QVector<QVector<bool> > as; // MSequences

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Generator *generator = new Generator(29);
    ConsoleView *view = new ConsoleView(generator, "output.txt");
    generator->generate();

    qDebug() << "What's all folks!";

    return a.exec();
}
