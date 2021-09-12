#ifndef TIME_CONVERTER_HPP
#define TIME_CONVERTER_HPP

#include <iomanip>
#include <ctime>
#include <regex>


const std::string getTimeFormat(std::string_view origin_time,
                          const std::string& ts = ":", const std::string& ds = ".");

const std::string timeConvert(std::string_view origin_time,
                              std::string_view target_fmt, std::string_view locale = "en_US.utf-8");


#endif // TIME_CONVERTER_HPP
