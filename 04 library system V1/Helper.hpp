
#pragma once

#include <iostream>
#include <vector>

std::string indenter(int tabs);
void show_menu(const std::vector<std::string> &options, const std::string &prompt, int tabs = 0);