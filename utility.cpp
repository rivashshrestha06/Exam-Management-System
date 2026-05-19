#include "utility.h"

// ==================== UTILITY FUNCTIONS ====================
// Function to mask password input (cross-platform)
string getPasswordInput()
{
    string password = "";
    char ch;

    #ifdef _WIN32
    // Windows implementation using _getch()
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!password.empty())
            {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            password += ch;
            cout << "*";
        }
    }
    cout << "\n";
    #else
    // Unix/Linux implementation
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((ch = getchar()) != '\n')
    {
        password += ch;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    cout << "\n";
#endif

    return password;
}

void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        cout << "\033[2J\033[1;1H";
    #endif
}

// ==================== UI UTILITY FUNCTIONS ====================
// Get console width
int getConsoleWidth()
{
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
        {
            return csbi.srWindow.Right - csbi.srWindow.Left + 1;
        }
    #else
        // For Unix/Linux, return standard width
    #endif
    return 80; // Default fallback width
}

// Center text based on console width
string centerText(string text, int width)
{
    int padding = (width - text.length()) / 2;
    if (padding < 0) padding = 0;
    return string(padding, ' ') + text;
}

void header(string title)
{
    int width = getConsoleWidth();
    string border(width - 1, '=');
    
    cout << centerText(border, width) << "\n";
    cout << centerText(title, width) << "\n";
    cout << centerText(border, width) << "\n";
}

void pause()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// ==================== DATE & TIME FUNCTIONS ====================
// Get current date in YYYY-MM-DD format
string getCurrentDate()
{
    time_t now = time(0);
    struct tm *timeinfo = localtime(&now);
    string year = to_string(1900 + timeinfo->tm_year);
    string month = (timeinfo->tm_mon + 1 < 10 ? "0" : "") + to_string(timeinfo->tm_mon + 1);
    string day = (timeinfo->tm_mday < 10 ? "0" : "") + to_string(timeinfo->tm_mday);
    return year + "-" + month + "-" + day;
}

// Get current time in HH:MM format
string getCurrentTime()
{
    time_t now = time(0);
    struct tm *timeinfo = localtime(&now);
    string hour = (timeinfo->tm_hour < 10 ? "0" : "") + to_string(timeinfo->tm_hour);
    string minute = (timeinfo->tm_min < 10 ? "0" : "") + to_string(timeinfo->tm_min);
    return hour + ":" + minute;
}

// Compare two times in HH:MM format. Returns: 1 if time1 > time2, -1 if time1 < time2, 0 if equal
int compareTime(string time1, string time2)
{
    int hour1 = stoi(time1.substr(0, 2));
    int min1 = stoi(time1.substr(3, 2));
    int hour2 = stoi(time2.substr(0, 2));
    int min2 = stoi(time2.substr(3, 2));
    
    int totalMin1 = hour1 * 60 + min1;
    int totalMin2 = hour2 * 60 + min2;
    
    if (totalMin1 > totalMin2) return 1;
    if (totalMin1 < totalMin2) return -1;
    return 0;
}

// Check if current date-time is >= exam date-time (for marking attendance - exam has started)
bool isExamStarted(string examDate, string examTime)
{
    string currentDate = getCurrentDate();
    string currentTime = getCurrentTime();
    
    if (currentDate > examDate) return true;
    if (currentDate < examDate) return false;
    return compareTime(currentTime, examTime) >= 0;
}

// Calculate exam end time by adding duration to start time
string getExamEndTime(string examTime, int durationHours, int durationMinutes)
{
    int hour = stoi(examTime.substr(0, 2));
    int min = stoi(examTime.substr(3, 2));
    
    int totalMinutes = hour * 60 + min + durationHours * 60 + durationMinutes;
    
    // Handle day overflow
    int endHour = (totalMinutes / 60) % 24;
    int endMin = totalMinutes % 60;
    
    string endTimeStr = (endHour < 10 ? "0" : "") + to_string(endHour) + ":" + (endMin < 10 ? "0" : "") + to_string(endMin);
    return endTimeStr;
}

// Check if current date-time is > exam end time (for entering marks - exam has ended)
// This accounts for exam duration
bool isExamEnded(string examDate, string examTime, int durationHours, int durationMinutes)
{
    string currentDate = getCurrentDate();
    string currentTime = getCurrentTime();
    string examEndTime = getExamEndTime(examTime, durationHours, durationMinutes);
    
    if (currentDate > examDate) return true;
    if (currentDate < examDate) return false;
    return compareTime(currentTime, examEndTime) > 0;
}

// Overload for backward compatibility (without duration)
bool isExamEnded(string examDate, string examTime)
{
    return isExamEnded(examDate, examTime, 0, 0);
}

// Get exam status based on real time (accounting for exam duration)
string getExamStatus(string examDate, string examTime, int durationHours, int durationMinutes)
{
    if (isExamEnded(examDate, examTime, durationHours, durationMinutes))
    {
        return "COMPLETED";
    }
    else if (isExamStarted(examDate, examTime))
    {
        return "ONGOING";
    }
    else
    {
        return "UPCOMING";
    }
}

// Overload for backward compatibility (without duration)
string getExamStatus(string examDate, string examTime)
{
    return getExamStatus(examDate, examTime, 0, 0);
}
