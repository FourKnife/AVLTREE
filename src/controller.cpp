#include "controller.h"
#include "dictionary.h"
#include "heap.h"
#include "avltree.h"

Controller::Controller(QString filePath,int type)
{
    this->originFilePath = filePath;
    this->type = type;
}
void Controller::modifyType(int newType)
{
    this->type = newType;
}
QString Controller::encrypt()
{
    QString cipherTextPath;
    QString pathForHeap;
    QString U2FilePath;
    Dictionary dict = new Dictionary(originFilePath,type);
    if(!dict.buildDictionary())
    {
        cipherTextPath = NULL;
        return cipherTextPath;
    }
    else
    {
        pathForHeap = dict.toHeap();            //获得堆所需使用的文件的路径
        Heap heap = new Heap(pathForHeap,type);
        if(!heap.buildHeap())
        {
            cipherTextPath = NULL;
            return cipherTextPath;
        }
        else
        {
            U2FilePath = heap.getU2FilePath();  //此处为伪代码，用于获取保存了‘01’的U2文件路径（heap没有此接口）。
            Avltree tree = new Avltree(U2FilePath);
            if(!tree.buildAvltree())
            {
                cipherTextPath = NULL;
                return cipherTextPath;
            }
            else
            {
                cipherTextPath = tree.getU3FilePath();  //伪码，用于获取经AVL树重排01后的U3的文件路径，返回给界面。
                return cipherTextPath;
            }
        }
    }
}
/*
QString Controller::unencrypt()
{
}
*/
