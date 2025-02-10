#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Mentor class defined before Student to avoid forward declaration issues
class Student; // Forward declaration since Mentor references Student

class Mentor
{
private:
    int mentorID;
    string name;
    vector<string> sportsExpertise;
    int maxLearners;
    vector<Student *> assignedLearners;

public:
    Mentor(int mentorID, string name, vector<string> sportsExpertise, int maxLearners)
    {
        this->mentorID = mentorID;
        this->name = name;
        this->sportsExpertise = sportsExpertise;
        this->maxLearners = maxLearners;
    }

    void viewMentor()
    {
        cout << "Mentor name: " << name << endl;
        cout << "Expertise: ";
        for (const string &experty : sportsExpertise)
        {
            cout << experty << ", ";
        }
        cout << endl;
    }

    bool hasSpace()
    {
        return assignedLearners.size() < maxLearners;
    }

    void assignLearner(Student &s);
    void removeLearner(int studentId);
    void viewLearners();
    void provideGuidance()
    {
        cout << "Providing guidance to assigned learners...\n";
    }
};

class Skill
{
private:
    int skillID;
    string skillName;
    string description;

public:
    Skill(int skillID, string skillName, string description)
    {
        this->skillID = skillID;
        this->skillName = skillName;
        this->description = description;
    }

    void showSkillDetails()
    {
        cout << "Skill ID: " << skillID << ", Name: " << skillName << ", Description: " << description << endl;
    }

    int getSkillID()
    {
        return skillID;
    }
};

class Sport
{
private:
    int sportID;
    string name;
    string description;
    vector<Skill> requiredSkills;

public:
    Sport(int sportID, string name, string description)
    {
        this->sportID = sportID;
        this->name = name;
        this->description = description;
    }

    void addSkill(Skill s)
    {
        requiredSkills.push_back(s);
    }

    string getSportname()
    {
        return name;
    }
};

class Student
{
private:
    int studentId;
    string name;
    int age;
    vector<Sport> sportsInterests;
    Mentor *mentorAssigned;

public:
    Student(int studentID, string name, int age)
    {
        this->studentId = studentID;
        this->name = name;
        this->age = age;
        mentorAssigned = nullptr;
    }

    void registerForMentorship(Mentor &m)
    {
        if (m.hasSpace())
        {
            m.assignLearner(*this);
            return;
        }
        cout << "Mentor not available." << endl;
    }

    void viewMentorDetails()
    {
        if (mentorAssigned)
        {
            mentorAssigned->viewMentor();
            return;
        }
        cout << "No mentor assigned yet." << endl;
    }

    void updateSportsInterest(Sport s)
    {
        for (Sport &sport : sportsInterests)
        {
            if (sport.getSportname() == s.getSportname())
            {
                cout << "This sport is already included." << endl;
                return;
            }
        }
        sportsInterests.push_back(s);
        cout << "Sport added successfully." << endl;
    }

    int getStudentId()
    {
        return studentId;
    }

    void viewStudent()
    {
        cout << "Student name: " << name << endl;
        cout << "Student Age: " << age << endl;
        cout << "Sport Interests: ";
        for (size_t i = 0; i < sportsInterests.size(); i++)
        {
            cout << sportsInterests[i].getSportname();
            if (i < sportsInterests.size() - 1)
                cout << ", ";
        }
        cout << endl;
    }

    void removeMentor()
    {
        mentorAssigned = nullptr;
    }
};

void Mentor::assignLearner(Student &s)
{
    if (assignedLearners.size() < maxLearners)
    {
        assignedLearners.push_back(&s);
        return;
    }
    cout << "Space not available." << endl;
}

void Mentor::removeLearner(int studentId)
{
    for (auto it = assignedLearners.begin(); it != assignedLearners.end(); ++it)
    {
        if ((*it)->getStudentId() == studentId)
        {
            (*it)->removeMentor();
            assignedLearners.erase(it);
            cout << "Mentor removed." << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
}

void Mentor::viewLearners()
{
    for (Student *student : assignedLearners)
    {
        student->viewStudent();
    }
}

int main()
{
    Skill skill1(1, "Serving", "Master the art of serving in tennis.");
    Skill skill2(2, "Volley", "Learn how to volley effectively.");

    Sport tennis(1, "Tennis", "A racket sport that can be played individually or in pairs.");
    tennis.addSkill(skill1);
    tennis.addSkill(skill2);

    vector<string> expertise = {"Tennis", "Badminton"};
    Mentor mentor1(1, "Ali", expertise, 3);

    Student student1(1, "Saad", 20);
    student1.updateSportsInterest(tennis);
    student1.registerForMentorship(mentor1);

    mentor1.viewLearners();
    mentor1.provideGuidance();
    mentor1.removeLearner(student1.getStudentId());

    return 0;
}
