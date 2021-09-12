#include "time_converter.hpp"

const std::string getTimeFormat(std::string_view origin_time,
                          const std::string& ts, const std::string& ds)
{
    static const std::regex exp1{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts + "([0-5][\\d])\\s([0-3][\\d])" + ds
        + "(1[0-2]|0[1-9])" + ds + "([2][0][0-5][\\d])"};

    static const std::regex exp2{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])" + ds +"(1[0-2]|0[1-9])"
        + ds +"([\\d]{2})"};

    static const std::regex exp3{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts +
        "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{3})\\s([2][0][0-5][\\d])"};

    static const std::regex exp4{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts +
        "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{4,9})\\s([2][0][0-5][\\d])"};

    static const std::regex exp5{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])" + ds
        + "(1[0-2]|0[1-9])" + ds + "([2][0][0-5][\\d])"};

    static const std::regex exp6{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{3})\\s([2][0][0-5][\\d])"};

    static const std::regex exp7{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{4,9})\\s([2][0][0-5][\\d])"};

    static const std::regex exp8{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{3})\\s([\\d]{2})"};

    static const std::regex exp9{
    "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s([0-3][\\d])\\s(\\w{4,9})\\s([\\d]{2})"};

    static const std::regex exp10{
    "([0-3][\\d])" + ds+ "(1[0-2]|0[1-9])" + ds + "([2][0][0-5][\\d])\\s"
        "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts + "([0-5][\\d])"};

    static const std::regex exp11{
    "([0-3][\\d])" + ds +"(1[0-2]|0[1-9])"
        + ds +"([\\d]{2})\\s([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])"};

    static const std::regex exp12{
    "([0-3][\\d])\\s(\\w{3})\\s([2][0][0-5][\\d])\\s"
        "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts + "([0-5][\\d])"};

    static const std::regex exp13{
    "([0-3][\\d])\\s(\\w{4,9})\\s([2][0][0-5][\\d])\\s"
        "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])" + ts + "([0-5][\\d])"};

    static const std::regex exp14{
    "([0-3][\\d])" + ds + "(1[0-2]|0[1-9])" + ds + "([2][0][0-5][\\d])\\s"
        "([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])\\s"};

    static const std::regex exp15{
    "([0-3][\\d])\\s(\\w{3})\\s([2][0][0-5][\\d])\\s([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])"};

    static const std::regex exp16{
    "([0-3][\\d])\\s(\\w{4,9})\\s([2][0][0-5][\\d])\\s([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])"};

    static const std::regex exp17{
    "([0-3][\\d])\\s(\\w{3})\\s([\\d]{2})\\s([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])"};

    static const std::regex exp18{
    "([0-3][\\d])\\s(\\w{4,9})\\s([\\d]{2})\\s([01]?[\\d]|2[0-3])" + ts + "([0-5][\\d])"};


    static const std::map<const std::string, const std::regex*> formats{
        {"%H:%M:%S %d.%m.%Y", &exp1},
        {"%T %d.%m.%Y", &exp1},
        {"%H:%M %d.%m.%y", &exp2},
        {"%H:%M:%S %d %b %Y", &exp3},
        {"%H:%M:%S %d %B %Y", &exp4},
        {"%H:%M %d.%m.%Y", &exp5},
        {"%H:%M %d %b %Y", &exp6},
        {"%H:%M %d %B %Y", &exp7},
        {"%H:%M %d %b %y", &exp8},
        {"%H:%M %d %B %y", &exp9},
        //reverse order
        {"%d.%m.%Y %H:%M:%S", &exp10},  //reverse exp1-1
        {"%d.%m.%Y %T", &exp10},        //reverse exp1-2
        {"%d.%m.%y %H:%M", &exp11},     //reverse exp2
        {"%d %b %Y %H:%M:%S", &exp12},  //reverse exp3
        {"%d %B %Y %H:%M:%S", &exp13},  //reverse exp4
        {"%d.%m.%Y %H:%M", &exp14},     //reverse exp5
        {"%d %b %Y %H:%M", &exp15},     //reverse exp6
        {"%d %B %Y %H:%M", &exp16},     //reverse exp7
        {"%d %b %y %H:%M", &exp17},     //reverse exp8
        {"%d %B %y %H:%M", &exp18}      //reverse exp9
    };

    for(const auto& format : formats)
    {
        if(regex_match(origin_time.data(), *format.second))
        {
            return format.first;
        }
    }

    throw "getTimeFormat found no matches";
}

const std::string timeConvert(std::string_view origin_time,
                              std::string_view target_fmt, std::string_view locale)
{
    std::tm t{};
    std::istringstream ss{origin_time.data()};
    ss.imbue(std::locale(locale.data()));

    std::string tf = getTimeFormat(origin_time);

    ss >> std::get_time(&t, getTimeFormat(origin_time).c_str());

    if (!ss.fail())
    {
        std::stringstream ss;
        ss<< std::put_time(&t, target_fmt.data());
        return ss.str();
    }
    else
    {
        throw "timeConvert parsing failed";
    }
}
