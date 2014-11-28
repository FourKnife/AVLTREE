#include"Dictionary.h"
#include<iostream>

Dictionary::Dictionary()
{
    for(int i = 0;i < 4;i++)
        mapping[i].clear();
    words.clear();
}

///
string Dictionary::build_dictionary(string file_location)
{
    bool success;
    success = read_file_to_words(file_location);
    if(!success)
        return "no found file";
    success = generate_dictionary_to_mapping();
    if(!success)
        return "generate dictionary failed";
    success = write_dictionary_to_file();
    if(!success)
        return "write dictionary failed";
    return "write dictionary success";
}

///¶ÁÈëÎÄ¼þ£¬³éÀë´Ê¡¢×Ö
bool Dictionary::read_file_to_words(string file_location)
{
    ifstream read;
    read.open(file_location.c_str());
    if(read.fail())///ÎÄ¼þ²»´æÔÚ
    {
        read.close();
        return false;
    }
    string line;
    while(getline(read,line))
    {
        deal_line(line);
    }
    read.close();
    return true;
}
///¶ÔÎÄ¼þÃ¿Ò»ÐÐ½øÐÐµ¥´Ê³é³ö
void Dictionary::deal_line(string line)
{
    for(int i = 0;i < line.length();i++)
    {
        ///µ±Ç°×Ö·ûÊÇ×ÖÄ¸
        if(judge_letter(line[i]))
        {
            int word_length;///¼ÇÂ¼µ±Ç°µ¥´Ê³¤¶È
            for(word_length = 1;i+word_length < line.length();word_length++)
            {
                if(judge_letter(line[i+word_length]))
                {
                    continue;
                }
                break;
            }
            if(word_length == 1)
                continue;
            string temp = line.substr(i,word_length);
            words.push_back(temp);
            i += word_length-1;
        }
    }
}
///ÅÐ¶Ï×Ö·ûÊÇ·ñÊÇ×ÖÄ¸
bool Dictionary::judge_letter(char character)
{
    if((character >= 'A' && character <= 'Z')||(character >= 'a' && character <= 'z'))
        return true;
    return false;
}

///Éú³É´Êµä
bool Dictionary::generate_dictionary_to_mapping()
{
    generate_high_frequency_words();
    generate_prefix_words();
    generate_middle_words();
    generate_suffix_words();
    return true;
}

void Dictionary::generate_high_frequency_words()
{
    map<string,int> word_map;
    map<string,int>::iterator iter;
    ///½«µ¥´Ê²»ÖØ¸´¼ÓÈëmap
    for(int i = 0;i < words.size();i++)
    {
        iter = word_map.find(words[i]);
        if(iter == word_map.end())
        {
            word_map.insert(pair<string,int>(words[i],1));
        }
        else
        {
            iter->second++;
        }
    }

    ///Í³¼Æ¸ßÆµ´Ê²¢¼ÇÂ¼Èëmapping
    insert_mapping(word_map,0);
}

void Dictionary::generate_prefix_words()
{
    map<string,int> word_map;
    map<string,int>::iterator iter;
    ///½«Ç°×º²»ÖØ¸´¼ÓÈëmap
    for(int i = 0;i < words.size();i++)
    {
        if(words[i].length() <= 2)
            continue;
        string temp = words[i].substr(0,prefix_num);
        iter = word_map.find(temp);
        if(iter == word_map.end())
        {
            word_map.insert(pair<string,int>(temp,1));
        }
        else
        {
            iter->second++;
        }
    }

    ///Í³¼Æ¸ßÆµ´Ê²¢¼ÇÂ¼Èëmapping
    insert_mapping(word_map,1);
}

void Dictionary::generate_suffix_words()
{
    map<string,int> word_map;
    map<string,int>::iterator iter;
    ///½«ºó×º²»ÖØ¸´¼ÓÈëmap
    for(int i = 0;i < words.size();i++)
    {
        if(words[i].length() <= 4)
            continue;
        string temp = words[i].substr(words[i].length()-suffix_num,suffix_num);
        iter = word_map.find(temp);
        if(iter == word_map.end())
        {
            word_map.insert(pair<string,int>(temp,1));
        }
        else
        {
            iter->second++;
        }
    }

    ///Í³¼Æ¸ßÆµ´Ê²¢¼ÇÂ¼Èëmapping
    insert_mapping(word_map,2);
}

void Dictionary::insert_mapping(map<string,int> word,int type)
{
    int high_frequency_times = qualified_line;///³¬¹ý¸ÃÊýÁ¿¼´Îª¸ßÆµ
    ///Í³¼Æ¸ßÆµ´Ê²¢¼ÇÂ¼Èëmapping
    int mapping_location = 128;///¼ÇÂ¼mappingµ±Ç°Ó³ÉäÊýÖµ
    map<string,int>::iterator iter;
    for(iter = word.begin();iter != word.end();iter++)
    {
        if(iter->second >= high_frequency_times)
        {
            mapping[type].insert(pair<int,string>(mapping_location++,iter->first));
        }
    }
}

void Dictionary::generate_middle_words()
{
    string double_words[26] = {"aa","bb","cc","dd","ee","ff","gg","hh","ii","jj",
    "kk","ll","mm","nn","oo","pp","qq","rr","ss","tt","uu","vv","ww","xx","yy","zz"};
    int mapping_location = 128;///¼ÇÂ¼mappingµ±Ç°Ó³ÉäÊýÖµ
    for(int i = 0;i < 26;i++)
    {
        mapping[3].insert(pair<int,string>(mapping_location++,double_words[i]));
    }
}

///½«´ÊµäÐ´ÈëÎÄ¼þ
///ÎÄ¼þ¸ñÊ½Ã¿ÐÐ¾ùÎª£º°ËÎ»¶þ½øÖÆÊý.¸ßÆµ´Ê.Ç°×º.ºó×º.double×Ö
bool Dictionary::write_dictionary_to_file()
{
    ///ËÄ¸öÎÄ¼þµÄµØÖ·
    string dictionary_location[4] = {"..\\dictionary\\frequently.txt",
    "..\\dictionary\\preffix.txt","..\\dictionary\\suffix.txt","..\\dictionary\\double.txt"};
    ///4¸öÎÄ¼þÊä³öÁ÷Ð´ÈëÎÄ¼þ
    for(int i = 0;i < 4;i++)
    {
        ofstream write_dictionary;
        try
        {
            write_dictionary.open(dictionary_location[i].c_str());
            map<int,string>::iterator iter;///µü´úÆ÷
            for(iter = mapping[i].begin();iter != mapping[i].end();iter++)
            {
                write_dictionary << iter->second << " " << to_binary(iter->first) << endl;
            }
            write_dictionary.close();
        }
        catch(...)
        {
            write_dictionary.close();
            return false;
        }
    }
    return true;
}

///½«Ê®½øÖÆ×ª»»³É8Î»¶þ½øÖÆ
int Dictionary::to_binary(int num)
{
    int binary_num = 0;     ///´æ·Å2½øÖÆµÄÊý×Ö
    int digits = 1;
    while(num != 0 && num != 1)
    {
        binary_num += digits * (num % 2);
        num /= 2;
        digits *= 10;
    }
    binary_num += digits * num;///¼ÓÉÏ×îºóÒ»Î»ÓàÊý.
    return binary_num;
}

/**
int main()
{
    Dictionary t;
    cout << t.Dictionary("sss.txt");
    return 0;
}
**/
