#ifndef PAGEMAKER_H
#define PAGEMAKER_H

#include <QString>

class PageMaker
{
public:
    PageMaker(const QString &appname);
    virtual ~PageMaker() {}

    QString appName() const;

    void addHeader_ContentType(const QString &mime);
    void addHeader_ContentDisposition(const QString &filename);
    void addHeader_ContentDescription(const QString &description);
    void addHeader_ContentLength(int len);

    void addEmptyString();
    void beginHtmlPage(const QString &title = QString());
    void endHtmlPage();

    virtual void addPageContent(const QString &content);
    virtual QString getResult() const;

private:
    QString m_appName;
    QString m_page;
};

#endif // PAGEMAKER_H
