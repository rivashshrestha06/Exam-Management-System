#ifndef CORE_H
#define CORE_H

#include <map>
#include <string>
#include <vector>
#include "models.h"
#include "filehandler.h"

using namespace std;

// ==================== EXAM MANAGEMENT SYSTEM ====================
class ExamManagementSystem
{
private:
    map<string, Student> students;
    map<string, Exam> exams;
    map<string, Result> results;
    map<string, bool> attendance;
    map<string, Subject> subjects;
    map<string, Teacher> teachers;

public:
    ExamManagementSystem();

    // Helper function to check if result passes based on exam's actual pass marks
    bool isResultPass(string examId, double marks);

    // ============ LOGIN ============
    bool adminLogin();
    string studentLogin();
    string teacherLogin();

    // ============ FILE OPERATIONS - SAVE ============
    void saveAll();

    // ============ STUDENT OPERATIONS ============
    void deleteStudent();
    bool studentRollExists(string roll);
    void viewAllStudents();
    void viewStudentsBySemester(int semester);
    void searchStudentByRoll();
    void searchStudentByName();

    // ============ EXAM OPERATIONS ============
    void createExam();
    void viewAllExams();
    void viewAllExamsReport();
    void deleteExam();

    // ============ ATTENDANCE OPERATIONS ============
    void markAttendance(string teacherId = "");
    void viewAttendance(string teacherId = "");

    // ============ MARKS OPERATIONS ============
    void enterMarks(string teacherId = "");

    // ============ RESULT OPERATIONS ============
    void viewResult(string teacherId = "");
    void viewAllResultsReport();
    void viewStudentReport(string roll);

    // ============ REPORTS ============
    void viewPassFailSummary();
    void viewTopperPerExam();
    void viewExamStatistics();
    void viewClassPerformance();
    void viewMarksDistribution();

    // ============ STUDENT PANEL ============
    void viewStudentProfile(string roll);
    void viewStudentExams(string roll);
    void viewStudentResultsDetailed(string roll);

    // Helper functions
    vector<pair<int, Student>> getStudentsForSemester(int semester);
    string extractSubjectFromExamId(string examId);
    bool isTeacherAuthorized(string teacherId, string examId);
};

#endif
