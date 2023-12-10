#ifndef ABSTRACTSELECTOR_HPP
#define ABSTRACTSELECTOR_HPP

class AbstractSelector {
public:
    AbstractSelector() = default;
    AbstractSelector(AbstractSelector&&) = delete;
    AbstractSelector(const AbstractSelector&) = delete;
    AbstractSelector& operator=(AbstractSelector&&) = delete;
    AbstractSelector& operator=(const AbstractSelector&) = delete;
    ~AbstractSelector() = default;
};

#endif // ABSTRACTSELECTOR_HPP
