#include "core.h"
#include "ui.h"
#include "utility.h"
#include <iostream>

using namespace std;

// ==================== MAIN ====================
int main()
{
    ExamManagementSystem ems;
    int choice;

    while (true)
    {
        clearScreen();
        displayMainMenu();

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input.\n";
            pause();
            clearScreen();
            continue;
        }

        // ===== ADMIN LOGIN =====
        if (choice == 1)
        {
            if (ems.adminLogin())
            {
                cout << "\nLogin successful!\n";
                pause();
                clearScreen();
                handleAdminPanel(ems);
            }
            else
            {
                cout << "\nInvalid admin credentials.\n";
                pause();
                clearScreen();
            }
        }

        // ===== STUDENT LOGIN =====
        else if (choice == 2)
        {
            string roll = ems.studentLogin();

            if (roll != "")
            {
                cout << "\nLogin successful!\n";
                pause();
                clearScreen();
                handleStudentPanel(ems, roll);
            }
            else
            {
                cout << "\nInvalid student credentials.\n";
                pause();
                clearScreen();
            }
        }

        // ===== TEACHER LOGIN =====
        else if (choice == 3)
        {
            string tid = ems.teacherLogin();

            if (tid != "")
            {
                cout << "\nLogin successful!\n";
                pause();
                clearScreen();
                handleTeacherPanel(ems, tid);
            }
            else
            {
                cout << "\nInvalid teacher credentials.\n";
                pause();
                clearScreen();
            }
        }

        // ===== EXIT =====
        else if (choice == 4)
        {
            clearScreen();
            header("SAVING DATA");

            ems.saveAll();

            cout << "\nAll data saved successfully.\n";
            cout << "Exiting system...\n";
            break;
        }

        else
        {
            cout << "\nInvalid option.\n";
            pause();
            clearScreen();
        }
    }

    return 0;
}
