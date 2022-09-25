#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "IniFile.h"

using namespace yazi::utility;

Value::Value()
{
}

Value::Value(bool value)
{
    *this = value;
}

Value::Value(int value)
{
    *this = value;
}

Value::Value(double value)
{
    *this = value;
}

Value::Value(const char * value) : m_value(value)
{
}

Value::Value(const string & value) : m_value(value)
{
}

Value::~Value()
{
}

Value & Value::operator = (bool value)
{
    m_value = value ? "true" : "false";
    return *this;
}

Value & Value::operator = (int value)
{
    stringstream ss;
    ss << value;
    m_value = ss.str();
    return *this;
}

Value & Value::operator = (double value)
{
    stringstream ss;
    ss << value;
    m_value = ss.str();
    return *this;
}

Value & Value::operator = (const char * value)
{
    m_value = value;
    return *this;
}

Value & Value::operator = (const string & value)
{
    m_value = value;
    return *this;
}

Value & Value::operator = (const Value & value)
{
    m_value = value.m_value;
    return *this;
}

Value::operator bool()
{
    if (m_value == "true")
        return true;
    else if (m_value == "false")
        return false;
    return false;
}

Value::operator int()
{
    return std::atoi(m_value.c_str());
}

Value::operator double()
{
    return std::atof(m_value.c_str());
}

Value::operator string()
{
    return m_value;
}

IniFile::IniFile()
{
}

IniFile::IniFile(const string & filename)
{
    load(filename);
}

IniFile::~IniFile()
{
}

string IniFile::trim(string s)
{
    if (s.empty())
    {
        return s;
    }
    s.erase(0, s.find_first_not_of(" \r\n"));
    s.erase(s.find_last_not_of(" \r\n") + 1);
    return s;
}

bool IniFile::load(const string & filename)
{
    m_sections.clear();
    m_filename = filename;

    string name;
    string line;

    ifstream fin(filename.c_str());
    if (fin.fail())
    {
        printf("loading file failed: %s is not found.\n", m_filename.c_str());
        return false;
    }
    while (std::getline(fin, line))
    {
        line = trim(line);
        if (line == "")
        {
            continue;
        }
        if (line[0] == '#') // it's comment
        {
            continue;
        }
        if ('[' == line[0]) // it's section
        {
            int pos = line.find_first_of(']');
            if (pos < 0)
            {
                return false;
            }
            name = trim(line.substr(1, pos - 1));
            m_sections[name] = Section();
        }
        else // it's key = value
        {
            int pos = line.find_first_of('=');
            if (pos < 0)
            {
                return false;
            }
            string key = trim(line.substr(0, pos));
            key = trim(key);
            string value = trim(line.substr(pos + 1, line.size() - pos - 1));
            value = trim(value);
            m_sections[name][key] = value;
        }
    }
    return true;
}

void IniFile::save(const string & filename)
{
    ofstream fout(filename.c_str());
    if (fout.fail())
    {
        printf("opening file failed: %s.\n", m_filename.c_str());
        return;
    }
    fout << str();
    fout.close();
}

string IniFile::str()
{
    stringstream ss;
    for (auto it = m_sections.begin(); it != m_sections.end(); ++it)
    {
        ss << "[" << it->first << "]" << endl;
        for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
        {
            ss << iter->first << " = " << (string)iter->second << endl;
        }
        ss << endl;
    }
    return ss.str();
}

void IniFile::show()
{
    std::cout << str();
}

void IniFile::clear()
{
    m_sections.clear();
}

bool IniFile::has(const string & section)
{
    return (m_sections.find(section) != m_sections.end());
}

bool IniFile::has(const string & section, const string & key)
{
    auto it = m_sections.find(section);
    if (it != m_sections.end())
    {
        return (it->second.find(key) != it->second.end());
    }
    return false;
}

Value & IniFile::get(const string & section, const string & key)
{
    return m_sections[section][key];
}

void IniFile::set(const string & section, const string & key, const Value & value)
{
    m_sections[section][key] = value;
}

void IniFile::remove(const string & section)
{
    m_sections.erase(section);
}

void IniFile::remove(const string & section, const string & key)
{
    auto it = m_sections.find(section);
    if (it != m_sections.end())
    {
        it->second.erase(key);
    }
}

