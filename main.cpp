#include <iostream>

#include "time_converter.hpp"

using namespace std;


//TODO
/*
 * поменять местами время и дату во всех регв ?
 * что-то с локалями ru формат для месяца - проверить на win
 * проверить чтобы не было двойных совпадений
 *
 * exp 6 и 7 с коротким годом
 */


int main()
{
    try
    {

       std::time_t t = std::time(nullptr);
       std::tm tm = *std::localtime(&t);
       stringstream ss; ss<< put_time(&tm, "%H:%M %d %B %Y");

       cout<<ss.str()<<endl;
       cout<<timeConvert(ss.str(), "%H:%M:%S %d.%m")<<endl;

       //output:
       //11:54 12 September 2021
       //11:54:00 12.09



    } catch (const std::regex_error &e)
    {
        cerr<<e.what()<<endl;

    }   catch (const std::exception &e)
    {
        cerr<<e.what()<<endl;
    }

    return 0;
}
