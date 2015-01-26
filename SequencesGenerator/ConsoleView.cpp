#include <QTextStream>
#include "ConsoleView.h"

ConsoleView::ConsoleView(Generator *generator, const QString &fileOutput, QObject *parent) :
    QObject(parent)
  , m_generator(generator)
{
    setFileHandler(fileOutput);
    connect(m_generator, SIGNAL(sequenceGenerated(QVector<int>)), this, SLOT(printToFile(QVector<int>)));
    connect(m_generator, SIGNAL(sequenceGenerated(QVector<int>)), this, SLOT(show(QVector<int>)));
}

void ConsoleView::printToFile(const QVector<int> &currentSequence)
{
    if(!m_file.isOpen() && !m_file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text)) {
        qErrnoWarning(QString("ERROR!\nCan't create file: \"" + m_file.fileName() + "\"").toStdString().c_str());
    }
    QTextStream out(&m_file);

    out << "BIN ";
    for(int i = 0; i < currentSequence.size(); ++i) {
        out << fromIntToBoolString(currentSequence.at(i));
    }
    out << "\n";

    m_file.close();
}

void ConsoleView::show(const QVector<int> &currentSequence)
{
    QTextStream out(stdout);

    for(int i = 0; i < currentSequence.size(); ++i) {
        out << fromIntToBoolString(currentSequence.at(i));
    }
    out << "\n";
}

void ConsoleView::setFileHandler(const QString &fileOutput)
{
    m_file.setFileName(fileOutput);
    if(!m_file.isOpen() && !m_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qErrnoWarning(QString("ERROR!\nCan't create file: \"" + m_file.fileName() + "\"").toStdString().c_str());
    }
    m_file.close();
}

QString ConsoleView::fromIntToBoolString(const int &currentInt)
{
    if(currentInt == 1) {
        return "1";
    } else if(currentInt == -1) {
        return "0";
    } else {
        return "Error!";
    }
}
