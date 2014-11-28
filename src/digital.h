#ifndef DIGITAL_H
#define DIGITAL_H

class Digital
{
public:
    Digital();
    static QString decToBin(int val);
    static int binToDec(QString val);
};

#endif // DIGITAL_H
