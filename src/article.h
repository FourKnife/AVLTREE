/*!
 * \file article.h
 * \brief class Article
 *
 * \author dr
 * \version 0.0.1
 * \date 2014/11/20
 */
#ifndef ARTICLE_H
#define ARTICLE_H
/// \brief none
#include <QString>
#include <map>
#include <vector>
#include <QFile>
#include <iostream>
using namespace std;

class Article
{
public:
    /*!
     * \brief Article construction function
     * \param p[5]: five tables paths(pre,suf,double, frequent,else)
     * \param filePath: the article'path
     * \param fileName: the article'name
     */
    Article(QString p[5], QString filePath, QString fileName);
    /*!
     * \brief toHeap, make the article to Binary
     * \return is success or not
     */
    bool toHeap();
    /*!
     * \brief isChar, make sure the char is a..z or A..z ot not.
     * \param str, the char
     * \return if char is a..z or A..Z  then return true else false
     */
    bool isChar(const QString str);
    /*!
     * \brief tablesToMap put five tables into m[5].
     * \return if success return true;
     */
    bool tablesToMap();
private:
    QString path[5]; //prePath,sufPath,douPath,frePath,else
    QString filePath;
    QString fileName;
    QString fileMiddlePath;
    /*!
     * \brief put five tables into m[5].
     */
    map<string, string> m[5];
};

#endif // ARTICLE_H
