#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>

#include "Generator.h"
#include "ConsoleView.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Generator *generator = new Generator(18, 1);
    ConsoleView *view = new ConsoleView(generator, "output.txt");
    generator->generate();

//    for(int i = 2; i < 31; ++i) {
//        qDebug() << "For" << i << ":";
//        generator->setSequenceSize(i);
//        generator->generate();
//    }

    return a.exec();
}
