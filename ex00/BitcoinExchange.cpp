#include "BitcoinExchange.hpp"

bool parse_date(std::string &date, std::string &line)
{
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    if (year <= 2009)
    {
        if (year < 2009)
            return (std::cerr << "Error: btc did not exist before [2009-01-02]", 0);
        if (day < 2 && month == 1)
            return (std::cerr << "Error: btc did not exist before [2009-01-02]", 0);
    }
    if (month > 12)
        return (std::cerr << "Error: bad input => " << line << std::endl,0);
    if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31)
        return (std::cerr << "Error: bad input => " << line << std::endl, 0);
    else if ((month == 2 || month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return (std::cerr << "Error: bad input => " << line << std::endl, 0);
    else if (month == 2 && day > 29)
        return (std::cerr << "Error: bad input => " << line << std::endl, 0);
    line = date;
    return true;
}

bool parse_line(std::string &line, double &val){
    size_t pos;
    std::string date;
    std::string value;
    char *end = NULL;
    pos = line.find(" | ");
    if (pos == std::string::npos)
        return (std::cerr << "Error: bad input => " << line << std::endl, 0);
    date = line.substr(0, pos);
    value = line.substr(pos + 3, line.size() - pos - 3);
    val = std::strtod(value.c_str(), &end);
    if (val > 1000)
        return (std::cerr << "Error: too large number" << std::endl, 0);
    if (val < 0)
        return (std::cerr << "Error: not a positive number" << std::endl, 0);
    if (*end != '\0' || isspace(value[0]))
        return (std::cerr << "Error: bad input => " << line << std::endl, 0);
    if (date.size() > 10 || date[4] != '-' || date[7] != '-')
        return (std::cerr << "Error: bad input => " << line << std::endl, 0);
    for (size_t i = 0; date[i]; i++)
    {
        if (i == 4 || i == 7)
            continue;
        else if (date[i] < '0' || date[i] > '9')
            return (std::cerr << "Error: bad input => " << line << std::endl, 0);
    }
    return (parse_date(date, line));
}

void print_the_result(std::map<std::string, float> &data, std::string &date, double &value)
{
    std::map<std::string, float>::iterator it = data.lower_bound(date);
    
    if (data.size() == 0){
        std::cerr << "Error the data is empty." << std::endl;
        return ;
    }
    if (it == data.end())
        --it;
    else if (it != data.begin() && it->first.compare(date))
        --it;
    std::cout << date << " => " << value << " = " << value * it->second << std::endl;
}