# yazi-ini
a tiny c++ ini parser

## example

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