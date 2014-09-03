#ifndef GIFRESOURCE_H
#define GIFRESOURCE_H

#include "resource.h"
#include <QMovie>

class GifResource : public Resource
{
public:
    GifResource(QString name);
    ~GifResource();

    bool load(QString path);

    virtual int frameCount() const;
    virtual QRect frameRect() const;
    virtual QImage frameImage(int frame) const;
    virtual bool isValid() const;

    void process(QString path);

private:

    QMovie *m_movie;
};

#endif // GIFRESOURCE_H
