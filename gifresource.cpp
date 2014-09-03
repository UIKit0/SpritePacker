#include "precompiled.h"

#include "compoundresource.h"
#include "gifresource.h"

GifResource::GifResource(QString name) :
    Resource(name),
    m_movie(NULL)
{
}

GifResource::~GifResource()
{
    delete m_movie;
}

bool GifResource::load(QString path)
{
    if (m_movie) {
        delete m_movie;
        m_movie = NULL;
    }
    m_movie = new QMovie(path);
    if (m_movie->isValid()) {
        m_movie->jumpToFrame(0);
        return true;
    }
    return false;
}

int GifResource::frameCount() const
{
    if (!isValid()) {
        return -1;
    }
    return m_movie->frameCount();
}

QRect GifResource::frameRect() const
{
    if (!isValid()) {
        return QRect();
    }

    return m_movie->frameRect();
}

bool GifResource::isValid() const
{
    if (m_movie == NULL) {
        return false;
    }
    return m_movie->isValid();
}

QImage GifResource::frameImage(int frame) const
{
    if (m_movie == NULL || frame < 0 || frame >= frameCount()) {
        return QImage();
    }

    m_movie->jumpToFrame(frame);
    return m_movie->currentImage();
}

void GifResource::process(QString path)
{
    CompoundResource c(name());
    c.add(this);
    c.process(path);
}
