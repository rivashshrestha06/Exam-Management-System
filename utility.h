#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <algorithm>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

// ==================== UTILITY FUNCTIONS ====================
string getPasswordInput();
void clearScreen();
int getConsoleWidth();
string centerText(string text, int width);
void header(string title);
void pause();
string getCurrentDate();
string getCurrentTime();
int compareTime(string time1, string time2);
bool isExamStarted(string examDate, string examTime);
string getExamEndTime(string examTime, int durationHours, int durationMinutes);
bool isExamEnded(string examDate, string examTime, int durationHours, int durationMinutes);
bool isExamEnded(string examDate, string examTime);
string getExamStatus(string examDate, string examTime, int durationHours, int durationMinutes);
string getExamStatus(string examDate, string examTime);

#endif
