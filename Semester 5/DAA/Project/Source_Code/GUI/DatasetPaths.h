#ifndef DATASETPATHS_H
#define DATASETPATHS_H

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QStringList>

// Finds datasets/<subfolder> no matter which folder the program was started from.
inline QString datasetFolder(const QString &subfolder)
{
    const QStringList starts = {
        QDir::currentPath(),
        QCoreApplication::applicationDirPath()
    };

    for (const QString &start : starts)
    {
        QDir dir(start);

        for (int level = 0; level < 6; ++level)
        {
            QString candidate =
                dir.filePath("datasets/" + subfolder);

            if (QFileInfo(candidate).isDir())
                return candidate;

            if (!dir.cdUp())
                break;
        }
    }

    return "datasets/" + subfolder;
}

#endif