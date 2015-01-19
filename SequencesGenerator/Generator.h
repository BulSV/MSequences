#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(const int &seqSize,
                       const int &absScatter = 1,
                       bool isFiltered = true,
                       const int &absMaxScatter = 1,
                       QObject *parent = 0);
    ~Generator();
    void setAbsScatter(const int &absScatter);
    void setAbsMaxScatter(const int &absMaxScatter);
    int getAbsScatter() const;
    int getAbsMaxScatter() const;
    void setSequenceSize(const int &seqSize);
    int getSequenceSize() const;
    void generate();
    QVector<QVector<int> > getSequences();
signals:
    void sequenceGenerated(QVector<int>);
private:
    int m_combSize;
    int m_seqSize;
    int m_absScatter;
    bool m_isFiltered;
    int m_absMaxScatter;
    int *m_combs;
    QVector<int> m_sequence;
    QVector<QVector<int> > m_sequences;

    void fillCombinations();
    void gen(int phase);
    bool filter();
};

#endif // GENERATOR_H
