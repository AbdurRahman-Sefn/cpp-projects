
#pragma once

#include <iostream>
#include <vector>


std::string indenter(int tabs);
void show_menu(const std::vector<std::string> &options, const std::string &prompt, int tabs = 0);
void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);
std::basic_istream<char> &read_and_trim(std::istream &is, std::string &str);
