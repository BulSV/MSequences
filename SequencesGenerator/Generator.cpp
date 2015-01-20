#include "Generator.h"
#include <QtMath>

#ifdef DEBUG
#include <QDebug>
#endif

Generator::Generator(const int &seqSize,
                     const int &absScatter,
                     bool isFiltered,
                     const int &absMaxScatter,
                     QObject *parent) :
    QObject(parent)
  , m_isFiltered(isFiltered)
{
    setSequenceSize(seqSize);
    setAbsScatter(absScatter);
    setAbsMaxScatter(absMaxScatter);
    fillCombinations();
}

Generator::~Generator()
{
    delete m_combs;
}

void Generator::setAbsScatter(const int &absScatter)
{
    if(qAbs(absScatter)) {
        m_absScatter = qAbs(absScatter);
    } else {
        m_absScatter = 1;
    }
}

void Generator::setAbsMaxScatter(const int &absMaxScatter)
{
    if(qAbs(absMaxScatter)) {
        m_absMaxScatter = absMaxScatter;
    } else {
        m_absMaxScatter = 1;
    }
}

int Generator::getAbsScatter() const
{
    return m_absScatter;
}

int Generator::getAbsMaxScatter() const
{
    return m_absMaxScatter;
}

void Generator::setSequenceSize(const int &seqSize)
{
    if(qAbs(seqSize) > 1) {
        m_seqSize = qAbs(seqSize);
    } else {
        qErrnoWarning("ERROR! Size of sequences must be equal or greater than 2");
        qErrnoWarning("Size set to 2");
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
#ifdef DEBUG
    qDebug() << "in gen(" << phase << ")";
#endif
    int summa = 0;

    if(phase >= ((m_seqSize & 1) ? (m_seqSize - 1)/2 : m_seqSize/2)) {
        if((m_seqSize & 1) && (phase == ((m_seqSize & 1) ? (m_seqSize - 1)/2 : m_seqSize/2))) {
            for(int combIndex = 0; combIndex < 2; ++combIndex) {
                m_sequence[phase] = qPow(-1, combIndex + 1);
#ifdef DEBUG
                qDebug() << "level:" << m_seqSize - phase;
                qDebug() << "combinations(" << qPow(-1, combIndex + 1) << ")";
                qDebug() << "combIndex =" << combIndex;
                qDebug() << "m_sequence[" << phase << "] =" << m_sequence[phase];
#endif
                for(int index = 0; index < m_seqSize - phase; ++index) {
                    summa += m_sequence.at(index)*m_sequence.at(index + phase);
                }
#ifdef DEBUG
                qDebug() << "summa =" << summa;
#endif
                if(qAbs(summa) <= m_absScatter) {
                    gen(--phase);
                    ++phase;
                } else {
                    summa = 0;
                    m_sequence[m_seqSize - phase - 1] = 0;
                    m_sequence[phase] = 0;
#ifdef DEBUG
                    qDebug() << "Wrong branch!";
#endif
                }
            }
        } else {
            for(int combIndex = 0; combIndex < m_combSize; combIndex += 2) {
                m_sequence[m_seqSize - phase - 1] = m_combs[combIndex];
                m_sequence[phase] = m_combs[combIndex + 1];
#ifdef DEBUG
                qDebug() << "level:" << m_seqSize - phase;
                qDebug() << "combinations(" << m_combs[combIndex] << "," << m_combs[combIndex + 1] << ")";
                qDebug() << "combIndex =" << combIndex;
#endif
                for(int index = 0; index < m_seqSize - phase; ++index) {
                    summa += m_sequence.at(index)*m_sequence.at(index + phase);
                }
#ifdef DEBUG
                qDebug() << "summa =" << summa;
#endif
                if(qAbs(summa) <= m_absScatter) {
                    gen(--phase);
                    ++phase;
                } else {
                    summa = 0;
                    m_sequence[m_seqSize - phase - 1] = 0;
                    m_sequence[phase] = 0;
#ifdef DEBUG
                    qDebug() << "Wrong branch!";
#endif
                }
            }
        }
    } else {
        if((m_isFiltered && filter()) || !m_isFiltered) {
#ifdef DEBUG
            qDebug() << "emit sequenceGenerated(" << m_sequence << ")";
#endif
            emit sequenceGenerated(m_sequence);
            m_sequences.append(m_sequence);
        }

    }
}

bool Generator::filter()
{
    int summa = 0;

    for(int phase = 1; phase < ((m_seqSize & 1) ? (m_seqSize - 1)/2 : m_seqSize/2); ++phase) {
        for(int index = 0; index < m_seqSize - phase; ++index) {
            summa += m_sequence.at(index)*m_sequence.at(index + phase);
        }
#ifdef DEBUG
        qDebug() << "bool Generator::filter():" << (qAbs(summa) <= m_absMaxScatter);
        qDebug() << "summa =" << summa;
#endif
        if(qAbs(summa) > m_absMaxScatter) {
            return false;
        }
        summa = 0;
    }

    return true;
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
