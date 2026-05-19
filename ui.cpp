#include "ui.h"
#include "core.h"
#include "utility.h"
#include <iostream>
#include <iomanip>

using namespace std;

// ==================== UI DISPLAY FUNCTIONS ====================
// ===== MAIN MENU =====
void displayMainMenu()
{
    header("EXAM MANAGEMENT SYSTEM");
    int width = getConsoleWidth();
    string border(min(width - 1, 40), '-');
    cout << centerText("", width) << "\n";
    cout << centerText("WELCOME TO EXAM MANAGEMENT SYSTEM !!!", width) << "\n";
    cout << centerText("", width) << "\n";
    cout << centerText("[1] Admin Login", width) << "\n";
    cout << centerText("[2] Student Login", width) << "\n";
    cout << centerText("[3] Teacher Login", width) << "\n";
    cout << centerText("[4] Exit", width) << "\n";
    cout << centerText(border, width) << "\n";
    cout << centerText("Enter choice: ", width);
}

// ===== ADMIN MENU =====
void displayAdminMenu()
{
    header("ADMIN PANEL");
    int width = getConsoleWidth();
    string border(min(width - 1, 40), '-');
    cout << centerText("", width) << "\n";
    cout << centerText("=== STUDENT MANAGEMENT ===", width) << "\n";
    cout << centerText("[1] View All Students", width) << "\n";
    cout << centerText("[2] Delete Student", width) << "\n";
    cout << centerText("[3] Search Student", width) << "\n";
    cout << centerText("", width) << "\n";
    cout << centerText("=== EXAM MANAGEMENT ===", width) << "\n";
    cout << centerText("[4] Create Exam", width) << "\n";
    cout << centerText("[5] View Exams", width) << "\n";
    cout << centerText("[6] Delete Exam", width) << "\n";
    cout << centerText("", width) << "\n";
    cout << centerText("=== REPORTS ===", width) << "\n";
    cout << centerText("[7] View Reports", width) << "\n";
    cout << centerText("", width) << "\n";
    cout << centerText("[8] Logout", width) << "\n";
    cout << centerText(border, width) << "\n";
    cout << centerText("Enter choice: ", width);
}

// ===== SEARCH STUDENT MENU =====
void displaySearchMenu()
{
    header("SEARCH STUDENT");
    int width = getConsoleWidth();
    string border(min(width - 1, 40), '-');
    cout << centerText("", width) << "\n";
    cout << centerText("[1] Search by Roll Number", width) << "\n";
    cout << centerText("[2] Search by Name", width) << "\n";
    cout << centerText("[3] Back", width) << "\n";
    cout << centerText(border, width) << "\n";
    cout << centerText("Enter choice: ", width);
}

// ===== TEACHER PANEL MENU =====
void displayTeacherPanelMenu()
{
    header("TEACHER PANEL");
    int width = getConsoleWidth();
    string border(min(width - 1, 40), '-');
    cout << centerText("", width) << "\n";
    cout << centerText("[1] Mark Attendance", width) << "\n";
    cout << centerText("[2] Enter Marks", width) << "\n";
    cout << centerText("[3] View Results", width) << "\n";
    cout << centerText("[4] View Attendance", width) << "\n";
    cout << centerText("[5] Logout", width) << "\n";
    cout << centerText(border, width) << "\n";
    cout << centerText("Enter choice: ", width);
}

// ===== STUDENT PANEL MENU =====
void displayStudentPanelMenu()
{
    header("STUDENT PANEL");
    int width = getConsoleWidth();
    string border(min(width - 1, 40), '-');
    cout << centerText("", width) << "\n";
    cout << centerText("[1] View Exams", width) << "\n";
    cout << centerText("[2] View My Results", width) << "\n";
    cout << centerText("[3] View My Profile", width) << "\n";
    cout << centerText("[4] Logout", width) << "\n";
    cout << centerText(border, width) << "\n";
    cout << centerText("Enter choice: ", width);
}

// ==================== ADMIN MENU HANDLERS ====================
void handleViewStudentsOption(ExamManagementSystem &ems)
{
    ems.viewAllStudents();
}

void handleAdminPanel(ExamManagementSystem &ems)
{
    int ch;
    while (true)
    {
        clearScreen();
        displayAdminMenu();

        if (!(cin >> ch))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input.\n";
            pause();
            clearScreen();
            continue;
        }

        if (ch == 8)
            break;

        switch (ch)
        {
        case 1:
            handleViewStudentsOption(ems);
            break;
        case 2:
            ems.deleteStudent();
            break;
        case 3:
            handleSearchStudent(ems);
            break;
        case 4:
            ems.createExam();
            break;
        case 5:
            ems.viewAllExamsReport();
            break;
        case 6:
            ems.deleteExam();
            break;
        case 7:
            handleReports(ems);
            break;
        default:
            cout << "\nInvalid option.\n";
        }

        pause();
        clearScreen();
    }
}

void handleTeacherPanel(ExamManagementSystem &ems, string teacherId)
{
    int ch;
    while (true)
    {
        clearScreen();
        displayTeacherPanelMenu();

        if (!(cin >> ch))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input.\n";
            pause();
            clearScreen();
            continue;
        }

        if (ch == 5)
            break;

        switch (ch)
        {
        case 1:
            ems.markAttendance(teacherId);
            break;
        case 2:
            ems.enterMarks(teacherId);
            break;
        case 3:
            ems.viewResult(teacherId);
            break;
        case 4:
            ems.viewAttendance(teacherId);
            break;
        default:
            cout << "\nInvalid option.\n";
        }

        pause();
        clearScreen();
    }
}

void handleSearchStudent(ExamManagementSystem &ems)
{
    int sch;
    clearScreen();
    while (true)
    {
        clearScreen();
        displaySearchMenu();
        if (!(cin >> sch))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (sch == 3)
            break;
        switch (sch)
        {
        case 1:
            ems.searchStudentByRoll();
            break;
        case 2:
            ems.searchStudentByName();
            break;
        default:
            cout << "\nInvalid option.\n";
        }
        pause();
        clearScreen();
    }
}

void handleReports(ExamManagementSystem &ems)
{
    int rch;
    clearScreen();
    while (true)
    {
        clearScreen();
        header("REPORTS");
        int width = getConsoleWidth();
        string border(min(width - 1, 40), '-');
        cout << centerText("", width) << "\n";
        cout << centerText("[1] View All Results", width) << "\n";
        cout << centerText("[2] View Pass/Fail Summary", width) << "\n";
        cout << centerText("[3] View Topper Per Exam", width) << "\n";
        cout << centerText("[4] View Exam Statistics", width) << "\n";
        cout << centerText("[5] View Class Performance", width) << "\n";
        cout << centerText("[6] View Marks Distribution", width) << "\n";
        cout << centerText("[7] Back", width) << "\n";
        cout << centerText(border, width) << "\n";
        cout << centerText("Enter choice: ", width);
        
        if (!(cin >> rch))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (rch == 7)
            break;
        switch (rch)
        {
        case 1:
            ems.viewAllResultsReport();
            break;
        case 2:
            ems.viewPassFailSummary();
            break;
        case 3:
            ems.viewTopperPerExam();
            break;
        case 4:
            ems.viewExamStatistics();
            break;
        case 5:
            ems.viewClassPerformance();
            break;
        case 6:
            ems.viewMarksDistribution();
            break;
        default:
            cout << "\nInvalid option.\n";
        }
        pause();
        clearScreen();
    }
}

// ==================== STUDENT MENU HANDLERS ====================
void handleStudentPanel(ExamManagementSystem &ems, string roll)
{
    int ch;
    clearScreen();
    while (true)
    {
        clearScreen();
        displayStudentPanelMenu();

        if (!(cin >> ch))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input.\n";
            pause();
            clearScreen();
            continue;
        }

        if (ch == 4)
            break;

        switch (ch)
        {
        case 1:
            ems.viewStudentExams(roll);
            break;
        case 2:
            ems.viewStudentResultsDetailed(roll);
            break;
        case 3:
            ems.viewStudentProfile(roll);
            break;
        default:
            cout << "\nInvalid option.\n";
        }

        pause();
        clearScreen();
    }
}
