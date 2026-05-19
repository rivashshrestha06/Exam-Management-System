#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include <map>
#include "models.h"

using namespace std;

// Forward declaration
class ExamManagementSystem;

// ==================== UI DISPLAY FUNCTIONS ====================
// ===== MAIN MENU =====
void displayMainMenu();

// ===== ADMIN MENU =====
void displayAdminMenu();

// ===== SEARCH STUDENT MENU =====
void displaySearchMenu();

// ===== TEACHER PANEL MENU =====
void displayTeacherPanelMenu();

// ===== STUDENT PANEL MENU =====
void displayStudentPanelMenu();

// ==================== MENU HANDLERS ====================
void handleViewStudentsOption(ExamManagementSystem &ems);
void handleAdminPanel(ExamManagementSystem &ems);
void handleTeacherPanel(ExamManagementSystem &ems, string teacherId);
void handleSearchStudent(ExamManagementSystem &ems);
void handleReports(ExamManagementSystem &ems);
void handleStudentPanel(ExamManagementSystem &ems, string roll);

#endif
