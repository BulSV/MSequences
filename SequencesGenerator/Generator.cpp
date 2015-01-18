#include "Generator.h"

#include <QDebug>

Generator::Generator(const int &seqSize, const int &absScatter, QObject *parent) :
    QObject(parent)
{
    setSequenceSize(seqSize);
    setAbsScatter(absScatter);
    fillCombinations();
}

Generator::~Generator()
{
    delete m_combs;
}

void Generator::setAbsScatter(const int &absScatter)
{
    m_absScatter = qAbs(absScatter);
}

int Generator::getAbsScatter() const
{
    return m_absScatter;
}

void Generator::setSequenceSize(const int &seqSize)
{
    if(qAbs(seqSize) > 1) {
        m_seqSize = qAbs(seqSize);
    } else {
        qDebug() << "ERROR! Size of sequences must be equal or greater than 2";
        qDebug() << "Size set to 2";
        m_seqSize = 2;
    }
}

int Generator::getSequenceSize() const
{
    return m_seqSize;
}

void Generator::generate()
{    
    int phase = m_seqSize - 1;

    m_sequence.fill(0, m_seqSize);

   gen(phase);
}

void Generator::gen(int phase)
{
    qDebug() << "in gen(" << phase << ")";
    int summa = 0;

    if(phase >= ((m_seqSize & 1) ? (m_seqSize + 1)/2 : m_seqSize/2)) {
        for(int combIndex = 0; combIndex < m_combSize; combIndex += 2) {
            m_sequence[m_seqSize - phase - 1] = m_combs[combIndex];
            m_sequence[phase] = m_combs[combIndex + 1];
            qDebug() << "level:" << m_seqSize - phase;
            qDebug() << "combinations(" << m_combs[combIndex] << "," << m_combs[combIndex + 1] << ")";
            qDebug() << "combIndex =" << combIndex;
            for(int index = 0; index < m_seqSize - phase; ++index) {
                summa += m_sequence.at(index)*m_sequence.at(index + phase);
            }
            qDebug() << "summa =" << summa;
            if(qAbs(summa) <= m_absScatter) {
                gen(--phase);
                ++phase;
            } else {
                summa = 0;
                m_sequence[m_seqSize - phase - 1] = 0;
                m_sequence[phase] = 0;
                qDebug() << "Wrong branch!";
            }
        }
    } else {
        qDebug() << "emit sequenceGenerated(" << m_sequence << ")";
        emit sequenceGenerated(m_sequence);
        m_sequences.append(m_sequence);
    }
}

QVector<QVector<int> > Generator::getSequences()
{
    return m_sequences;
}

void Generator::fillCombinations()
{
    int v[] = {-1, -1, -1, 1, 1, -1, 1, 1};
    m_combSize = 8;
    m_combs = new int[m_combSize];

    for(int i = 0; i < m_combSize; ++i) {
        m_combs[i] = v[i];
    }
}
