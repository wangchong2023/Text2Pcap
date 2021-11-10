#include "fileutils.h"
#include "Common/common_header.h"

FileUtils::FileUtils(QObject *parent) : QObject(parent)
{

}

QString FileUtils::GetRootDirByAppPath(QString appPath) {
#ifdef Q_OS_OSX
    return FileUtilsMacOS::GetRootDirByAppPath(appPath);
#elif defined Q_OS_WIN
    return FileUtilsWin::GetRootDirByAppPath(appPath);
#endif
}

QString FileUtils::GetSubAppPathByRootAndSubName(QString rootDir, QString subAppName) {
#ifdef Q_OS_OSX
    return FileUtilsMacOS::GetSubAppPathByRootAndSubName(rootDir, subAppName);
#elif defined Q_OS_WIN
    return FileUtilsWin::GetSubAppPathByRootAndSubName(rootDir, subAppName);
#endif
}

QString FileUtils::GetSubAppPathByAppAndSubName(QString appPath, QString subAppName) {
#ifdef Q_OS_OSX
    return FileUtilsMacOS::GetSubAppPathByAppAndSubName(appPath, subAppName);
#elif defined Q_OS_WIN
    return FileUtilsWin::GetSubAppPathByAppAndSubName(appPath, subAppName);
#endif
}

bool FileUtils::isFile(QString filePath) {
    if (filePath.isNull() || filePath.isEmpty()) {
        return false;
    }

    QFileInfo fileInfo(filePath);
    return fileInfo.isFile();
}
bool FileUtils::isDir(QString dirPath) {
    if (dirPath.isNull() || dirPath.isEmpty()) {
        return false;
    }

    QFileInfo fileInfo(dirPath);
    return fileInfo.isDir();
}

bool FileUtils::isFileExist(QString appPath) {
    if (appPath.isNull() || appPath.isEmpty()) {
        return false;
    }

    QFile file(appPath);
    return file.exists();
}

bool FileUtils::isDirExist(QString dirPath) {
    return isFileExist(dirPath);
}

QString FileUtils::getAppNameByPath(QString appPath) {
    if (appPath.isNull() || appPath.isEmpty()) {
        return STRING_EMPTY;
    }
    QFileInfo fileInfo(appPath);
    return fileInfo.fileName();
}

QString FileUtils::getAppCanonicalByPath(QString appPath) {
    if (appPath.isNull() || appPath.isEmpty()) {
        return STRING_EMPTY;
    }

    QFileInfo fileInfo(appPath);
    return fileInfo.canonicalFilePath();
}

QString FileUtils::getAppSuffixByPath(QString appPath) {
    if (appPath.isNull() || appPath.isEmpty()) {
        return STRING_EMPTY;
    }

    QFileInfo fileInfo(appPath);
    return fileInfo.suffix();
}

QString FileUtils::getAppAbsoluteByPath(QString appPath) {
    if (appPath.isNull() || appPath.isEmpty()) {
        return STRING_EMPTY;
    }

    QFileInfo fileInfo(appPath);
    return fileInfo.absolutePath();
}

void FileUtils::writeText2File(QString textPath, QString text) {
    if ((textPath.isEmpty()) || (textPath.isEmpty())) {
        qWarning("TextPath is empty.");
        return;
    }

    if ((text.isEmpty()) || (text.isEmpty())) {
        qWarning("Text is empty.");
        return;
    }

    QFile file(textPath);
    if (file.open(QFile::WriteOnly | QFile :: Truncate))
    {
        QTextStream out(&file);
        out << text;
    }
    else
    {
        qDebug() << "open file failed";
    }

    file.close();
}

void FileUtils::deleteFile(QString filePath) {
    if ((filePath.isEmpty()) || (filePath.isEmpty())) {
        qWarning("FilePath is empty.");
        return;
    }

    QFile::remove(filePath);
}

uint32_t FileUtils::deleteFilesBySuffix(QString dirPath, QString suffix) {
    if ((dirPath.isEmpty()) || (dirPath.isEmpty())) {
        qWarning("DirPath is empty.");
        return 0;
    }

    QDir dir(dirPath);
    uint32_t fileCount = 0;
    foreach (QFileInfo fileInfo, dir.entryInfoList()){
        if (fileInfo.isFile() && (fileInfo.suffix() == suffix)) {
            dir.remove(fileInfo.fileName());
            fileCount++;
        }
    }

    return fileCount;
}

void FileUtils::deleteDirAndSubFiles(QString dirPath) {
    if ((dirPath.isEmpty()) || (dirPath.isEmpty())) {
        qWarning("DirPath is empty.");
        return;
    }

    QString dirPathString = QString(dirPath);
    QDir dir;
    dir.setPath(dirPathString);
    dir.removeRecursively();
}

