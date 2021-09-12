#include <iostream>
#include <iomanip>
#include <ctime>
#include <regex>


using namespace std;


//TODO
/*
 * поменять местами время и дату во всех регв ?
 * что-то с локалями ru формат для месяца - проверить на win
 * проверить чтобы не было двойных совпадений
 *
 * exp 6 и 7 с коротким годом
 */

//string_view args?
const std::string getTimeFormat(string_view origin_time,
                          const std::string& ts = ":", const std::string& ds = ".")
{
    static const regex exp1{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts + "([0-5][\\d])\\s([0-3][\\d])" + ds
                + "(1[0-2]|0[1-9])" + ds + "([2][0][0-5][\\d])"};

    static const regex exp2{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])" + ds +"(1[0-2]|0[1-9])"
                + ds +"([\\d]{2})"};

    static const regex exp3{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{3})\\s([2][0][0-5][\\d])"};

    static const regex exp4{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{4,9})\\s([2][0][0-5][\\d])"};

    static const regex exp5{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])" + ds
                + "(1[0-2]|0[1-9])" + ds + "([2][0][0-5][\\d])"};

    static const regex exp6{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{3})\\s([2][0][0-5][\\d])"};

    static const regex exp7{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{4,9})\\s([2][0][0-5][\\d])"};

    static const map<const string, const regex*> formats{
        {"%H:%M:%S %d.%m.%Y", &exp1},
        {"%T %d.%m.%Y", &exp1},
        {"%H:%M %d.%m.%y", &exp2},
        {"%H:%M:%S %d %b %Y", &exp3},
        {"%H:%M:%S %d %B %Y", &exp4},
        {"%H:%M %d.%m.%Y", &exp5},
        {"%H:%M %d %b %Y", &exp6},
        {"%H:%M %d %B %Y", &exp7}

    };

    for(const auto& format : formats)
    {
        if(regex_match(origin_time.data(), *format.second))
        {
            return format.first;
        }
    }

    return ""; //что вернуть? мб исключение выше?
}

//string_view args?
const std::string timeConvert(string origin_time, string target_fmt)
{
    std::tm t{};
    std::istringstream ss{origin_time};
//    ss.imbue(std::locale("ru_RU.utf-8")); //en_US

    ss >> std::get_time(&t, getTimeFormat(origin_time).c_str());

    if (ss.fail())
    {
        std::cout << "Parse failed\n";
        //exeption?

    }
    else
    {
        stringstream ss; ss<< std::put_time(&t, target_fmt.c_str());
        return ss.str();
    }
}

bool regExTimeConvert(string origin_time, string_view target_fmt = "", string ts = ":", string ds = ".")
{
    //12:25:32 11.09.2021
    static const regex format1{//"%H:%M:%S %d.%m.%Y" или "%T %d.%m.%Y"
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts + "([0-5][\\d])\\s([0-3][\\d])" + ds
                + "(1[0-2]|0[1-9])" + ds + "([2][0][0-5][\\d])"};

    //12:26 11.09.21
    static const regex format2{//"%H:%M %d.%m.%y"
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])" + ds +"(1[0-2]|0[1-9])"
                + ds +"([\\d]{2})"};

    //12:25:02 11 Sep 2021
    static const regex format3{//"%H:%M:%S %d %b %Y"
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{3})\\s([2][0][0-5][\\d])"};

    //12:24:39 11 September 2021
    static const regex format4{//"%H:%M:%S %d %B %Y"
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{4,9})\\s([2][0][0-5][\\d])"};

    //09:31 12.09.2021
    static const regex format5{//"%H:%M %d.%m.%Y"
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])" + ds
                + "(1[0-2]|0[1-9])" + ds + "([2][0][0-5][\\d])"};

    //09:38 12 Sep 2021
    static const regex format6{//"%H:%M %d %b %Y"
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{3})\\s([2][0][0-5][\\d])"};

    //09:37 12 September 2021
    static const regex format7{//"%H:%M %d %B %Y"
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{4,9})\\s([2][0][0-5][\\d])"};


    //проверяем какому формату подходит origin_time


    static const array<const regex*, 7> formats{
        &format1, &format2, &format3, &format4, &format5, &format6, &format7};

    for(const auto& format : formats)
    {
        if(regex_match(origin_time.data(), *format))
        {
            cout<<"Match found!"<<endl;

            smatch m;
            std::tm tm;

            if(regex_search(origin_time, m, *format))
            {
                 for (string &&str : m)
                 {
                     cout << str << endl;
                 }

                 for (string &&str : m)
                 {
                     tm.tm_hour = stoi(str);
                     tm.tm_min = stoi(str);
                 }



            }
        }
    }

    return true;
}


int main()
{
    try
    {

       std::time_t t = std::time(nullptr);
       std::tm tm = *std::localtime(&t);
       stringstream ss; ss<< put_time(&tm, "%H:%M %d %b %Y");

       cout<<ss.str()<<endl;

       cout<<timeConvert(ss.str(), "%H:%M:%S %d.%m.%Y")<<endl;



    } catch (const std::regex_error &e)
    {
        cerr<<e.what()<<endl;

    }   catch (const std::exception &e)
    {
        cerr<<e.what()<<endl;
    }

    return 0;
}
