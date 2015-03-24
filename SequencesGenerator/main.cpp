#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include <QDebug>

#include "Generator.h"
#include "ConsoleView.h"

void resultsOutput(Generator *generator, QFile &file)
{
    QTextStream cout(stdout);
    QTextStream fout(&file);

    if(!file.isOpen() && !file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text)) {
        qErrnoWarning(QString("ERROR!\nCan't create file: \"" + file.fileName() + "\"").toStdString().c_str());
    }
    cout << "Starting to generate sequences with the following parameters:\n";
    cout << "\tSize: " << generator->getSequenceSize() << "\n";
    fout << "Starting to generate sequences with the following parameters:\n";
    fout << "\tSize: " << generator->getSequenceSize() << "\n";
    if(generator->isFiltered()) {
        cout << "\tClose-central side lobes within: |" << generator->getCloseCentralSideLobes() << "|\n";
        fout << "\tClose-central side lobes within: |" << generator->getCloseCentralSideLobes() << "|\n";
    } else {
        cout << "\tClose-central side lobes within: NOT LIMITED\n";
        fout << "\tClose-central side lobes within: NOT LIMITED\n";
    }
    cout << "\tTerminal side lobes within: |" << generator->getTerminalSideLobes() << "|\n";
    fout << "\tTerminal side lobes within: |" << generator->getTerminalSideLobes() << "|\n";
    if(generator->isBalanced()) {
        cout << "\tBalanced within: " << generator->disbalanse() << "\n";
        fout << "\tBalanced within: " << generator->disbalanse() << "\n";
    } else {
        cout << "\tBalanced within: NOT BALANCED\n";
        fout << "\tBalanced within: NOT BALANCED\n";
    }
    cout << "Generated sequences:\n";
    cout.flush();
    fout << "Generated sequences:\n";
    file.close();

    generator->generate();
    qApp->processEvents(); // for synchronizing outputs of sequences, cout and fout

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

    qRegisterMetaType<QVector<int> >("QVector<int>");

    QFile file("output.txt");

    Generator *generator = new Generator(36, 3, true, 3, true, 0);
    ConsoleView *view = new ConsoleView(generator, file.fileName());

    resultsOutput(generator, file);

    QVector<QVector<int> > combs;
    qDebug();
    for(int i = 0; i < generator->getSequences().size(); ++i) {
        qDebug() << "\nFor:";
        view->show(generator->getSequences().at(i));
        qDebug() << "Additional combinations are:";
        combs = Generator::combinations(generator->getSequences().at(i));
        for(int j = 0; j < combs.size(); ++j) {
            view->show(combs.at(j));
        }
    }

    return a.exec();
}
