#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>

#include "Generator.h"
#include "ConsoleView.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Generator *generator = new Generator(5);
    ConsoleView *view = new ConsoleView(generator, "output.txt");
    generator->generate();
    qDebug() << generator->getSequences();

    qDebug() << "What's all folks!";

    return a.exec();
}
