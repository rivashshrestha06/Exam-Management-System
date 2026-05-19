#ifndef MODELS_H
#define MODELS_H

#include <string>

using namespace std;

// ==================== MODELS ====================
// -------------------- USER --------------------
class User
{
protected:
    string id, password, name;

public:
    User() {}
    User(string i, string pw, string n)
        : id(i), password(pw), name(n) {}

    virtual string getId() const { return id; }
    virtual string getPassword() const { return password; }
    virtual string getName() const { return name; }
    virtual ~User() {}
};

// -------------------- ADMIN --------------------
class Admin : public User
{
public:
    Admin() {}
    Admin(string i, string pw, string n)
        : User(i, pw, n) {}
};

// -------------------- STUDENT --------------------
class Student : public User
{
    string program;
    int semester;

public:
    Student() {}
    Student(string roll, string pw, string n, string p, int sem)
        : User(roll, pw, n), program(p), semester(sem) {}

    string getRollNumber() const { return id; }
    string getProgram() const { return program; }
    int getSemester() const { return semester; }
};

// -------------------- TEACHER --------------------
class Teacher : public User
{
    string subject;
public:
    Teacher() {}
    Teacher(string tid, string pw, string n, string subj = "")
        : User(tid, pw, n), subject(subj) {}

    string getTeacherId() const { return id; }
    string getSubject() const { return subject; }
};

// -------------------- SUBJECT --------------------
struct Subject
{
    string id, name;
    int credits, theory, practical, semester;

    Subject() {}
    Subject(string i, string n, int c, int t, int p, int s)
        : id(i), name(n), credits(c), theory(t), practical(p), semester(s) {}
};

// -------------------- EXAM --------------------
class Exam
{
    string id, subject, date, time, type;
    int durationHours, durationMinutes, marks, passMarks, semester;

public:
    Exam() {}
    Exam(string i, string s, string d, string t, string ty, int dh, int dm, int m, int p, int sem)
        : id(i), subject(s), date(d), time(t), type(ty), durationHours(dh), durationMinutes(dm), marks(m), passMarks(p), semester(sem) {}

    string getId() const { return id; }
    string getSubject() const { return subject; }
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getType() const { return type; }
    int getDurationHours() const { return durationHours; }
    int getDurationMinutes() const { return durationMinutes; }
    int getTotalMarks() const { return marks; }
    int getPassMarks() const { return passMarks; }
    int getSemester() const { return semester; }
};

// -------------------- RESULT --------------------
class Result
{
    string studentId, examId;
    double marks;

public:
    Result() {}
    Result(string s, string e, double m)
        : studentId(s), examId(e), marks(m) {}

    string getStudentId() const { return studentId; }
    string getExamId() const { return examId; }
    double getMarks() const { return marks; }
};

#endif
