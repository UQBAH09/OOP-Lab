#include <iostream>
#include <string>
using namespace std;

#define STUDENT_NAME "UQBAH KHAN"
#define STUDENT_ID "24K-0614"

int generateHash(string password)
{
    int hash = 5381;
    for (char c : password)
    {
        hash = hash * 33 + c;
    }
    return hash;
}

// ------------------- User Base Class -------------------
class User
{
protected:
    string name;
    int id;
    string email;
    string permissions[5];
    int permissionCount;
    int hashed_password;

public:
    User(string name, int id, string perms[], int count, string email, string pass) : name(name), id(id), permissionCount(count), email(email), hashed_password(generateHash(pass))
    {
        for (int i = 0; i < permissionCount; i++)
        {
            permissions[i] = perms[i];
        }
    }

    virtual void display()
    {
        cout << "\nUser Name: " << name << "\nUser ID: " << id << "\nEmail: " << email << "\nPermissions: ";
        for (int i = 0; i < permissionCount; i++)
        {
            cout << permissions[i];
            if (i < permissionCount - 1)
                cout << ", ";
        }
        cout << endl;
    }

    bool authenticate(string password)
    {
        return generateHash(password) == hashed_password;
    }

    void acssesLab(string requiredPermission)
    {
        for (int i = 0; i < permissionCount; i++)
        {
            if (permissions[i] == requiredPermission)
            {
                cout << name << " has access to: " << requiredPermission << endl;
                return;
            }
        }
        cout << name << " does NOT have permission: " << requiredPermission << endl;
    }

    virtual string getRole()
    {
        return "User";
    }
};

// ------------------- Student Class -------------------
class Student : public User
{
protected:
    int assignments[5] = {0}; // 0 = not submitted, 1 = submitted
    int numOfAssignments = 0;

public:
    Student() : User("", 0, nullptr, 0, "", "")
    {
        numOfAssignments = 0;
        for (int i = 0; i < 5; i++)
            assignments[i] = 0;
    }

    Student(string name, int id, string perms[], int count, string email, string pass) : User(name, id, perms, count, email, pass) {}

    void giveAssignment()
    {
        if (numOfAssignments < 5)
        {
            assignments[numOfAssignments] = 0;
            numOfAssignments++;
        }
        else
        {
            cout << "Max assignments reached.\n";
        }
    }

    void submitAssignment(int num)
    {
        if (num < numOfAssignments)
        {
            assignments[num] = 1;
        }
        else
        {
            cout << "No assignment found.\n";
        }
    }

    void display() override
    {
        User::display();
        cout << "Assignments: ";
        for (int i = 0; i < numOfAssignments; i++)
        {
            cout << "A" << (i + 1) << "=" << (assignments[i] ? "Submitted" : "Pending") << " ";
        }
        cout << endl;
    }

    string getRole() override
    {
        return "Student";
    }
};

// ------------------- TA Class -------------------
class TeacherAssistant : public Student
{
    Student studentList[10];
    int numOfStd = 0;
    string projects[2];
    int numOfProj = 0;

public:
    TeacherAssistant(string name, int id, string perms[], int count, string email, string pass) : Student(name, id, perms, count, email, pass) {}

    void assignStudent(Student &s)
    {
        if (numOfStd < 10)
        {
            studentList[numOfStd++] = s;
        }
        else
        {
            cout << "TA already has 10 students.\n";
        }
    }

    void startProject(string projectName)
    {
        if (numOfProj < 2)
        {
            projects[numOfProj++] = projectName;
        }
        else
        {
            cout << "Max projects limit reached.\n";
        }
    }

    void viewProject()
    {
        cout << "TA Projects: ";
        for (int i = 0; i < numOfProj; i++)
        {
            cout << projects[i];
            if (i < numOfProj - 1)
                cout << ", ";
        }
        cout << endl;
    }

    void display() override
    {
        Student::display();
        cout << "Students Managed: " << numOfStd << endl;
        viewProject();
    }

    string getRole() override
    {
        return "TA";
    }
};

// ------------------- Professor Class -------------------
class Professor : public User
{
public:
    Professor(string name, int id, string perms[], int count, string email, string pass) : User(name, id, perms, count, email, pass) {}

    void collaborateWithTA(TeacherAssistant &ta, string project)
    {
        ta.startProject(project);
    }

    void display() override
    {
        User::display();
        cout << "Role: Professor (Full Lab Access)\n";
    }

    string getRole() override
    {
        return "Professor";
    }
};

// ------------------- Global Function -------------------
void authenticateAndPerformAction(User *user, string action)
{
    cout << "\nChecking permission for action: " << action << endl;
    user->acssesLab(action);
}

// ------------------- MAIN -------------------
int main()
{
    string studentPerms[] = {"submit assignment"};
    string taPerms[] = {"submit assignment", "view projects", "manage_students"};
    string profPerms[] = {"assign projects", "full_lab_access"};

    Student s1("Ali", 101, studentPerms, 1, "ali@nu.edu.pk", "pass123");
    TeacherAssistant ta1("Sara", 202, taPerms, 3, "sara@nu.edu.pk", "ta456");
    Professor p1("Dr. Khan", 303, profPerms, 2, "khan@nu.edu.pk", "prof789");

    // Simulate actions
    s1.giveAssignment();
    s1.submitAssignment(0);

    ta1.assignStudent(s1);
    ta1.startProject("ML Research");

    p1.collaborateWithTA(ta1, "AI Supervision");

    // Display info
    s1.display();
    ta1.display();
    p1.display();

    // Permission checks
    authenticateAndPerformAction(&s1, "submit assignment");
    authenticateAndPerformAction(&ta1, "manage_students");
    authenticateAndPerformAction(&p1, "full_lab_access");

    return 0;
}
