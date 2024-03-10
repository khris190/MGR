#ifndef DRAWINGINTERFACE_HPP
#define DRAWINGINTERFACE_HPP

#include "genetic/Genotype.hpp"
class AbstractDrawer {
public:
    AbstractDrawer(Genotype& individual);
    AbstractDrawer(AbstractDrawer&&) = default;
    AbstractDrawer(const AbstractDrawer&) = default;
    AbstractDrawer& operator=(AbstractDrawer&&) = default;
    AbstractDrawer& operator=(const AbstractDrawer&) = default;
    ~AbstractDrawer();
    // virtual void drawImage(Genotype genotype) = 0;

private:
};

#endif // DRAWINGINTERFACE_HPP
