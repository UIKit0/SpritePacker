#include "precompiled.h"

#include "resource.h"
#include "gifresource.h"
#include "resourcefactory.h"

static const char* DEBUG_TYPE_FOLDER    = "Folder  ";
static const char* DEBUG_TYPE_COMPOUND  = "Compound";
static const char* DEBUG_TYPE_GIF       = "GIF     ";
static const char* DEBUG_TYPE_SEQUENCE  = "Sequence";
static const char* DEBUG_TYPE_IMAGE     = "Image   ";

ResourceFactory::ResourceFactory()
{
}

Folder *ResourceFactory::loadFolder(QString path)
{
    Folder *folder = new Folder("root");
    loadFolder(path, folder);
    return folder;
}

CompoundResource *ResourceFactory::loadCompound(QString path)
{
    CompoundResource *compound = new CompoundResource(QFileInfo(path).baseName());
    qDebug() << DEBUG_TYPE_COMPOUND << " " << compound->name();

    QDir dir(path);

    QStringList filters;
    filters << "*.sequence" << "*.gif" << "*.png";

    QFileInfoList entries = dir.entryInfoList(filters, QDir::Files | QDir::Dirs | QDir::Readable, QDir::Name);
    foreach (QFileInfo info, entries) {
        compound->add(loadResource(info));
    }

    return compound;
}

Resource *ResourceFactory::loadResource(QString path)
{
    return loadResource(QFileInfo(path));
}

Resource *ResourceFactory::loadResource(QFileInfo info)
{
    Resource *resource = NULL;

    QString suffix = info.completeSuffix();
    if (info.isDir() && suffix == "sequence") {
        resource = loadSequence(info.absoluteFilePath());
    } else {
        if (suffix == "gif") {
            resource = loadGif(info.absoluteFilePath());
        } else if (suffix == "png") {
            resource = loadImage(info.absoluteFilePath());
        }
    }

    return resource;
}

Resource *ResourceFactory::loadGif(QString path)
{
    GifResource *res = new GifResource(QFileInfo(path).baseName());
    qDebug() << DEBUG_TYPE_GIF << " " << res->name();
    if (res->load(path)) {
        return res;
    }
    delete res;
    return NULL;
}

Resource *ResourceFactory::loadSequence(QString path)
{
    return NULL;
}

Resource *ResourceFactory::loadImage(QString path)
{
    return NULL;
}

void ResourceFactory::loadFolder(QString path, Folder *parent)
{
    qDebug() << DEBUG_TYPE_FOLDER << " " << QFileInfo(path).baseName();

    QDir dir(path);

    QStringList filters;
    filters << "*.gif" << "*.png";

    QFileInfoList entries = dir.entryInfoList(filters, QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files | QDir::Readable, QDir::Name);
    foreach (QFileInfo info, entries) {
        if (info.isDir()) {
            if (info.fileName()[0] != '.') {
                if (info.completeSuffix() == "compound") {
                    CompoundResource *childCompound = loadCompound(info.absoluteFilePath());
                    parent->add(childCompound);
                } else {
                    Folder *childFolder = new Folder(info.baseName());
                    parent->add(childFolder);
                    loadFolder(info.absoluteFilePath(), childFolder);
                }
            }
        } else {
            Resource *childResource = loadResource(info);
            parent->add(childResource);
        }
    }
}
