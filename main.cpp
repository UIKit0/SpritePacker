#include "precompiled.h"

#include "folder.h"

#include "resourcefactory.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString appExeName = QFileInfo(QApplication::applicationFilePath()).fileName();
    if (argc < 2) {
        qDebug("Usage:");
        qDebug("\t%s <input_directory>", appExeName.toUtf8().constData());
        return 1;
    }

    QDir output(argv[1]);
    output.mkdir(".package");
    output.cd(".package");
    qDebug("\nOutput directory: %s\n", output.absolutePath().toUtf8().constData());

    ResourceFactory factory;
    Folder *folder = factory.loadFolder(argv[1]);

    folder->process(output.absolutePath(), true);

    return 0; // a.exec();
}
