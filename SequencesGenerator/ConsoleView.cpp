#include <QTextStream>
#include "ConsoleView.h"

ConsoleView::ConsoleView(Generator *generator, const QString &fileOutput, QObject *parent) :
    QObject(parent)
  , m_generator(generator)
{
    setFileHandler(fileOutput);
    connect(m_generator, SIGNAL(sequenceGenerated), this, SLOT(printToFile(QVector<int>)));
}

void ConsoleView::printToFile(const QVector<int> &currentSequence)
{
    QTextStream out(stdout);

    for(int i = 0; i < currentSequence.size(); ++i) {
        out << currentSequence.at(i);
    }
    out << "\n";
}

void ConsoleView::show(const QVector<int> &currentSequence)
{
    QTextStream out(stdout);

    for(int i = 0; i < currentSequence.size(); ++i) {
        out << currentSequence.at(i);
    }
    out << "\n";
}

void ConsoleView::setFileHandler(const QString &fileOutput)
{
    m_file.setFileName(fileOutput);
    if(!m_file.isOpen()) {
        m_file.open(QIODevice::Append | QIODevice::Text);
    }
}
