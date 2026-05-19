#include "core.h"
#include "utility.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

// ==================== CONSTRUCTOR ====================
ExamManagementSystem::ExamManagementSystem()
{
    FileHandler::loadSubjectsFromFile(subjects);
    FileHandler::loadStudentsFromAllSemesters(students);
    FileHandler::loadTeachersFromFile(teachers);
    FileHandler::loadExamsFromFile(exams);
    FileHandler::loadResultsFromFile(results);
    FileHandler::loadAttendanceFromFile(attendance);
}

// Helper function to check if result passes based on exam's actual pass marks
bool ExamManagementSystem::isResultPass(string examId, double marks)
{
    if (exams.count(examId))
    {
        return marks >= exams[examId].getPassMarks();
    }
    return marks >= 40; // fallback to 40 if exam not found
}

// ============ LOGIN ============
bool ExamManagementSystem::adminLogin()
{
    string u, p;
    cout << "Admin Username: ";
    cin >> u;
    cout << "Password: ";
    p = getPasswordInput();
    return (u == "admin" && p == "12345678");
}

string ExamManagementSystem::studentLogin()
{
    string roll, pw;
    cout << "Enter Roll Number: ";
    cin >> roll;

    if (students.count(roll))
    {
        cout << "Password: ";
        pw = getPasswordInput();
        if (students[roll].getPassword() == pw)
        {
            return roll;
        }
        cout << "Invalid password\n";
        return "";
    }
    cout << "Invalid roll number\n";
    return "";
}

string ExamManagementSystem::teacherLogin()
{
    string tid, pw;
    cout << "Enter Teacher ID: ";
    cin >> tid;

    if (teachers.count(tid))
    {
        cout << "Password: ";
        pw = getPasswordInput();
        if (teachers[tid].getPassword() == pw)
        {
            return tid;
        }
        cout << "Invalid password\n";
        return "";
    }
    cout << "Invalid teacher ID\n";
    return "";
}

// ============ FILE OPERATIONS - SAVE ============
void ExamManagementSystem::saveAll()
{
    FileHandler::saveStudentsToFile(students);
    FileHandler::saveExamsToFile(exams);
    FileHandler::saveResultsToFile(results);
    FileHandler::saveAttendanceToFile(attendance);
}

// ============ STUDENT OPERATIONS ============
void ExamManagementSystem::deleteStudent()
{
    string roll;
    cout << "Roll Number to delete: ";
    cin >> roll;

    if (students.count(roll))
    {
        students.erase(roll);
        cout << "Student deleted successfully.\n";
    }
    else
    {
        cout << "Student not found.\n";
    }
}

bool ExamManagementSystem::studentRollExists(string roll)
{
    return students.count(roll) > 0;
}

void ExamManagementSystem::viewAllStudents()
{
    if (students.empty())
    {
        cout << "No students found.\n";
        return;
    }

    vector<pair<string, Student>> studentsList;
    for (auto &p : students)
    {
        studentsList.push_back(p);
    }
    sort(studentsList.begin(), studentsList.end(), [](const pair<string, Student> &a, const pair<string, Student> &b)
         { return a.second.getRollNumber() < b.second.getRollNumber(); });

    cout << "\n========== ALL STUDENTS ==========\n";
    cout << "\n"
         << left << setw(15) << "Roll Number" << setw(30) << "Name" << setw(20) << "Program" << "\n";
    cout << "------------------------------------------------------------------------\n";
    for (auto &p : studentsList)
    {
        auto s = p.second;
        cout << left << setw(15) << s.getRollNumber() << setw(30) << s.getName() << setw(20) << s.getProgram() << "\n";
    }
}

void ExamManagementSystem::viewStudentsBySemester(int semester)
{
    vector<pair<string, Student>> studentsList;
    for (auto &p : students)
    {
        studentsList.push_back(p);
    }
    
    if (studentsList.empty())
    {
        cout << "\nNo students found.\n";
        return;
    }
    
    sort(studentsList.begin(), studentsList.end(), [](const pair<string, Student> &a, const pair<string, Student> &b)
         { return a.second.getRollNumber() < b.second.getRollNumber(); });
    
    cout << "\n========== SEMESTER 3 STUDENTS ==========\n";
    cout << "\n"
         << left << setw(15) << "Roll Number" << setw(30) << "Name" << setw(20) << "Program" << "\n";
    cout << "------------------------------------------------------------------------\n";
    for (auto &p : studentsList)
    {
        auto s = p.second;
        cout << left << setw(15) << s.getRollNumber() << setw(30) << s.getName() << setw(20) << s.getProgram() << "\n";
    }
}

void ExamManagementSystem::searchStudentByRoll()
{
    string roll;
    cout << "Enter Roll Number: ";
    cin >> roll;

    vector<pair<string, Student>> matchedStudents;
    
    if (students.count(roll))
    {
        matchedStudents.push_back({roll, students[roll]});
    }

    if (matchedStudents.empty())
    {
        cout << "\nNo student found with Roll Number: " << roll << "\n";
        return;
    }

    cout << "\n========== SEARCH RESULTS ==========\n";
    cout << "\n" << left << setw(15) << "Roll Number" << setw(30) << "Name" << setw(20) << "Program" << setw(10) << "Semester" << "\n";
    cout << "------------------------------------------------------------------------\n";
    
    for (auto &p : matchedStudents)
    {
        auto s = p.second;
        cout << left << setw(15) << s.getRollNumber() << setw(30) << s.getName() << setw(20) << s.getProgram() << setw(10) << s.getSemester() << "\n";
    }
}

void ExamManagementSystem::searchStudentByName()
{
    string name;
    cin.ignore();
    cout << "Enter Student Name (partial or full): ";
    getline(cin, name);

    vector<pair<string, Student>> matchedStudents;

    for (auto &p : students)
    {
        auto s = p.second;
        string studentName = s.getName();

        transform(studentName.begin(), studentName.end(), studentName.begin(), ::tolower);
        string searchName = name;
        transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);

        if (studentName.find(searchName) != string::npos)
        {
            matchedStudents.push_back(p);
        }
    }

    if (matchedStudents.empty())
    {
        cout << "\nNo students found matching: " << name << "\n";
        return;
    }

    sort(matchedStudents.begin(), matchedStudents.end(), [](const pair<string, Student> &a, const pair<string, Student> &b)
         { return a.second.getRollNumber() < b.second.getRollNumber(); });

    cout << "\n========== SEARCH RESULTS ==========\n";
    cout << "\n" << left << setw(15) << "Roll Number" << setw(30) << "Name" << setw(20) << "Program" << setw(10) << "Semester" << "\n";
    cout << "------------------------------------------------------------------------\n";

    for (auto &p : matchedStudents)
    {
        auto s = p.second;
        cout << left << setw(15) << s.getRollNumber() << setw(30) << s.getName() << setw(20) << s.getProgram() << setw(10) << s.getSemester() << "\n";
    }
}

// ============ EXAM OPERATIONS ============
void ExamManagementSystem::createExam()
{
    string subjectCode, subjectName, date, time, type, durationStr, examId;
    int durationHours, durationMinutes, marks, passMarks, semester;
    bool validSubject = false;
    int choice;

    // Loop until valid subject is found
    while (!validSubject)
    {
        clearScreen();
        cout << "========================================\n";
        cout << "          CREATE NEW EXAM\n";
        cout << "========================================\n\n";

        cout << "Subject Code: ";
        cin >> subjectCode;
        cin.ignore();

        cout << "Subject Name: ";
        getline(cin, subjectName);

        // Validate subject code and name
        if (subjects.count(subjectCode))
        {
            if (subjects[subjectCode].name == subjectName)
            {
                validSubject = true;
                semester = subjects[subjectCode].semester;
            }
            else
            {
                cout << "\nError: Subject name does not match the code in database.\n";
                cout << "Correct subject name for " << subjectCode << " is: " << subjects[subjectCode].name << "\n";
                pause();
            }
        }
        else
        {
            cout << "\nError: Subject code not found in database.\n";
            pause();
        }
    }

    // Display type options
    clearScreen();
    cout << "========================================\n";
    cout << "          CREATE NEW EXAM\n";
    cout << "========================================\n\n";
    cout << "Subject Code: " << subjectCode << "\n";
    cout << "Subject Name: " << subjectName << "\n\n";

    cout << "Select Exam Type:\n";
    cout << "  [1] Viva\n";
    cout << "  [2] Test\n";
    cout << "  [3] MCQ\n";
    cout << "  [4] Assessment\n";
    cout << "  [5] Lab/Practical\n";
    cout << "Enter choice: ";

    int typeChoice;
    cin >> typeChoice;

    switch (typeChoice)
    {
    case 1:
        type = "Viva";
        break;
    case 2:
        type = "Test";
        break;
    case 3:
        type = "MCQ";
        break;
    case 4:
        type = "Assessment";
        break;
    case 5:
        type = "Lab/Practical";
        break;
    default:
        cout << "Invalid choice. Setting type to Test.\n";
        type = "Test";
    }

    // Generate Exam ID as SubjectCode-Type
    examId = subjectCode + "-" + type;

    // Check if exam ID already exists
    if (exams.count(examId))
    {
        cout << "\nError: " << examId << " already exists.\n";
        cout << "An exam for this subject with type '" << type << "' is already scheduled.\n";
        pause();
        return;
    }

    clearScreen();
    cout << "========================================\n";
    cout << "          CREATE NEW EXAM\n";
    cout << "========================================\n\n";
    cout << "Subject Code: " << subjectCode << "\n";
    cout << "Subject Name: " << subjectName << "\n";
    cout << "Exam Type: " << type << "\n";
    cout << "Exam ID: " << examId << "\n\n";

    // Get exam details with date validation
    bool validDate = false;
    while (!validDate)
    {
        cout << "Date (YYYY-MM-DD): ";
        cin >> date;
        cin.ignore();

        // Validate that date is not in the past
        string currentDate = getCurrentDate();
        if (date < currentDate)
        {
            cout << "\nError: Cannot schedule exam in the past. Current date is " << currentDate << "\n";
            cout << "Please enter a future date.\n";
            pause();
            clearScreen();
            cout << "========================================\n";
            cout << "          CREATE NEW EXAM\n";
            cout << "========================================\n\n";
            cout << "Subject Code: " << subjectCode << "\n";
            cout << "Subject Name: " << subjectName << "\n";
            cout << "Exam Type: " << type << "\n";
            cout << "Exam ID: " << examId << "\n\n";
            continue;
        }
        validDate = true;
    }

    // Check for exams on the same date
    bool sameDateExists = false;
    for (auto &p : exams)
    {
        if (p.second.getDate() == date)
        {
            sameDateExists = true;
            cout << "\nWarning: Another exam is scheduled on this day.\n";
            cout << "Exam: " << p.first << " - " << p.second.getSubject() << " at " << p.second.getTime() << "\n";
            break;
        }
    }

    if (sameDateExists)
    {
        cout << "Are you sure? (1=Yes, 0=No): ";
        cin >> choice;
        if (choice != 1)
        {
            cout << "Exam creation cancelled.\n";
            pause();
            return;
        }
        cin.ignore();
    }

    // Get exam time with validation for past times
    bool validTime = false;
    while (!validTime)
    {
        cout << "\nTime (HH:MM): ";
        getline(cin, time);

        // If exam is scheduled for today, check that time is not in the past
        string currentDate = getCurrentDate();
        if (date == currentDate)
        {
            string currentTime = getCurrentTime();
            if (compareTime(time, currentTime) <= 0)
            {
                cout << "\nError: Cannot schedule exam at a past time. Current time is " << currentTime << "\n";
                cout << "Please enter a future time.\n";
                continue;
            }
        }

        validTime = true;
    }

    // Check for exams at the same time
    bool sameTimeExists = false;
    for (auto &p : exams)
    {
        if (p.second.getTime() == time && p.second.getDate() == date)
        {
            sameTimeExists = true;
            cout << "\nError: Another exam is scheduled at the same time on this date.\n";
            cout << "Exam: " << p.first << " - " << p.second.getSubject() << "\n";
            cout << "Please enter a different time.\n";
            pause();
            // Restart the exam creation process
            createExam();
            return;
        }
    }

    cout << "\nDuration (HH:MM): ";
    getline(cin, durationStr);

    // Parse duration from HH:MM format
    size_t colonPos = durationStr.find(':');
    if (colonPos != string::npos)
    {
        try
        {
            durationHours = stoi(durationStr.substr(0, colonPos));
            durationMinutes = stoi(durationStr.substr(colonPos + 1));
        }
        catch (...)
        {
            cout << "Invalid duration format. Setting to 3:00.\n";
            durationHours = 3;
            durationMinutes = 0;
        }
    }
    else
    {
        cout << "Invalid duration format. Setting to 3:00.\n";
        durationHours = 3;
        durationMinutes = 0;
    }

    cout << "\nMarks: ";
    cin >> marks;

    // Calculate pass marks as 40% of total marks
    passMarks = (marks * 40) / 100;

    // Create exam with new constructor
    exams[examId] = Exam(examId, subjectName, date, time, type, durationHours, durationMinutes, marks, passMarks, semester);

    cout << "\nExam created successfully!\n";
    cout << "Exam ID: " << examId << "\n";
    cout << "Pass marks (40%): " << passMarks << "\n";
}

void ExamManagementSystem::viewAllExams()
{
    for (auto &p : exams)
    {
        auto e = p.second;
        string status = getExamStatus(e.getDate(), e.getTime(), e.getDurationHours(), e.getDurationMinutes());
        cout << "\nExam ID: " << e.getId()
             << "\nSubject: " << e.getSubject()
             << "\nDate: " << e.getDate()
             << "\nTime: " << e.getTime()
             << "\nType: " << e.getType()
             << "\nDuration: " << e.getDurationHours() << "h " << e.getDurationMinutes() << "m"
             << "\nTotal Marks: " << e.getTotalMarks()
             << "\nPass Marks: " << e.getPassMarks()
             << "\nStatus: " << status << "\n";
    }
}

void ExamManagementSystem::viewAllExamsReport()
{
    if (exams.empty())
    {
        cout << "No exams found.\n";
        return;
    }

    vector<pair<string, Exam>> examsList;
    for (auto &p : exams)
    {
        examsList.push_back(p);
    }
    sort(examsList.begin(), examsList.end(), [](const pair<string, Exam> &a, const pair<string, Exam> &b)
         { return a.second.getId() < b.second.getId(); });

    cout << "\n========== ALL EXAMS ==========\n";
    cout << "\n"
         << left << setw(18) << "ID" << setw(30) << "Subject" << setw(12) << "Date" << setw(8) << "Time" << setw(12)<< "Full Marks" << setw(12) << "Pass Marks" << setw(12) << "Status" << "\n";
    cout << "------------------------------------------------------------------------------------------------\n";
    for (auto &p : examsList)
    {
        auto e = p.second;
        string status = getExamStatus(e.getDate(), e.getTime(), e.getDurationHours(), e.getDurationMinutes());
        cout << left << setw(18) << e.getId() << setw(30) << e.getSubject() << setw(12) << e.getDate()
             << setw(8) << e.getTime() << setw(12) << e.getTotalMarks() << setw(12) << e.getPassMarks() << setw(12) << status << "\n";
    }
}

void ExamManagementSystem::deleteExam()
{
    string examId;
    cout << "Enter Exam ID to delete: ";
    cin >> examId;

    if (!exams.count(examId))
    {
        cout << "Exam not found.\n";
        return;
    }

    auto e = exams[examId];
    cout << "\n========== DELETE EXAM CONFIRMATION ==========\n";
    cout << "Exam ID: " << e.getId() << "\n";
    cout << "Subject: " << e.getSubject() << "\n";
    cout << "Date: " << e.getDate() << "\n";
    cout << "Time: " << e.getTime() << "\n";
    cout << "\nAre you sure you want to delete this exam? (1=Yes, 0=No): ";
    
    int choice;
    if (!(cin >> choice) || choice != 1)
    {
        cout << "Deletion cancelled.\n";
        return;
    }

    // Check if there are any results or attendance for this exam
    int resultCount = 0, attendanceCount = 0;
    for (auto &p : results)
    {
        if (p.second.getExamId() == examId)
            resultCount++;
    }
    for (auto &p : attendance)
    {
        size_t pos = p.first.find("_");
        if (pos != string::npos)
        {
            string eid = p.first.substr(pos + 1);
            if (eid == examId)
                attendanceCount++;
        }
    }

    if (resultCount > 0 || attendanceCount > 0)
    {
        cout << "\nWarning: This exam has " << resultCount << " result(s) and " 
             << attendanceCount << " attendance record(s).\n";
        cout << "These will also be deleted. Continue? (1=Yes, 0=No): ";
        if (!(cin >> choice) || choice != 1)
        {
            cout << "Deletion cancelled.\n";
            return;
        }

        // Delete related results and attendance
        vector<string> keysToDelete;
        for (auto &p : results)
        {
            if (p.second.getExamId() == examId)
                keysToDelete.push_back(p.first);
        }
        for (auto &key : keysToDelete)
            results.erase(key);

        keysToDelete.clear();
        for (auto &p : attendance)
        {
            size_t pos = p.first.find("_");
            if (pos != string::npos)
            {
                string eid = p.first.substr(pos + 1);
                if (eid == examId)
                    keysToDelete.push_back(p.first);
            }
        }
        for (auto &key : keysToDelete)
            attendance.erase(key);
    }

    exams.erase(examId);
    cout << "\nExam deleted successfully.\n";
}

// Helper function to get all students (semester 3)
vector<pair<int, Student>> ExamManagementSystem::getStudentsForSemester(int semester)
{
    vector<pair<int, Student>> semesterStudents;
    int index = 1;
    
    for (auto &p : students)
    {
        semesterStudents.push_back({index++, p.second});
    }
    
    sort(semesterStudents.begin(), semesterStudents.end(), 
         [](const pair<int, Student> &a, const pair<int, Student> &b)
         { return a.second.getRollNumber() < b.second.getRollNumber(); });
    
    return semesterStudents;
}

// Helper function to extract subject code from exam ID (e.g., "E01" from "E01-Viva")
string ExamManagementSystem::extractSubjectFromExamId(string examId)
{
    size_t dashPos = examId.find('-');
    if (dashPos != string::npos)
    {
        return examId.substr(0, dashPos);
    }
    return examId;
}

// Helper function to verify if teacher is authorized for the exam
bool ExamManagementSystem::isTeacherAuthorized(string teacherId, string examId)
{
    if (!teachers.count(teacherId))
        return false;

    string teacherSubject = teachers[teacherId].getSubject();
    string examSubject = extractSubjectFromExamId(examId);

    return teacherSubject == examSubject;
}

// ============ ATTENDANCE OPERATIONS ============
void ExamManagementSystem::markAttendance(string teacherId)
{
    string eid;
    cout << "Enter Exam ID: ";
    cin >> eid;

    // Validate exam ID exists
    if (!exams.count(eid))
    {
        cout << "Invalid exam ID. Please enter a valid exam ID.\n";
        pause();
        return;
    }

    // Check if exam time has started (real-time validation)
    string examDate = exams[eid].getDate();
    string examTime = exams[eid].getTime();
    
    if (!isExamStarted(examDate, examTime))
    {
        cout << "\nError: Cannot mark attendance yet.\n";
        cout << "Exam scheduled for: " << examDate << " at " << examTime << "\n";
        cout << "Current date and time: " << getCurrentDate() << " at " << getCurrentTime() << "\n";
        cout << "Attendance can only be marked when the exam time has started.\n";
        pause();
        return;
    }

    // Verify teacher is authorized for this exam
    if (!teacherId.empty() && !isTeacherAuthorized(teacherId, eid))
    {
        cout << "\nError: You are not authorized to mark attendance for this exam.\n";
        cout << "Your subject: " << teachers[teacherId].getSubject() << "\n";
        cout << "Exam subject: " << extractSubjectFromExamId(eid) << "\n";
        pause();
        return;
    }

    auto classStudents = getStudentsForSemester(3);

    if (classStudents.empty())
    {
        cout << "No students found in semester 3.\n";
        pause();
        return;
    }

    clearScreen();
    cout << "\n========== MARK ATTENDANCE FOR EXAM " << eid << " ==========\n";
    cout << "Semester: 3\n";
    cout << "Total Students: " << classStudents.size() << "\n";
    cout << "(Enter 1 for Present, 0 for Absent)\n";
    cout << "========================================\n\n";

    for (auto &p : classStudents)
    {
        auto s = p.second;
        string roll = s.getRollNumber();
        
        while (true)
        {
            cout << "[" << p.first << "] " << s.getName() << " (" << roll << "): ";
            
            int choice;
            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter 0 or 1.\n";
                continue;
            }

            if (choice != 0 && choice != 1)
            {
                cout << "Invalid input. Please enter 0 or 1.\n";
                continue;
            }

            attendance[roll + "_" + eid] = (choice == 1);

            if (choice == 1)
            {
                cout << "Present\n";
            }
            else
            {
                cout << "Absent\n";
            }
            cout << "\n";
            break;
        }
    }

    cout << "========================================\n";
    cout << "Attendance marked for " << classStudents.size() << " students.\n";
    pause();
}

void ExamManagementSystem::viewAttendance(string teacherId)
{
    string eid;
    cout << "Enter Exam ID: ";
    cin >> eid;

    // Validate exam ID exists
    if (!exams.count(eid))
    {
        cout << "Invalid exam ID.\n";
        return;
    }

    // Verify teacher is authorized for this exam (if teacher login)
    if (!teacherId.empty() && !isTeacherAuthorized(teacherId, eid))
    {
        cout << "\nError: You are not authorized to view attendance for this exam.\n";
        cout << "Your subject: " << teachers[teacherId].getSubject() << "\n";
        cout << "Exam subject: " << extractSubjectFromExamId(eid) << "\n";
        return;
    }

    bool found = false;
    cout << "\n========== ATTENDANCE FOR EXAM " << eid << " ==========\n";
    cout << "\n"
         << left << setw(15) << "Roll Number" << setw(30) << "Name" << setw(15) << "Status" << "\n";
    cout << "------------------------------------------------------------------------\n";

    vector<pair<string, bool>> attendanceList;
    for (auto &p : attendance)
    {
        string key = p.first;
        size_t pos = key.find("_");
        if (pos != string::npos)
        {
            string examId = key.substr(pos + 1);
            if (examId == eid)
            {
                string roll = key.substr(0, pos);
                attendanceList.push_back({roll, p.second});
                found = true;
            }
        }
    }

    sort(attendanceList.begin(), attendanceList.end(), [](const pair<string, bool> &a, const pair<string, bool> &b)
         { return a.first < b.first; });

    for (auto &p : attendanceList)
    {
        string roll = p.first;
        bool isPresent = p.second;
        string status = isPresent ? "Present" : "Absent";
        string studentName = "N/A";

        if (students.count(roll))
        {
            studentName = students[roll].getName();
        }

        cout << left << setw(15) << roll << setw(30) << studentName << setw(15) << status << "\n";
    }

    if (!found)
        cout << "No attendance records found for this exam.\n";
}

// ============ MARKS OPERATIONS ============
void ExamManagementSystem::enterMarks(string teacherId)
{
    string eid;
    cout << "Enter Exam ID: ";
    cin >> eid;

    // Validate exam ID exists
    if (!exams.count(eid))
    {
        cout << "Invalid exam ID. Please enter a valid exam ID.\n";
        pause();
        return;
    }

    // Check if exam time has passed (real-time validation)
    string examDate = exams[eid].getDate();
    string examTime = exams[eid].getTime();
    int durationHours = exams[eid].getDurationHours();
    int durationMinutes = exams[eid].getDurationMinutes();
    
    if (!isExamEnded(examDate, examTime, durationHours, durationMinutes))
    {
        cout << "\nError: Cannot enter marks yet.\n";
        cout << "Exam scheduled for: " << examDate << " at " << examTime << "\n";
        cout << "Current date and time: " << getCurrentDate() << " at " << getCurrentTime() << "\n";
        cout << "Marks can only be entered after the exam time has passed.\n";
        pause();
        return;
    }

    // Verify teacher is authorized for this exam
    if (!teacherId.empty() && !isTeacherAuthorized(teacherId, eid))
    {
        cout << "\nError: You are not authorized to enter marks for this exam.\n";
        cout << "Your subject: " << teachers[teacherId].getSubject() << "\n";
        cout << "Exam subject: " << extractSubjectFromExamId(eid) << "\n";
        pause();
        return;
    }

    int totalMarks = exams[eid].getTotalMarks();
    auto classStudents = getStudentsForSemester(3);

    if (classStudents.empty())
    {
        cout << "No students found in semester 3.\n";
        pause();
        return;
    }

    clearScreen();
    cout << "\n========== ENTER MARKS FOR EXAM " << eid << " ==========\n";
    cout << "Semester: 3\n";
    cout << "Total Marks: " << totalMarks << "\n";
    cout << "(Only mark present students)\n";
    cout << "========================================\n\n";

    for (auto &p : classStudents)
    {
        auto s = p.second;
        string roll = s.getRollNumber();
        string key = roll + "_" + eid;

        // Check attendance
        if (!attendance[key])
        {
            cout << "[" << p.first << "] " << s.getName() << " (" << roll << "): ABSENT - SKIP\n";
            continue;
        }

        while (true)
        {
            cout << "[" << p.first << "] " << s.getName() << " (" << roll << "): ";
            
            double marks;
            if (!(cin >> marks))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a number (0-" << totalMarks << ").\n";
                continue;
            }

            // Validate marks are not negative and don't exceed total marks
            if (marks < 0)
            {
                cout << "Error: Marks cannot be negative.\n";
                continue;
            }

            if (marks > totalMarks)
            {
                cout << "Error: Marks cannot exceed " << totalMarks << ".\n";
                continue;
            }

            // Check if result already exists and ask for confirmation
            if (results.count(key))
            {
                cout << "Warning: Previous marks = " << results[key].getMarks() << ". Overwrite? (1=Yes, 0=No): ";
                int confirmChoice;
                if (!(cin >> confirmChoice) || confirmChoice != 1)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Cancelled - Moving to next student\n\n";
                    break;
                }
            }

            results[key] = Result(roll, eid, marks);
            cout << "✓ " << marks << " marks\n\n";
            break;
        }
    }

    cout << "========================================\n";
    cout << "Marks entry completed.\n";
    pause();
}

// ============ RESULT OPERATIONS ============
void ExamManagementSystem::viewResult(string teacherId)
{
    if (results.empty())
    {
        cout << "No results found.\n";
        return;
    }

    cout << "\n========== VIEW RESULTS ==========\n";
    cout << "\n  [1] View Specific Exam Results\n";
    cout << "  [2] View All Results\n";
    cout << "  [0] Back\n";
    cout << "\n----------------------------------------\n";
    cout << "  Enter choice: ";

    int choice;
    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (choice == 0)
        return;

    if (choice == 1)
    {
        string eid;
        cout << "\nEnter Exam ID: ";
        cin >> eid;

        if (!exams.count(eid))
        {
            cout << "Invalid exam ID.\n";
            return;
        }

        // Verify teacher is authorized for this exam (if teacher login)
        if (!teacherId.empty() && !isTeacherAuthorized(teacherId, eid))
        {
            cout << "\nError: You are not authorized to view results for this exam.\n";
            cout << "Your subject: " << teachers[teacherId].getSubject() << "\n";
            cout << "Exam subject: " << extractSubjectFromExamId(eid) << "\n";
            return;
        }

        vector<pair<string, double>> examStudents;
        for (auto &p : results)
        {
            if (p.second.getExamId() == eid)
            {
                examStudents.push_back({p.second.getStudentId(), p.second.getMarks()});
            }
        }

        if (examStudents.empty())
        {
            cout << "\nNo results found for exam " << eid << ".\n";
            return;
        }

        sort(examStudents.begin(), examStudents.end(), [](const pair<string, double> &a, const pair<string, double> &b)
             { return a.first < b.first; });

        cout << "\n========== RESULTS FOR " << eid << " ==========\n";
        cout << "\n" << left << setw(15) << "Roll Number" << setw(30) << "Name" << setw(12) << "Marks" << setw(10) << "Status" << "\n";
        cout << "------------------------------------------------------------------------\n";

        for (auto &student : examStudents)
        {
            string roll = student.first;
            double marks = student.second;
            string studentName = "N/A";

            if (students.count(roll))
            {
                studentName = students[roll].getName();
            }

            cout << left << setw(15) << roll << setw(30) << studentName << setw(12) << marks
                 << setw(10) << (isResultPass(eid, marks) ? "PASS" : "FAIL") << "\n";
        }
    }
    else if (choice == 2)
    {
        // Group results by exam ID
        map<string, vector<pair<string, double>>> examResults;
        for (auto &p : results)
        {
            string eid = p.second.getExamId();
            // If teacher is viewing, only show their subject's results
            if (!teacherId.empty() && !isTeacherAuthorized(teacherId, eid))
                continue;
            examResults[eid].push_back({p.second.getStudentId(), p.second.getMarks()});
        }

        if (examResults.empty())
        {
            if (!teacherId.empty())
                cout << "\nNo results found for your subject.\n";
            else
                cout << "\nNo results found.\n";
            return;
        }

        // Sort students within each exam
        for (auto &er : examResults)
        {
            sort(er.second.begin(), er.second.end(), [](const pair<string, double> &a, const pair<string, double> &b)
                 { return a.first < b.first; });
        }

        cout << "\n========== ALL RESULTS ==========\n";
        for (auto &er : examResults)
        {
            string examId = er.first;
            cout << "\n========== RESULTS FOR " << examId << " ==========\n";
            cout << "\n" << left << setw(15) << "Roll Number" << setw(30) << "Name" << setw(12) << "Marks" << setw(10) << "Status" << "\n";
            cout << "------------------------------------------------------------------------\n";
            
            for (auto &student : er.second)
            {
                string roll = student.first;
                double marks = student.second;
                string studentName = "N/A";
                
                if (students.count(roll))
                {
                    studentName = students[roll].getName();
                }
                
                cout << left << setw(15) << roll << setw(30) << studentName << setw(12) << marks
                     << setw(10) << (isResultPass(examId, marks) ? "PASS" : "FAIL") << "\n";
            }
        }
    }
}

void ExamManagementSystem::viewAllResultsReport()
{
    if (results.empty())
    {
        cout << "No results found.\n";
        return;
    }

    // Group results by exam ID
    map<string, vector<pair<string, double>>> examResults;
    for (auto &p : results)
    {
        examResults[p.second.getExamId()].push_back({p.second.getStudentId(), p.second.getMarks()});
    }

    // Sort students within each exam
    for (auto &er : examResults)
    {
        sort(er.second.begin(), er.second.end(), [](const pair<string, double> &a, const pair<string, double> &b)
             { return a.first < b.first; });
    }

    cout << "\n========== ALL RESULTS ==========\n";
    for (auto &er : examResults)
    {
        string examId = er.first;
        cout << "\n========== RESULTS FOR " << examId << " ==========\n";
        cout << "\n" << left << setw(15) << "Roll Number" << setw(30) << "Name" << setw(12) << "Marks" << setw(10) << "Status" << "\n";
        cout << "------------------------------------------------------------------------\n";
        
        for (auto &student : er.second)
        {
            string roll = student.first;
            double marks = student.second;
            string studentName = "N/A";
            
            if (students.count(roll))
            {
                studentName = students[roll].getName();
            }
            
            cout << left << setw(15) << roll << setw(30) << studentName << setw(12) << marks
                 << setw(10) << (isResultPass(examId, marks) ? "PASS" : "FAIL") << "\n";
        }
    }
}

void ExamManagementSystem::viewStudentReport(string roll)
{
    bool found = false;
    for (auto &p : results)
    {
        if (p.second.getStudentId() == roll)
        {
            found = true;
            double m = p.second.getMarks();
            string examId = p.second.getExamId();
            cout << "\nExam: " << examId
                 << " | Marks: " << m
                 << " | " << (isResultPass(examId, m) ? "PASS" : "FAIL") << "\n";
        }
    }
    if (!found)
        cout << "No results found\n";
}

// ============ REPORTS ============
void ExamManagementSystem::viewPassFailSummary()
{
    string eid;
    cout << "Exam ID: ";
    cin >> eid;

    int pass = 0, fail = 0;
    double highestMarks = -1;
    string topper = "";

    for (auto &p : results)
    {
        if (p.second.getExamId() == eid)
        {
            double m = p.second.getMarks();
            if (isResultPass(eid, m))
                pass++;
            else
                fail++;

            if (m > highestMarks)
            {
                highestMarks = m;
                topper = p.second.getStudentId();
            }
        }
    }

    cout << "\n========== PASS/FAIL SUMMARY FOR EXAM " << eid << " ==========\n";
    cout << "Pass: " << pass << "\n";
    cout << "Fail: " << fail << "\n";
    if (topper != "")
    {
        cout << "Topper: " << topper << " (" << highestMarks << " marks)\n";
    }
    else
    {
        cout << "No results found for this exam.\n";
    }
}

void ExamManagementSystem::viewTopperPerExam()
{
    cout << "\n========== TOPPER PER EXAM ==========\n";

    for (auto &exam : exams)
    {
        string eid = exam.first;
        double highestMarks = -1;
        string topper = "";

        for (auto &p : results)
        {
            if (p.second.getExamId() == eid)
            {
                double m = p.second.getMarks();
                if (m > highestMarks)
                {
                    highestMarks = m;
                    topper = p.second.getStudentId();
                }
            }
        }

        cout << "\nExam (" << eid << "): ";
        if (topper != "")
        {
            cout << topper << " (" << highestMarks << " marks)\n";
        }
        else
        {
            cout << "No results yet\n";
        }
    }
}

void ExamManagementSystem::viewExamStatistics()
{
    if (exams.empty())
    {
        cout << "No exams found.\n";
        return;
    }

    cout << "\n========== EXAM STATISTICS ==========\n";
    cout << "\n" << left << setw(20) << "Exam ID" << setw(15) << "Total Students" << setw(10) << "Pass" 
         << setw(10) << "Fail" << setw(15) << "Pass %" << setw(15) << "Avg Marks" << "\n";
    cout << "------------------------------------------------------------------------\n";

    for (auto &exam : exams)
    {
        string eid = exam.first;
        int totalStudents = 0;
        int passCount = 0;
        int failCount = 0;
        double totalMarks = 0;

        for (auto &p : results)
        {
            if (p.second.getExamId() == eid)
            {
                totalStudents++;
                double m = p.second.getMarks();
                totalMarks += m;
                if (isResultPass(eid, m))
                    passCount++;
                else
                    failCount++;
            }
        }

        failCount = totalStudents - passCount;
        double passPercentage = totalStudents > 0 ? (passCount * 100.0 / totalStudents) : 0;
        double avgMarks = totalStudents > 0 ? (totalMarks / totalStudents) : 0;

        if (totalStudents == 0)
            continue;

        cout << left << setw(20) << eid << setw(15) << totalStudents << setw(10) << passCount 
             << setw(10) << failCount << fixed << setprecision(2) << setw(15) << passPercentage << setw(15) << avgMarks << "\n";
    }
}

void ExamManagementSystem::viewClassPerformance()
{
    if (results.empty())
    {
        cout << "No results found.\n";
        return;
    }

    int totalResults = 0;
    int totalPass = 0;
    double totalMarksAll = 0;
    double highestMark = -1;
    double lowestMark = 1000;
    string topperRoll = "";
    string failerRoll = "";

    for (auto &p : results)
    {
        totalResults++;
        double m = p.second.getMarks();
        string examId = p.second.getExamId();
        totalMarksAll += m;

        if (isResultPass(examId, m))
            totalPass++;
        else
        {
            // Track lowest mark only among failed results
            if (m < lowestMark)
            {
                lowestMark = m;
                failerRoll = p.second.getStudentId();
            }
        }

        if (m > highestMark)
        {
            highestMark = m;
            topperRoll = p.second.getStudentId();
        }
    }

    int failCount = totalResults - totalPass;
    double passPercentage = (totalPass * 100.0 / totalResults);
    double failPercentage = (failCount * 100.0 / totalResults);
    double avgMarks = totalMarksAll / totalResults;

    cout << "\n========== CLASS PERFORMANCE SUMMARY ==========\n";
    cout << "\nTotal Results Entered: " << totalResults << "\n";
    cout << "Total Pass: " << totalPass << "\n";
    cout << "Total Fail: " << failCount << "\n";
    cout << fixed << setprecision(2);
    cout << "Overall Pass Percentage: " << passPercentage << "%\n";
    cout << "Overall Fail Percentage: " << failPercentage << "%\n";
    cout << "Average Marks (Overall): " << avgMarks << "\n";
    cout << "Highest Mark: " << highestMark << " (Student: " << topperRoll << ")\n";
    if (failerRoll != "")
        cout << "Lowest Mark: " << lowestMark << " (Student: " << failerRoll << ")\n";
    else
        cout << "Lowest Mark: N/A (All students passed)\n";
}

void ExamManagementSystem::viewMarksDistribution()
{
    if (results.empty())
    {
        cout << "No results found.\n";
        return;
    }

    cout << "\n========== MARKS DISTRIBUTION ANALYSIS ==========\n";

    map<string, vector<double>> examMarks;
    for (auto &p : results)
    {
        examMarks[p.second.getExamId()].push_back(p.second.getMarks());
    }

    cout << "\n" << left << setw(20) << "Exam ID" << setw(12) << "Min Marks" << setw(12) << "Max Marks" 
         << setw(15) << "Median Marks" << setw(15) << "Std Dev" << "\n";
    cout << "------------------------------------------------------------------------\n";

    for (auto &em : examMarks)
    {
        auto marks = em.second;
        sort(marks.begin(), marks.end());

        double minMarks = marks.front();
        double maxMarks = marks.back();
        double medianMarks = 0;
        
        if (marks.size() % 2 == 0)
            medianMarks = (marks[marks.size()/2 - 1] + marks[marks.size()/2]) / 2.0;
        else
            medianMarks = marks[marks.size()/2];

        // Calculate standard deviation
        double sum = 0;
        for (auto &m : marks)
            sum += m;
        double mean = sum / marks.size();
        
        double variance = 0;
        for (auto &m : marks)
            variance += (m - mean) * (m - mean);
        variance /= marks.size();
        double stdDev = sqrt(variance);

        cout << left << setw(20) << em.first << fixed << setprecision(2) << setw(12) << minMarks 
             << setw(12) << maxMarks << setw(15) << medianMarks << setw(15) << stdDev << "\n";
    }
}

// ============ STUDENT PANEL ============
void ExamManagementSystem::viewStudentProfile(string roll)
{
    if (students.count(roll))
    {
        auto s = students[roll];
        cout << "\n========== MY PROFILE ==========\n";
        cout << "Roll Number: " << s.getRollNumber() << "\n";
        cout << "Name: " << s.getName() << "\n";
        cout << "Program: " << s.getProgram() << "\n";
        cout << "Semester: " << s.getSemester() << "\n";
    }
    else
    {
        cout << "Student not found.\n";
    }
}

void ExamManagementSystem::viewStudentExams(string roll)
{
    if (!students.count(roll))
    {
        cout << "Student not found.\n";
        return;
    }

    vector<pair<string, Exam>> relevantExams;

    // Get UPCOMING exams and COMPLETED exams with published results for the student's semester
    for (auto &p : exams)
    {
        if (p.second.getSemester() == 3)
        {
            string examStatus = getExamStatus(p.second.getDate(), p.second.getTime(), p.second.getDurationHours(), p.second.getDurationMinutes());
            
            // Check if marks have been entered for this exam
            bool marksPublished = false;
            for (auto &r : results)
            {
                if (r.second.getExamId() == p.first && r.second.getStudentId() == roll)
                {
                    marksPublished = true;
                    break;
                }
            }
            
            // Include UPCOMING exams always
            if (examStatus == "UPCOMING")
            {
                relevantExams.push_back(p);
            }
            // Include COMPLETED exams only if marks have been published
            else if (examStatus == "COMPLETED" && marksPublished)
            {
                relevantExams.push_back(p);
            }
        }
    }

    if (relevantExams.empty())
    {
        cout << "No exams to display for your semester.\n";
        return;
    }

    sort(relevantExams.begin(), relevantExams.end(), [](const pair<string, Exam> &a, const pair<string, Exam> &b)
    { return a.second.getDate() < b.second.getDate(); });

    cout << "\n========== MY EXAMS (SEMESTER 3) ==========\n";
    cout << "\n"
         << left << setw(18) << "ID" << setw(20) << "Subject" << setw(12) << "Date" << setw(8) << "Time" << setw(12) << "Full Marks" << setw(12) << "Pass Marks" << setw(15) << "Status" << "\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";
    for (auto &p : relevantExams)
    {
        auto e = p.second;
        string status = "UPCOMING";
        
        string examStatus = getExamStatus(e.getDate(), e.getTime(), e.getDurationHours(), e.getDurationMinutes());
        
        // Check if marks have been entered for this exam
        bool marksPublished = false;
        for (auto &r : results)
        {
            if (r.second.getExamId() == e.getId() && r.second.getStudentId() == roll)
            {
                marksPublished = true;
                break;
            }
        }
        
        if (marksPublished || examStatus == "COMPLETED")
        {
            status = "RESULT PUBLISHED";
        }
        
        cout << left << setw(18) << e.getId() << setw(20) << e.getSubject() << setw(12) << e.getDate()
             << setw(8) << e.getTime() << setw(12) << e.getTotalMarks() << setw(12) << e.getPassMarks() << setw(15) << status << "\n";
    }
}

void ExamManagementSystem::viewStudentResultsDetailed(string roll)
{
    vector<pair<string, double>> studentExams;
    int passCount = 0;
    double totalMarks = 0;
    int attendedExams = 0;

    for (auto &p : results)
    {
        if (p.second.getStudentId() == roll)
        {
            string examId = p.second.getExamId();
            double marks = p.second.getMarks();
            studentExams.push_back({examId, marks});
            totalMarks += marks;
            attendedExams++;
            if (isResultPass(examId, marks))
                passCount++;
        }
    }

    if (studentExams.empty())
    {
        cout << "\n========== MY RESULTS ==========\n";
        cout << "\nNo results found.\n";
        return;
    }

    sort(studentExams.begin(), studentExams.end(), [](const pair<string, double> &a, const pair<string, double> &b)
         { return a.first < b.first; });

    cout << "\n========== MY RESULTS ==========\n";
    cout << "\n" << left << setw(20) << "Exam ID" << setw(15) << "Marks" << setw(15) << "Pass Marks" << setw(10) << "Status" << "\n";
    cout << "------------------------------------------------------------------------\n";

    for (auto &exam : studentExams)
    {
        string examId = exam.first;
        double marks = exam.second;
        int passMarks = 0;

        if (exams.count(examId))
        {
            passMarks = exams[examId].getPassMarks();
        }

        cout << left << setw(20) << examId << setw(15) << marks << setw(15) << passMarks
             << setw(10) << (isResultPass(examId, marks) ? "PASS" : "FAIL") << "\n";
    }

    cout << "\n------------------------------------------------------------------------\n";
    cout << "Total Exams: " << attendedExams << " | Pass: " << passCount << " | Fail: " << (attendedExams - passCount) << "\n";
}
