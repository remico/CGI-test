#ifndef FILEITEM
#define FILEITEM

#include <QString>

struct FileItem {
    QString name;
    int contentLen;
    int contentPos;
};

#endif // FILEITEM

