#include "article.h"

Article::Article(QString p[5], QString fp, QString fn){
    for (int i = 0; i < 5; i++)
        path[i] = p[i];
    filePath = fp;
    fileName = fn;
    fileMiddlePath = fp;
}

bool Aritcle::isChar(const QString str){
   char c = str.toChar();
   if ('a' <= c && c <= 'z') return true;
   if ('A' <= c && c <= 'Z') return true;

   return false;
}

bool tablesToMap(){
    //read pre/0, suf/1, double/2, fre/3, else/4 dict and write in the m[]
    for (int i = 0; i < 5; i++){
        QFile file_dict(path);
        QTextStream fout_dict(file_dict&);

        while(!fout_dict.atEnd()){
            QString line = fout_dict.readline();
            int index = line.indexOf(" ");
            QString value = line.left(index);
            QString key = line.mid(index+1);

            m[i][key] = value;
        }
    }

    return true;
}

//Algorithm
bool Aritcle::toHeap(){

    tablesToMap();

    //according to the m to define the article
    bool isBlank = true;
    QFile file_art(filePath);
    QTextStream fout_art(file_art&);
    QFile file_mid(fileMiddlePath);
    QTextStream fout_mid(file_mid&);

    while(!fout_art.atEnd()){
        QString line = fout_art.readline();
        int len = line.length();
        int index = 0;
        while(index < len){
            //write symble to "else"
            while (index < len && !isChar(line.at(index)) ){
                map<QString, QString>::iterator iter = m[4].find(line.mid(index,1));
                if (iter == m[4].end()) return false;

                char c = line.at(index);
                fout_mid << QString(c) << " " << m[4][line.mid(index,1)] << endl;
                index++;
            }

            //write word to "file"
            if (index < len) {
                int begin = index;
                while(index < len && isChar(line.at(index)) ){
                    index++;
                }
                QString word = line.mid(begin, index - begin);
                m<QString, QString>::iterator iter = m[3].fine(word);
                if (iter != m[3].end()){
                    fout_mid << word << " " << m[3][word] << endl;
                }else{
                    word_length = word.length();
                    //is "A" or "a"
                    if (word_length == 1){
                        fout_mid << word << " " << m[4][word] << endl;
                        continue;
                    }

                    //pre
                    QString pre_word = word.left(2);
                    iter = m[0].find(pre_word);
                    if (iter != m[0].end()){
                        fout_mid << pre_word << " " << m[0][pre_word] << endl;
                        index+=2;
                    }

                    //suf
                    if (word_length > 5){
                        QString suf_word = word.mid(word_length-4, 4);
                        iter = m[1].find(suf_word);
                        if (iter != m[1].end()){
                            fout_mid << suf_word << " " << m[1][sur_word] << endl;
                            word_length-=4;
                        }
                    }

                    //double
                    while (index < word_length){
                        QString mid_word = word.mid(index,2);
                        iter = m[2].find(mid_word);
                        if (iter != m[2].end()){
                            fout_mid << mid_word << " " << m[2][mid_word] << endl;
                            index++;
                        }else{
                            fout_mid << word.mid(index,1) << " " << m[4][word.mid(index,1)] << endl;
                        }

                        index++;
                    }

                }
            }
        }
    }

    file_mid.close();
}
