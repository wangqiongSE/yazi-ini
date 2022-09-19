# yazi-ini
a tiny c++ ini parser

## example

main.ini
```ini
[server]
ip = 127.0.0.1
port = 80
```

main.cpp
```c++
#include <iostream>
using namespace std;

#include "IniFile.h"
using namespace yazi::utility;

int main()
{
    // load a ini file
    const string & filename = "./main.ini";
    IniFile ini(filename);

    const string & ip = ini.get("server", "ip");
    int port = ini["server"]["port"];

    return 0;
}
```