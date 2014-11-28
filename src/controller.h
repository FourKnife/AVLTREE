/*!
 * \file Controller.h
 * \brief class Controller
 *
 * \author pb
 * \version 0.0.1
 * \date 2014/11/23
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QString>

class Controller
{
public:
    /*!
     * \brief create a Controller
     * \param article's Path, dict's type
     * \return
     */
    Controller(QString filePath,int type);

    /*!
     * \brief when you got an article and want to encrypt it,use this function.
     * \param
     * \return the filePath of ciphertext
     */
    QString encrypt();

    /*!
     * \brief when you want to convert a ciphertext to originalFile ,use this
     * \return the filePath of originFilePath which is convert from ciphertext
     */
    //QString unencrypt();

    /*!
     * \brief if you want to change the type of dict,use it.
     * \param newType
     */
    void modifyType(int newType);

private:
    int type;
    QString originFilePath;

};

#endif // CONTROLLER_H
