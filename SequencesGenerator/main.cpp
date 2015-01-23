#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>

#include "Generator.h"
#include "ConsoleView.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Generator *generator = new Generator(18, 2, true, 2);
    ConsoleView *view = new ConsoleView(generator, "output.txt");
    generator->generate();
    qDebug() << "END";

    return a.exec();
}
