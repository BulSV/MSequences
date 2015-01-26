#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include <QDebug>

#include "Generator.h"
#include "ConsoleView.h"

void resultsOutput(QTextStream &fout, Generator *generator, QFile &file)
{
    QTextStream cout(stdout);

    if(!file.isOpen() && !file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text)) {
        qErrnoWarning(QString("ERROR!\nCan't create file: \"" + file.fileName() + "\"").toStdString().c_str());
    }
    cout << "Starting to generate a sequences with the following parameters:\n";
    cout << "\tSize: " << generator->getSequenceSize() << "\n";
    fout << "Starting to generate a sequences with the following parameters:\n";
    fout << "\tSize: " << generator->getSequenceSize() << "\n";
    if(generator->isFiltered()) {
        cout << "\tClose-central side lobes within: |" << generator->getCloseCentralSideLobes() << "|\n";
        fout << "\tClose-central side lobes within: |" << generator->getCloseCentralSideLobes() << "|\n";
    } else {
        cout << "\tClose-central side lobes within: NOT LIMITED\n";
        fout << "\tClose-central side lobes within: NOT LIMITED\n";
    }
    cout << "\tTerminal side lobes within: |" << generator->getTerminalSideLobes() << "|\n";
    cout << "Generated sequences:\n";
    cout.flush();
    fout << "\tTerminal side lobes within: |" << generator->getTerminalSideLobes() << "|\n";
    fout << "Generated sequences:\n";
    file.close();

    generator->generate();

    if(!file.isOpen() && !file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text)) {
        qErrnoWarning(QString("ERROR!\nCan't create file: \"" + file.fileName() + "\"").toStdString().c_str());
    }
    cout << "Total generated sequences: " << generator->getSequences().size() << "\n";
    cout << "Generation is over!";
    fout << "Total generated sequences: " << generator->getSequences().size() << "\n";
    fout << "Generation is over!";
    file.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("output.txt");
    QTextStream fout(&file);

    Generator *generator = new Generator(51, 3, true, 1);
    ConsoleView *view = new ConsoleView(generator, file.fileName());

    resultsOutput(fout, generator, file);

    return a.exec();
}
