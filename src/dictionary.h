/*!
 * \file dictionary.h
 * \brief class Dictionary
 *
 * \author lfl
 * \version 0.0.1
 * \date 2014/11/20
 */
#ifndef Dictionary_H
#define Dictionary_H

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <QString>
#include <QFile>

using namespace std;
/// \brief make a dictionary
class Dictionary
{
public:
    /*!
     * \brief Constraction
     */
    Dictionary();

    /*!
     * \brief Dictionary
     * \param the path of the dictionary
     * \return path?
     */
    QString build_dictionary(QString);
private:
    ///¸÷´ÊµäÉú³ÉÊý¾Ý
    const int qualified_line = 8;///ÖØ¸´¼¸¸öÒÔÉÏËãÊÇ¸ßÆµ
    const int prefix_num = 2;///Ç°×º½ØÈ¡³¤¶È
    const int middle_num = 2;///double×Ö½ØÈ¡³¤¶È
    const int suffix_num = 4;///ºó×º½ØÈ¡³¤¶È

    ///±£´æ¸÷´ÊÓ³ÉäÊýÖµ
    map<int,string> mapping[4];
    ///±£´æµ¥´Ê
    vector<string> words;

    ///¶ÁÈëÎÄ¼þ£¬³éÀë´Ê¡¢×Ö
    bool read_file_to_words(string);
    void deal_line(string);
    bool judge_letter(char);

    ///Éú³É´Êµä
    bool generate_dictionary_to_mapping();
    void generate_high_frequency_words();
    void generate_prefix_words();
    void generate_middle_words();
    void generate_suffix_words();
    void insert_mapping(map<string,int>,int);

    ///½«´ÊµäÐ´ÈëÎÄ¼þ²¢·µ»ØÊÇ·ñ³É¹¦
    bool write_dictionary_to_file();
    int to_binary(int);
};

#endif // DICTIONARY_H
