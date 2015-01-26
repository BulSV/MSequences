#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QMutex>
#include "IView.h"
#include "Generator.h"

class ConsoleView : public QObject , public IView
{
    Q_OBJECT
public:
    explicit ConsoleView(Generator *generator, const QString &fileOutput, QObject *parent = 0);
signals:

public slots:
    void printToFile(const QVector<int> &currentSequence);
    void show(const QVector<int> &currentSequence);
private:
    mutable QMutex m_mutex;
    Generator *m_generator;
    QFile m_file;

    void setFileHandler(const QString &fileOutput);
    QString fromIntToBoolString(const int &currentInt);
};

#endif // CONSOLEVIEW_H
