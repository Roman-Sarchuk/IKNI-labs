#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

const float priceByPage = 150.0f;	// can be changeds
const std::vector<std::string> fieldName = { "customer","language","pages","transleter","date","price" };

struct Order
{
	std::string customer;
	std::string language;
	size_t pages{};
	std::string transleter;
	std::string date;
	float price{};
};

// File Processing
std::string getPath();
void updateFile(std::vector<Order> database, std::string filename);
void appandRtoF(Order record, std::string filename);
void getData(std::vector<Order>& database, std::string filename);
std::pair<std::vector<Order>, std::vector<size_t>> getSearchDB(std::vector<Order> database, std::string fpath);


// Menu Opration
void addRecord(std::vector<Order>& database);
std::pair<std::vector<Order>, std::vector<size_t>> searchRecord(std::vector<Order> database, std::string filename, bool showAll = false);
void showDataBase(std::vector<Order> database, bool showID = false);
void editRecord(std::vector<Order>& database, size_t recordnum);
void sortDataBase(std::vector<Order>& database);
std::vector<size_t> spellDate(std::string date);
bool compareDate(Order lor, Order ror);

// Data Processing
std::string enterString(size_t marginl, std::string inputtext);
size_t enterPages(size_t marginl = 15);
float enterPrice(size_t marginl = 15);
std::string enterDate(size_t marginl = 10);

// Auxiliary Function
bool isin(size_t value, std::vector<size_t> list);
std::vector<size_t> getRange(size_t end);
size_t getActionNum(size_t range);
size_t getFieldId(bool showAll = false);
std::string getFieldname(std::string field);
std::string getFieldvalue(std::string field);
