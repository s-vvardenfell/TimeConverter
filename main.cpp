#include <iostream>

#include "time_converter.hpp"

using namespace std;

int main()
{
    try
    {
       std::time_t t = std::time(nullptr);
       std::tm tm = *std::localtime(&t);
       stringstream ss; ss<< put_time(&tm, "%H:%M %d %B %Y");

       cout<<ss.str()<<endl;
       cout<<timeConvert(ss.str(), "%d.%m.%y %H:%M:%S")<<endl;

       //output:
       //12:16 12 September 2021
       //12.09.2021 12:16:00



    } catch (const std::regex_error &e)
    {
        cerr<<e.what()<<endl;

    }   catch (const std::exception &e)
    {
        cerr<<e.what()<<endl;
    }

    return 0;
}
