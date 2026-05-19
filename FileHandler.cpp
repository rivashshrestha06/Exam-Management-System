#include "FileHandler.h"
#include <fstream>
#include <sstream>

// ==================== FILE CONSTANTS ====================
static const string EXAM_FILE = "exams.txt";
static const string RESULT_FILE = "results.txt";
static const string ATTENDANCE_FILE = "attendance.txt";
static const string SUBJECTS_FILE = "subjects.txt";
static const string TEACHERS_FILE = "teachers.txt";

// ============ FILE OPERATIONS - SAVE ============
void FileHandler::saveStudentsToFile(map<string, Student> &students)
{
    // Save students to semester3.txt
    string filename = "semester3.txt";
    ofstream out(filename);
    
    // Write all students
    for (auto &p : students)
    {
        auto s = p.second;
        out << s.getRollNumber() << "|" << s.getPassword() << "|"
            << s.getName() << "|" << s.getProgram() << "|" << s.getSemester() << "\n";
    }
    out.close();
}

void FileHandler::saveExamsToFile(map<string, Exam> &exams)
{
    ofstream out(EXAM_FILE);
    for (auto &p : exams)
    {
        auto e = p.second;
        // Format duration as "HH hour : MM minutes"
        string durationStr = (e.getDurationHours() < 10 ? "0" : "") + to_string(e.getDurationHours()) + " hour : ";
        durationStr += (e.getDurationMinutes() < 10 ? "0" : "") + to_string(e.getDurationMinutes()) + " minutes";
        
        out << e.getId() << "|" << e.getSubject() << "|"
            << e.getDate() << "|" << e.getTime() << "|" << e.getType() << "|"
            << durationStr << "|"
            << e.getTotalMarks() << "|" << e.getPassMarks() << "|" << e.getSemester() << "\n";
    }
    out.close();
}

void FileHandler::saveResultsToFile(map<string, Result> &results)
{
    ofstream out(RESULT_FILE);
    for (auto &p : results)
    {
        auto r = p.second;
        out << r.getStudentId() << "|" << r.getExamId()
            << "|" << r.getMarks() << "\n";
    }
    out.close();
}

void FileHandler::saveAttendanceToFile(map<string, bool> &attendance)
{
    ofstream out(ATTENDANCE_FILE);
    for (auto &p : attendance)
    {
        out << p.first << "|" << p.second << "\n";
    }
    out.close();
}

// ============ FILE OPERATIONS - LOAD ============
void FileHandler::loadSubjectsFromFile(map<string, Subject> &subjects)
{
    ifstream in(SUBJECTS_FILE);
    string line;
    while (getline(in, line))
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name;
        int credits, theory, practical, semester;

        getline(ss, id, '|');
        getline(ss, name, '|');
        ss >> credits;
        ss.ignore();
        ss >> theory;
        ss.ignore();
        ss >> practical;
        ss.ignore();
        ss >> semester;

        subjects[id] = Subject(id, name, credits, theory, practical, semester);
    }
    in.close();
}

void FileHandler::loadStudentsFromAllSemesters(map<string, Student> &students)
{
    // Load students from semester 3 only
    string filename = "semester3.txt";
    ifstream in(filename);
    string line;
    while (getline(in, line))
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string roll, pass, name, prog;
        int sem;

        getline(ss, roll, '|');
        getline(ss, pass, '|');
        getline(ss, name, '|');
        getline(ss, prog, '|');
        ss >> sem;

        students[roll] = Student(roll, pass, name, prog, sem);
    }
    in.close();
}

void FileHandler::loadExamsFromFile(map<string, Exam> &exams)
{
    ifstream in(EXAM_FILE);
    string line;
    while (getline(in, line))
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, sub, date, time, type, durationStr;
        int dh, dm, marks, passMarks, sem;

        getline(ss, id, '|');
        getline(ss, sub, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, type, '|');
        getline(ss, durationStr, '|');
        
        // Parse duration from "HH hour : MM minutes" format
        size_t hourPos = durationStr.find(' ');
        size_t colonPos = durationStr.find(':');
        size_t minutesPos = durationStr.find(' ', colonPos + 1);
        
        if (hourPos != string::npos && colonPos != string::npos)
        {
            try
            {
                dh = stoi(durationStr.substr(0, hourPos));
                dm = stoi(durationStr.substr(colonPos + 2, minutesPos - colonPos - 2));
            }
            catch (...)
            {
                dh = 3;
                dm = 0;
            }
        }
        else
        {
            dh = 3;
            dm = 0;
        }
        
        ss >> marks;
        ss.ignore();
        ss >> passMarks;
        ss.ignore();
        ss >> sem;
        exams[id] = Exam(id, sub, date, time, type, dh, dm, marks, passMarks, sem);
    }
    in.close();
}

void FileHandler::loadResultsFromFile(map<string, Result> &results)
{
    ifstream in(RESULT_FILE);
    string line;
    while (getline(in, line))
    {
        stringstream ss(line);
        string sid, eid;
        double m;

        getline(ss, sid, '|');
        getline(ss, eid, '|');
        ss >> m;

        results[sid + "_" + eid] = Result(sid, eid, m);
    }
    in.close();
}

void FileHandler::loadAttendanceFromFile(map<string, bool> &attendance)
{
    ifstream in(ATTENDANCE_FILE);
    string line;
    while (getline(in, line))
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string key;
        bool val;

        getline(ss, key, '|');
        ss >> val;

        attendance[key] = val;
    }
    in.close();
}

void FileHandler::loadTeachersFromFile(map<string, Teacher> &teachers)
{
    ifstream in(TEACHERS_FILE);
    string line;
    while (getline(in, line))
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string tid, pw, name, subject;

        getline(ss, tid, '|');
        getline(ss, pw, '|');
        getline(ss, name, '|');
        getline(ss, subject, '|');

        teachers[tid] = Teacher(tid, pw, name, subject);
    }
    in.close();
}
