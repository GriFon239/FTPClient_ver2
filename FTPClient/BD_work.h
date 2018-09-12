#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <msclr\marshal_cppstd.h>
#include <map>


using namespace System;
using namespace System::Data::OleDb;
namespace fs = std::filesystem;


int Name_addres(std::string);
int BD(String ^);