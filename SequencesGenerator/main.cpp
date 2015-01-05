#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>

#include "Generator.h"
#include "ConsoleView.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Generator *generator = new Generator(13);
    ConsoleView *view = new ConsoleView(generator, "output.txt");

    for(int i = 5; i < 31; ++i) {
        qDebug() << "For" << i << ":";
        generator->setSequenceSize(i);
        generator->generate();
    }    

    return a.exec();
}
