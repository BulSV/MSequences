#include "Generator.h"
#include <QtMath>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

#ifdef DEBUG
#include <QDebug>
#endif

Generator::Generator(const int &seqSize,
                     const int &terminalSideLobes,
                     bool isFiltered,
                     const int &closeCentralSideLobes,
                     bool isBalanced,
                     const int &disbalance,
                     QObject *parent) :
    QObject(parent)
  , m_isFiltered(isFiltered)
  , m_progressBar("[ ]")
  , m_progress(0)
  , m_isBalanced(isBalanced)
{
    setSequenceSize(seqSize);
    setCloseCentralSideLobes(closeCentralSideLobes);
    setTerminalSideLobes(terminalSideLobes);
    setDisbalance(disbalance);
    fillCombinations();
}

Generator::~Generator()
{
    delete[] m_combs;
    delete[] m_combsEvenSimplified;
    delete[] m_combsOddSimplified;
}

void Generator::setCloseCentralSideLobes(const int &closeCentralSideLobes)
{
    if(qAbs(closeCentralSideLobes)) {
        m_closeCentralSideLobes = qAbs(closeCentralSideLobes);
    } else {
        qErrnoWarning("WARNING! Close-central side lobes must be equal or greater than 1");
        qErrnoWarning("Close-central side lobes set to 1");
        m_closeCentralSideLobes = 1;
    }
}

void Generator::setTerminalSideLobes(const int &absMaxScatter)
{
    if(qAbs(absMaxScatter)) {
        m_terminalSideLobes = absMaxScatter;
    } else {
        qErrnoWarning("WARNING! Terminal side lobes must be equal or greater than 1");
        qErrnoWarning("Terminal side lobes set to 1");
        m_terminalSideLobes = 1;
    }
}

void Generator::setFiltered(const bool &isFiltered)
{
    m_isFiltered = isFiltered;
}

bool Generator::isFiltered() const
{
    return m_isFiltered;
}

void Generator::setBalanced(const bool &isBalanced)
{
    m_isBalanced = isBalanced;
}

bool Generator::isBalanced() const
{
    return m_isBalanced;
}

void Generator::setDisbalance(const int &disbalance)
{
    if(disbalance >= 0) {
        m_disbalance = disbalance;
    } else {
        m_disbalance = 0;
    }
}

int Generator::disbalanse() const
{
    return m_disbalance;
}

int Generator::getCloseCentralSideLobes() const
{
    return m_closeCentralSideLobes;
}

int Generator::getTerminalSideLobes() const
{
    return m_terminalSideLobes;
}

void Generator::setSequenceSize(const int &seqSize)
{
    if(qAbs(seqSize) > 1) {
        m_seqSize = qAbs(seqSize);
    } else {
        qErrnoWarning("WARNING! Size of sequences must be equal or greater than 2");
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
    QVector<int> sequence;
    QVector<QFuture<void> > fs;

    sequence.fill(0, m_seqSize);
    if(!isOddSeqSize()) {
        sequence[m_seqSize - phase - 1] = -1;
        sequence[phase] = -1;
        --phase;
        for(int combIndex = 0; combIndex < m_combEvenSizeSimplified; combIndex += 2) {
            sequence[m_seqSize - phase - 1] = m_combsEvenSimplified[combIndex];
            sequence[phase] = m_combsEvenSimplified[combIndex + 1];
            m_tempSequences.append(sequence);
        }

        for(int i = 0; i < m_combEvenSizeSimplified/2; ++i) {
            fs.append(QtConcurrent::run(this, &Generator::gen, phase - 1, m_tempSequences[i], true));
        }

        for(int i = 0; i < m_combEvenSizeSimplified/2; ++i) {
            fs[i].waitForFinished();
        }
    } else {
        for(int combIndex = 0; combIndex < m_combOddSizeSimplified; combIndex += 2) {
            sequence[m_seqSize - phase - 1] = m_combsOddSimplified[combIndex];
            sequence[phase] = m_combsOddSimplified[combIndex + 1];
            m_tempSequences.append(sequence);
        }

        for(int i = 0; i < m_combOddSizeSimplified/2; ++i) {
            fs.append(QtConcurrent::run(this, &Generator::gen, phase - 1, m_tempSequences[i], true));
        }

        for(int i = 0; i < m_combOddSizeSimplified/2; ++i) {
            fs[i].waitForFinished();
        }
    }
}

void Generator::gen(int phase, QVector<int> &seq, bool isSimplified)
{
    int summa = 0;

    if(phase >= phaseLimit()
            && ((!isOddSeqSize() && phase < m_seqSize - 2)
                || (isOddSeqSize() && phase < m_seqSize - 1))) {
        if(isOddSeqSize() && (phase == phaseLimit())) {
            for(int combIndex = 0; combIndex < 2; ++combIndex) {
                seq[phase] = qPow(-1, combIndex + 1);

                for(int index = 0; index < m_seqSize - phase; ++index) {
                    summa += seq.at(index)*seq.at(index + phase);
                }

                if(qAbs(summa) <= m_terminalSideLobes) {
                    gen(phase - 1, seq, isSimplified);
                } else {
                    seq[phase] = 0;
                }
                summa = 0;
            }
        } else if(isSimplified && !isOddSeqSize() && !((seq.at(m_seqSize - phase - 2))^(seq.at(phase + 1)))) {
                for(int combIndex = 0; combIndex < m_combEvenSizeSimplified; combIndex += 2) {
                    seq[m_seqSize - phase - 1] = m_combsEvenSimplified[combIndex];
                    seq[phase] = m_combsEvenSimplified[combIndex + 1];

                    for(int index = 0; index < m_seqSize - phase; ++index) {
                        summa += seq.at(index)*seq.at(index + phase);
                    }

                    if(qAbs(summa) <= m_terminalSideLobes) {
                        gen(phase - 1, seq, isSimplified);
                    } else {
                        seq[m_seqSize - phase - 1] = 0;
                        seq[phase] = 0;
                    }
                    summa = 0;
                }
            } else if(isSimplified && isOddSeqSize() && !((seq.at(m_seqSize - phase - 1))^(seq.at(phase)))) {
                for(int combIndex = 0; combIndex < m_combOddSizeSimplified; combIndex += 2) {
                    seq[m_seqSize - phase - 1] = m_combsOddSimplified[combIndex];
                    seq[phase] = m_combsOddSimplified[combIndex + 1];

                    for(int index = 0; index < m_seqSize - phase; ++index) {
                        summa += seq.at(index)*seq.at(index + phase);
                    }

                    if(qAbs(summa) <= m_terminalSideLobes) {
                        gen(phase - 1, seq, isSimplified);
                    } else {
                        seq[m_seqSize - phase - 1] = 0;
                        seq[phase] = 0;
                    }
                    summa = 0;
                }
            } else {
            isSimplified = false;
            for(int combIndex = 0; combIndex < m_combSize; combIndex += 2) {
                seq[m_seqSize - phase - 1] = m_combs[combIndex];
                seq[phase] = m_combs[combIndex + 1];

                for(int index = 0; index < m_seqSize - phase; ++index) {
                    summa += seq.at(index)*seq.at(index + phase);
                }

                if(qAbs(summa) <= m_terminalSideLobes) {
                    gen(phase - 1, seq, isSimplified);
                } else {
                    seq[m_seqSize - phase - 1] = 0;
                    seq[phase] = 0;
                }
                summa = 0;
            }
        }
    } else if((m_isFiltered && filter(seq)) || !m_isFiltered) {
        if( (m_isBalanced && balance(seq)) || !m_isBalanced) {
            QMutexLocker locker(&m_mutex); // ? need or not
            emit sequenceGenerated(seq);
            m_sequences.append(seq);
        }
    }
}

int Generator::phaseLimit()
{
    return (isOddSeqSize() ? (m_seqSize - 1)/2 : m_seqSize/2);
}

bool Generator::isOddSeqSize()
{
    return (m_seqSize & 1);
}

bool Generator::filter(const QVector<int> &seq)
{
    int summa = 0;

    for(int phase = 1; phase < ((m_seqSize & 1) ? (m_seqSize - 1)/2 : m_seqSize/2); ++phase) {
        for(int index = 0; index < m_seqSize - phase; ++index) {
            summa += seq.at(index)*seq.at(index + phase);
        }
#ifdef DEBUG
        qDebug() << "[!]*****bool Generator::filter():" << (qAbs(summa) <= m_closeCentralSideLobes);
        qDebug() << "[!]*****summa =" << summa;
        qDebug() << "[!]*****bool Generator::filter() | phase:" << phase;
#endif
        if(qAbs(summa) > m_closeCentralSideLobes) {
            return false;
        }
        summa = 0;
    }

    return true;
}

bool Generator::balance(const QVector<int> &seq)
{
    int numZerros = 0;

    for(int i = 0; i < seq.size(); ++i) {
        if(seq.at(i) == -1) {
            ++numZerros;
        }
    }

    if(qAbs(2*numZerros - seq.size()) <= m_disbalance) {
        return true;
    } else {
        return false;
    }
}

QVector<int> Generator::mirrorSeq(const QVector<int> &seq)
{
    QVector<int> res;

    for(int i = 0; i < seq.size(); ++i) {
        seq.at(i) == 1 ? res.append(-1) : res.append(1);
    }

    return res;
}

QVector<int> Generator::reverseSeq(const QVector<int> &seq)
{
    QVector<int> res;

    for(int i = seq.size() - 1; i > -1; --i) {
        res.append(seq.at(i));
    }

    return res;
}

QVector<int> Generator::phaseOffsetSeq(const QVector<int> &seq)
{
    QVector<int> res;

    for(int i = 0; i < seq.size(); ++i) {
        if(i % 2) {
            res.append(-seq.at(i));
        } else {
            res.append(seq.at(i));
        }
    }

    return res;
}

QVector<QVector<int> > Generator::getSequences() const
{
    return m_sequences;
}

QVector<QVector<int> > Generator::combinations(const QVector<int> &seq)
{
    QVector<QVector<int> > seqs;

    seqs.append(mirrorSeq(seq));
    seqs.append(reverseSeq(seq));
    seqs.append(reverseSeq(mirrorSeq(seq)));
    seqs.append(phaseOffsetSeq(seq));
    seqs.append(phaseOffsetSeq(mirrorSeq(seq)));
    seqs.append(phaseOffsetSeq(reverseSeq(seq)));
    seqs.append(phaseOffsetSeq(reverseSeq(mirrorSeq(seq))));

    return seqs;
}

void Generator::fillCombinations()
{
    int v[] = {-1, -1, -1, 1, 1, -1, 1, 1};
    int vEvenSimple[] = {-1, -1, -1, 1, 1, 1};
    int vOddSimple[] = {-1, -1, -1, 1, 1, -1};
    m_combSize = 8;
    m_combEvenSizeSimplified = 6;
    m_combOddSizeSimplified = 6;
    m_combs = new int[m_combSize];
    m_combsEvenSimplified = new int[m_combEvenSizeSimplified];
    m_combsOddSimplified = new int[m_combOddSizeSimplified];

    for(int i = 0; i < m_combSize; ++i) {
        m_combs[i] = v[i];
    }

    for(int i = 0; i < m_combEvenSizeSimplified; ++i) {
        m_combsEvenSimplified[i] = vEvenSimple[i];
    }

    for(int i = 0; i < m_combOddSizeSimplified; ++i) {
        m_combsOddSimplified[i] = vOddSimple[i];
    }
}
