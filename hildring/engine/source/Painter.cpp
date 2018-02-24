#include "Painter.h"

Painter::Painter(std::function<void()> paintFunc)
    : m_paintFunc(paintFunc)
{

}

void Painter::paint() {
    if (m_paintFunc) {
        m_paintFunc();
    }
}

