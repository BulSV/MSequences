#include "Generator.h"

#include <QDebug>

Generator::Generator(const int &seqSize, const int &absScatter) :
    m_summa(0)
{
    setSequenceSize(seqSize);
    setAbsScatter(absScatter);
    fillCombinations();
}

Generator::~Generator()
{
    for (int i = 0; i < m_rows; ++i)
        delete [] m_combinations[i];

    delete [] m_combinations;
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
    m_phase = m_seqSize - 1;
}

int Generator::getSequenceSize() const
{
    return m_seqSize;
}

void Generator::generate()
{
    if(!m_phase) {
        return;
    }
    for(int m = 0; m < 29 - m_phase; ++m) {
        if(m == 29 - 1 - m_phase) {
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 2; ++j) {
                    m_summa += m_combinations[i][j]*m_combinations[i][j+1];

                    if(qAbs(m_summa) <= m_absScatter) {
                        m_sequence[m] = m_combinations[i][j]; // convert v[j] to bool before assignment
                        m_sequence[m+m_phase] = m_combinations[i][j+1]; // convert v[j+1] to bool before assignment
                        generate();
                    } else {
                        m_summa -= m_combinations[i][j]*m_combinations[i][j+1];
                    }
                }
            }
        }
        qDebug() << "ia[" << m << "] =" << m_sequence[m] << "| ia[" << m+m_phase << "] =" << m_sequence[m + m_phase];
//        m_summa += m_sequence.at(m)*m_sequence.at(m+m_phase);
        qDebug() << "qAbs(m_summa):" << qAbs(m_summa);
    }
}

QVector<QVector<int> > Generator::getSequences()
{
    return m_sequences;
}

void Generator::fillCombinations()
{
    m_rows = 4;
    m_columns = 2;
    int v[4][2] = {
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1}
    };
    m_combinations = new int*[m_rows];
    for(int i = 0; i < m_rows; ++i) {
        m_combinations[i] = new int[m_columns];
    }
    for(int i = 0; i < m_rows; ++i) {
        for(int j = 0; j < m_columns; ++j) {
            m_combinations[i][j] = v[i][j];
        }
    }
}
