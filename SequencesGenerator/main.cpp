#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>

#include "Generator.h"
#include "ConsoleView.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Generator *generator = new Generator(51, 3, true, 3);
    ConsoleView *view = new ConsoleView(generator, "output.txt");
    generator->generate();

    return a.exec();
}
