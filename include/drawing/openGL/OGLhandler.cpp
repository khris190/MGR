#include "OGLhandler.hpp"

OGLhandler* OGLhandler::getInstance()
{
    if (instance_ == nullptr) {
        instance_ = new OGLhandler();
    }
    return instance_;
}
void OGLhandler::initOGL() { }

OGLhandler::~OGLhandler() { }
OGLhandler* OGLhandler::instance_;
