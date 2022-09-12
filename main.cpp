#include <iostream>
using namespace std;

#include "IniFile.h"
using namespace yazi::utility;

int main()
{
    // load a ini file
    const string & filename = "./main.ini";
    IniFile ini(filename);

    // load a ini file
    const string & filename2 = "./main.ini";
    IniFile ini2;
    ini2.load(filename2);

    // show the ini file
    ini.show();

    // dump the ini file
    ini.save("./main2.ini");

    // get value
    const string & name = ini["profile"]["name"];
    std::cout << "ini[\"profile\"][\"name\"] = " << name << std::endl;

    // get value
    int age = ini.get("profile", "age");
    std::cout << "ini[\"profile\"][\"age\"] = " << age << std::endl;

    // set value
    ini["profile"]["age"] = 31;

    // set value
    ini.set("profile", "age", 32);

    age = ini["profile"]["age"];
    std::cout << "int[\"profile\"[\"age\"] = " << age << std::endl;

    // if the server section is exist
    if (ini.has("server"))
    {
        std::cout << "ini[\"server\"] is exist" << std::endl;
    }

    // if the server section and ip key is exist
    if (ini.has("server", "ip"))
    {
        std::cout << "ini[\"server\"][\"ip\"] is exist" << std::endl;
    }

    // remove the key ip in server section
    ini.remove("server", "ip");

    // remove the sever section
    ini.remove("server");

    // clear the ini file
    ini.clear();

    return 0;
}
