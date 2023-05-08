#ifndef DRAWINGINTERFACE_HPP
#define DRAWINGINTERFACE_HPP

#include "genetic/Genotype.hpp"
class IDrawer
{
public:
    virtual void drawImage(Genotype genotype) = 0;

private:
};

#endif // DRAWINGINTERFACE_HPP
