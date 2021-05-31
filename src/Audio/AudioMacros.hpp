#pragma once

#include <string>
#include <iostream>
#include <type_traits>
#include <AL/al.h>

bool check_al_errors(const std::string filename, const int linenumber, std::string arg);

#define alCall(var) var; !check_al_errors(__FILE__, __LINE__, #var)

