#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include <QObject>
#include <QVector>
#include <QFile>
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
    Generator *m_generator;
    QFile m_file;

    void setFileHandler(const QString &fileOutput);
};

#endif // CONSOLEVIEW_H
