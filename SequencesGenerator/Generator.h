#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
#include <QMutex>

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(const int &seqSize,
                       const int &terminalSideLobes = 1,
                       bool isFiltered = true,
                       const int &closeCentralSideLobes = 1,
                       QObject *parent = 0);
    ~Generator();
    void setCloseCentralSideLobes(const int &closeCentralSideLobes);
    void setTerminalSideLobes(const int &absMaxScatter);
    void setFiltered(const bool &isFiltered);
    bool isFiltered() const;
    int getCloseCentralSideLobes() const;
    int getTerminalSideLobes() const;
    void setSequenceSize(const int &seqSize);
    int getSequenceSize() const;
    void generate();
    QVector<QVector<int> > getSequences();
signals:
    void sequenceGenerated(QVector<int>);
private:
    int m_combSize;
    int m_combSizeSimplified;
    int m_seqSize;
    int m_closeCentralSideLobes;
    bool m_isFiltered;
    int m_terminalSideLobes;
    int *m_combs;
    int *m_combsSimplified;
    QVector<int> m_sequence;
    QVector<QVector<int> > m_tempSequences;
    QVector<QVector<int> > m_sequences;
    QString m_progressBar;
    int m_progress;
    QMutex m_mutex;

    void fillCombinations();
    void gen(int phase, QVector<int> &seq, bool isSimplified/*, int i = 0*/);
    int phaseLimit();
    bool isOddSeqSize();
    bool filter(const QVector<int> &seq);
    void progressBar();

    static QVector<bool> m_wasShown;
};

#endif // GENERATOR_H
