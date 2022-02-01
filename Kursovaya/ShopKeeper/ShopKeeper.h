#pragma once
//#include <codecvt>
#include <fstream>
#include <string>
#include <vector>
#ifndef ShopKeeper
#define ShopKeeper

int main();
void ShowPositions();
void RedactPosition();
void AddPosition();
void DeletePosition();
void ReadFile();
void WriteFile();
void CoutSpecificPosition(int Code);
int GetMaxColLength(int Index);
std::string FindPositionByCode(std::string Code);
int ReturnChoiceInMain(std::string InterIndex);
bool bIsDigit(std::string Input);


std::vector<std::vector<std::string>> TempFile{};
std::fstream File;

#endif