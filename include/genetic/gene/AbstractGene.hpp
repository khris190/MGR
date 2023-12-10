#ifndef ABSTRACTGENE_HPP
#define ABSTRACTGENE_HPP

class AbstractGene {
public:
    AbstractGene() = default;
    AbstractGene(AbstractGene&&) = default;
    AbstractGene(const AbstractGene&) = default;
    AbstractGene& operator=(AbstractGene&&) = default;
    AbstractGene& operator=(const AbstractGene&) = default;
    virtual ~AbstractGene() = default;

    virtual void mutate(float mutationRate = 0.001f) = 0;
};

#endif // ABSTRACTGENE_HPP
