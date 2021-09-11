#include <iostream>
#include <iomanip>
#include <ctime>
#include <regex>


using namespace std;
//нужен ли аргумент origin_fmt или определяю в теле ф-ии?

bool regExTimeConverter(string_view origin_time, string_view target_fmt = "", string ts = ":", string ds = ".")
{
    //12:25:32 11.09.2021
    static const regex format1{//"%H:%M:%S %d.%m.%Y" или "%T %d.%m.%Y"
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts + "([0-5][\\d])\\s([0-3][\\d])" + ds
                + "(1[0-2]|0[1-9])" + ds + "([2][0][0-5][\\d])"};

    //12:26 11.09.21
    static const regex format4{//"%H:%M %d.%m.%y"
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])" + ds +"(1[0-2]|0[1-9])"
                + ds +"([\\d]{2})"};

    //12:25:02 11 Sep 2021
    static const regex format2{//"%H:%M:%S %d %b %Y"
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{3})\\s([2][0][0-5][\\d])"};

    //12:24:39 11 September 2021
    static const regex format3{//"%H:%M:%S %d %B %Y"
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{4,9})\\s([2][0][0-5][\\d])"};


    //TODO
    /*
     * 2 и 3 без секунд
     * поменять местами время и дату во всех регв
     *
     */


    return regex_match(origin_time.data(), format4);
}


int main()
{
    try
    {

       std::time_t t = std::time(nullptr);
       std::tm tm = *std::localtime(&t);
       stringstream ss; ss<< put_time(&tm, "%H:%M %d.%m.%y");

       cout<<ss.str()<<endl;
       cout<<(regExTimeConverter(ss.str()) ? "match" : "not match")<<endl;



    } catch (const std::regex_error &e)
    {
        cerr<<e.what()<<endl;

    }   catch (const std::exception &e)
    {
        cerr<<e.what()<<endl;
    }

    return 0;
}
