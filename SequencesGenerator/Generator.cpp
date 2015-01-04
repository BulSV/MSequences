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
    m_seqSize = qAbs(seqSize);    
}

int Generator::getSequenceSize() const
{
    return m_seqSize;
}

void Generator::generate()
{
    bool isSuccess = false;
    int phaseLimit = 0;
    int currCombIndex = 0;
    int phase = m_seqSize - 1;
    int summa = 0;
    QVector<int> sequence;

    sequence.fill(0, m_seqSize);

    if(m_seqSize % 2) {
        phaseLimit = m_seqSize/2 + 1;
    } else {
        phaseLimit = m_seqSize/2;
    }

    phase = m_seqSize - 1;

    while(true) {
        while(true) {
            for(int combIndex = currCombIndex; combIndex < m_combSize - 1; ++combIndex) {
                sequence[phase] = m_combs[combIndex];
                sequence[m_seqSize - 1 - phase] = m_combs[combIndex + 1];

                for(int index = 0; index < m_seqSize - phase; ++index) {
                    summa += sequence[index]*sequence[index + phase];
                }

                if(qAbs(summa) <= m_absScatter) {
                    isSuccess = true;
                    break;
                } else {
                    isSuccess = false;
                }
            }

            if(!isSuccess) {
                ++phase;
                ++currCombIndex;
            } else {
                if(phase > 1) {
                    --phase;
                }
            }

            if(phase <= phaseLimit) {
                break;
            }
        }

        if(isSuccess) {
            ++phase;
            ++currCombIndex;
            m_sequences.push_back(sequence);
            emit sequenceGenerated(sequence);
        } else {
            break;
        }
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

//    for(int i = 0; i < m_combSize; ++i) {
//        qDebug() << "m_comb[" << i << "]" << m_combs[i];
//    }
}
