#include <iostream>
#include <QDir>
#include <QRegExp>
#include <QCoreApplication>

#include "packer.h"
#include "pagemaker.h"
#include "directory.h"
#include "directoryview.h"
#include "simplefactory.h"

using namespace std;

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    /* archives' directory should be placed alongside of the webserver's cgi-bin directory */
    QString arcDirPath = app.applicationDirPath() + QDir::separator() + QString("..") + QDir::separator() + ARC_DIR;

    /*
     * Simple helper code to create a test archive.
     * Run the app with 'pack' parameter to create an test non-compressed archive.
     *
     * example:
     *      $ <appname> pack <source_txtfiles_dir> <target_arc_dir>
     */
    if (argc > 1 && qstrlen(argv[1])) {
        const char *param_pack = "pack";
        if (qstrcmp(argv[1], param_pack) || argc != 3) {
            cerr << "Invalid parameters.\n";
            cerr << "Using: " << argv[0] << " " << param_pack << " <source_txtfiles_dir>\n";
            return 0;
        }
        Packer packer(argv[2], arcDirPath);
        packer.setNameFilters(QStringList() << "*.txt");  // to limit possible set of input files
        packer.packFiles("archive_35.nca");   // *.nca => non-compressed archive
        return 0;
    }

    /*
     * Run the application itself
     */
    PageMaker pagemaker(app.applicationName());
    Directory arcDir(arcDirPath);
//    arcDir.setNameFilters(QStringList() << "*.nca");  // see above; for new test archives only
    if (!arcDir.searchArchives())
        return -1;

    ArchiveReader *pArcReader = nullptr;
    ArchiveView *pArcView = nullptr;
    FileView *pFileView = nullptr;
    DirectoryView *pDirView = nullptr;

    try {
        pArcReader = SimpleFactory::instance()->createArchiveReader(&arcDir);
        pArcView = SimpleFactory::instance()->createArchiveView(pArcReader);
        pFileView = SimpleFactory::instance()->createFileView(pArcReader);
        pDirView = SimpleFactory::instance()->createDirectoryView(&arcDir);
    }
    catch (const NonRigisteredTypeError &e) {
        cerr << e.what() << "\nAborted." << endl;
        return -1;
    }

    QString query(getenv("QUERY_STRING"));

    /* show list of archives */
    if (query.trimmed().isEmpty()) {
        cout << pDirView->makeHtmlPage(&pagemaker).toUtf8().constData() << endl;
    }
    /* show archive's content */
    else if (query.startsWith(PARAM_ARC)) {
        QString arcname = query.remove(PARAM_ARC);
        cout << pArcView->makeHtmlPage(&pagemaker, arcname).toUtf8().constData() << endl;
    }
    /* show file's content */
    else if (query.contains(PARAM_FILE_VW)) {
        QStringList params = query.split('&');
        QString filename = params.takeAt(params.indexOf(QRegExp(PARAM_FILE_VW".*"))).remove(PARAM_FILE_VW);
        QString arcname = params.takeAt(params.indexOf(QRegExp(PARAM_ARC".*"))).remove(PARAM_ARC);
        cout << pFileView->makeHtmlPage(&pagemaker, arcname, filename).toUtf8().constData() << endl;
    }
    /* download a file */
    else if (query.contains(PARAM_FILE_DL)) {
        QStringList params = query.split('&');
        QString filename = params.takeAt(params.indexOf(QRegExp(PARAM_FILE_DL".*"))).remove(PARAM_FILE_DL);
        QString arcname = params.takeAt(params.indexOf(QRegExp(PARAM_ARC".*"))).remove(PARAM_ARC);

        QByteArray content = pArcReader->getFileContent(arcname, filename);

        pagemaker.addHeader_ContentDescription("File Transfer");
        pagemaker.addHeader_ContentType("text/plain");
        pagemaker.addHeader_ContentDisposition(filename);
        pagemaker.addHeader_ContentLength(content.size());
        pagemaker.addEmptyString();
        pagemaker.addPageContent(content);

        cout << pagemaker.getResult().toUtf8().constData() << endl;
    }

    /* cleanup */
    delete pDirView;
    delete pFileView;
    delete pArcView;
    delete pArcReader;

    return 0;
}

