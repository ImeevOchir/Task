#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>

class Operation
{
    int _type;
    int _n;
    char _a;
    char _b;
public:
    Operation(char *str)
    {
        char *tmp;
        _n = strtol(str, &tmp, 10);
        ++tmp;
        if (tmp[1] == '\0' && tmp[0] == 'u') {
            _type = 0;
        } else if (tmp[1] == '\0' && tmp[0] == 'U') {
            _type = 1;
        } else {
            _type = 2;
            _a = tmp[1];
            _b = tmp[2];
        }
    }

    int get_n()
    {
        return _n;
    }

    void execute(std::string &str)
    {
        if (_type == 0) {
            std::transform(str.begin(), str.end(), str.begin(),
                [](unsigned char c){ return std::tolower(c); });
        } else if (_type == 1) {
            std::transform(str.begin(), str.end(), str.begin(),
                [](unsigned char c){ return std::toupper(c); });
        } else {
            std::replace(str.begin(), str.end(), _a, _b);
        }
    }
};

int
main(int argc, char **argv)
{
    std::ifstream input(argv[1]);
    std::list<Operation> ops;
    for (int i = 2; i < argc; ++i)
        ops.push_back(Operation(argv[i]));
    for (std::string line; getline(input, line); )
    {
        std::istringstream is(line);
        std::list<std::string> tmp;
        std::string str;
        std::list<std::string>::iterator it;
        while (is >> str)
            tmp.push_back(str);
        for (Operation op : ops) {
            int n = op.get_n();
            if (tmp.size() > n) {
                it = tmp.begin();
                std::advance(it, n);
                op.execute(*it);
            }
        }
        it = tmp.begin();
        std::cout << *it;
        ++it;
        for (;it != tmp.end(); ++it)
            std::cout << '\t' << *it;
        std::cout << std::endl;
    }
    return 0;
}
