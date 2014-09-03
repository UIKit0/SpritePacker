#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include "folder.h"
#include "compoundresource.h"
#include "resource.h"

class ResourceFactory
{
public:
    ResourceFactory();

    Folder *loadFolder(QString path);
    CompoundResource *loadCompound(QString path);
    Resource *loadResource(QString path);
    Resource *loadResource(QFileInfo file);

    Resource *loadGif(QString path);
    Resource *loadSequence(QString path);
    Resource *loadImage(QString path);

private:

    void loadFolder(QString path, Folder *parent);
};

#endif // RESOURCEFACTORY_H
