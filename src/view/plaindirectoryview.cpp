#include "plaindirectoryview.h"

PlainDirectoryView::PlainDirectoryView(Directory *pDir)
    : DirectoryView(pDir)
{}

QString PlainDirectoryView::makeHtmlPage(PageMaker *pPagemaker) const
{
    QString linktag("<a href=\"%1?arc=%2\">%2</a>");
    QString linkslist;

    foreach (QString s, m_pDir->getArchivesList()) {
        linkslist.append(linktag.arg(pPagemaker->appName(), s)).append("<br>");
    }

    pPagemaker->addHeader_ContentType("text/html");
    pPagemaker->beginHtmlPage("CGI: page 1");
    pPagemaker->addPageContent("<h2>List of archives:</h2>");
    pPagemaker->addPageContent(linkslist);
    pPagemaker->endHtmlPage();

    return pPagemaker->getResult();
}

