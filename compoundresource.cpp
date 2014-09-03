#include "precompiled.h"

#include "resource.h"
#include <QTextStream>

#include "compoundresource.h"

CompoundResource::CompoundResource(QString name) :
    Item(name),
    m_per_row(4),
    m_frame_count(0),
    m_new_line_per_resource(true)
{
}

CompoundResource::~CompoundResource()
{
    foreach (Resource *resource, m_resources) {
        delete resource;
    }
    m_resources.clear();
}

void CompoundResource::add(Resource *resource)
{
    if (!resource || !resource->isValid()) {
        qWarning("Resource is not valid.");
        return;
    }
    m_resources.append(resource);
    m_frame_count += resource->frameCount();
}

void CompoundResource::process(QString path)
{
    int rows = (m_frame_count + (m_per_row-1)) / m_per_row;

    rows = 0;
    foreach (Resource *resource, m_resources) {
        rows += (resource->frameCount() + (m_per_row-1)) / m_per_row;
        if ((resource->frameCount() % m_per_row) != 0) {
            rows++;
        }
    }

//    if (m_new_line_per_resource) {
//        rows += m_resources.size()-1;
//    }

    QRect frame_rect = m_resources.first()->frameRect();
    QSize frame_size = frame_rect.size();

    QImage texture(QSize(m_per_row * frame_size.width(), rows * frame_size.height()), QImage::Format_ARGB32);
    texture.fill(Qt::transparent);

    QPainter painter(&texture);
    // painter.fillRect(texture.rect(), Qt::transparent);

    int x = 0;
    int y = 0;
    foreach (Resource *resource, m_resources) {
        for (int i = 0; i < resource->frameCount(); i++) {
            painter.drawImage(x * frame_size.width(), y * frame_size.height(), resource->frameImage(i));
            x++;
            if (x == m_per_row) {
                x = 0;
                y++;
            }
        }

        if (m_new_line_per_resource && x > 0) {
            x = 0;
            y++;
        }
    }

    texture.save(path + '/' + name() + ".png");
    generateInfo(path + '/' + name() + ".txt");
}

void CompoundResource::generateInfo(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QFile::Truncate)) {
        qWarning("Cannot open file %s for writing.", path.toUtf8().constData());
    }

    QRect frame_rect = m_resources.first()->frameRect();
    QSize frame_size = frame_rect.size();

    QTextStream stream(&file);
    stream << "FrameSize " << frame_size.width() << "x" << frame_size.height();
}
