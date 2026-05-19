#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <map>
#include "models.h"

using namespace std;

// ==================== FILE HANDLER CLASS ====================
class FileHandler
{
public:
    static void saveStudentsToFile(map<string, Student> &students);
    static void saveExamsToFile(map<string, Exam> &exams);
    static void saveResultsToFile(map<string, Result> &results);
    static void saveAttendanceToFile(map<string, bool> &attendance);
    
    static void loadSubjectsFromFile(map<string, Subject> &subjects);
    static void loadStudentsFromAllSemesters(map<string, Student> &students);
    static void loadExamsFromFile(map<string, Exam> &exams);
    static void loadResultsFromFile(map<string, Result> &results);
    static void loadAttendanceFromFile(map<string, bool> &attendance);
    static void loadTeachersFromFile(map<string, Teacher> &teachers);
};

#endif
