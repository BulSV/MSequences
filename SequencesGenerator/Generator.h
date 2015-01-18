#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(const int &seqSize, const int &absScatter = 1, QObject *parent = 0);
    ~Generator();
    void setAbsScatter(const int &absScatter);
    int getAbsScatter() const;
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
    int *m_combs;
    QVector<int> m_sequence;
    QVector<QVector<int> > m_sequences;

    void fillCombinations();
    void gen(int phase);
};

#endif // GENERATOR_H
