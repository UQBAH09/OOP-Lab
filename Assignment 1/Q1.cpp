#include <iostream>
#include <string>
using namespace std;

class Skill
{
private:
    int skillID;
    string skillName;
    string description;

public:
    Skill(int ID = 0, const string &name = "", const string &des = "") : skillID(ID), skillName(name), description(des) {}
    Skill(const Skill &s) : skillID(s.skillID), skillName(s.skillName), description(s.description) {}

    void updateSkillDescription(const string &newDescription)
    {
        description = newDescription;
        cout << "Skill updated successfully." << endl;
    }

    string getSkillName() const
    {
        return skillName;
    }

    void setSkillName(const string &n)
    {
        skillName = n;
    }

    void showSkillDetails() const
    {
        cout << "Skill ID: " << skillID << ", Name: " << skillName << ", Description: " << description << endl;
    }
};

class Sport
{
private:
    int sportID;
    string name;
    string description;
    Skill *requiredSkills;
    int numOfSkills;

public:
    Sport(int ID = 0, const string &n = "", const string &des = "") : sportID(ID), name(n), description(des), requiredSkills(nullptr), numOfSkills(0) {}
    Sport(const Sport &s) : sportID(s.sportID), name(s.name), description(s.description), numOfSkills(s.numOfSkills)
    {
        if (numOfSkills > 0)
        {
            requiredSkills = new Skill[numOfSkills];
            for (int i = 0; i < numOfSkills; i++)
                requiredSkills[i] = s.requiredSkills[i];
        }
        else
        {
            requiredSkills = nullptr;
        }
    }
    ~Sport()
    {
        delete[] requiredSkills;
    }

    void addSkill(const Skill &s)
    {
        Skill *newArray = new Skill[numOfSkills + 1];
        for (int i = 0; i < numOfSkills; i++)
            newArray[i] = requiredSkills[i];
        newArray[numOfSkills] = s;
        delete[] requiredSkills;
        requiredSkills = newArray;
        numOfSkills++;
        cout << "Skill added successfully." << endl;
    }

    void removeSkill(const Skill &s)
    {
        int index = -1;
        for (int i = 0; i < numOfSkills; i++)
        {
            if (requiredSkills[i].getSkillName() == s.getSkillName())
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            cout << "No skill found." << endl;
            return;
        }
        Skill *newArray = (numOfSkills - 1 > 0) ? new Skill[numOfSkills - 1] : nullptr;
        for (int i = 0; i < index; i++)
            newArray[i] = requiredSkills[i];
        for (int i = index + 1; i < numOfSkills; i++)
            newArray[i - 1] = requiredSkills[i];
        delete[] requiredSkills;
        requiredSkills = newArray;
        numOfSkills--;
        cout << "Skill removed successfully." << endl;
    }

    void viewDetails() const
    {
        cout << "Sport ID: " << sportID << ", Name: " << name << ", Description: " << description << endl;
        cout << "Required Skills:" << endl;
        for (int i = 0; i < numOfSkills; i++)
            requiredSkills[i].showSkillDetails();
    }
};

class Mentor;

class Student
{
private:
    int studentID;
    string name;
    int age;
    Sport *sportsInterests;
    int numOfSportInterests;
    Mentor *mentorAssigned;

public:
    Student(int ID = 0, const string &n = "", int a = 0, int num = 0, Sport *SI = nullptr) : studentID(ID), name(n), age(a), numOfSportInterests(num), mentorAssigned(nullptr)
    {
        if (numOfSportInterests > 0 && SI != nullptr)
        {
            sportsInterests = new Sport[numOfSportInterests];
            for (int i = 0; i < numOfSportInterests; i++)
                sportsInterests[i] = SI[i];
        }
        else
        {
            sportsInterests = nullptr;
        }
    }

    Student(const Student &s) : studentID(s.studentID), name(s.name), age(s.age), numOfSportInterests(s.numOfSportInterests), mentorAssigned(s.mentorAssigned)
    {
        if (numOfSportInterests > 0 && s.sportsInterests != nullptr)
        {
            sportsInterests = new Sport[numOfSportInterests];
            for (int i = 0; i < numOfSportInterests; i++)
                sportsInterests[i] = s.sportsInterests[i];
        }
        else
        {
            sportsInterests = nullptr;
        }
    }

    ~Student()
    {
        delete[] sportsInterests;
    }

    void registerForMentorship(Mentor &m);
    void viewMentorDetails();

    void updateSportsInterest(const Sport &s)
    {
        Sport *newArray = new Sport[numOfSportInterests + 1];
        for (int i = 0; i < numOfSportInterests; i++)
            newArray[i] = sportsInterests[i];
        newArray[numOfSportInterests] = s;
        delete[] sportsInterests;
        sportsInterests = newArray;
        numOfSportInterests++;
        cout << "Sports interest updated successfully." << endl;
    }

    void viewDetail() const
    {
        cout << "Student ID: " << studentID << ", Name: " << name << ", Age: " << age << endl;
        cout << "Sports Interests:" << endl;
        for (int i = 0; i < numOfSportInterests; i++)
            sportsInterests[i].viewDetails();
        if (mentorAssigned)
            cout << "Mentor assigned. Use viewMentorDetails() for details." << endl;
        else
            cout << "No mentor assigned." << endl;
    }

    int getID() const
    {
        return studentID;
    }

    void setMentor(Mentor *m)
    {
        mentorAssigned = m;
    }
};

class Mentor
{
private:
    int mentorID;
    string name;
    Sport *sportsExpertise;
    int numOfSportsExpertise;
    int maxLearners;
    int curLearners;
    Student *assignedLearners;

public:
    Mentor(int ID = 0, const string &n = "", int maxL = 0, Sport *expertise = nullptr, int numExpertise = 0) : mentorID(ID), name(n), maxLearners(maxL), curLearners(0), numOfSportsExpertise(numExpertise)
    {
        if (numOfSportsExpertise > 0 && expertise != nullptr)
        {
            sportsExpertise = new Sport[numOfSportsExpertise];
            for (int i = 0; i < numOfSportsExpertise; i++)
                sportsExpertise[i] = expertise[i];
        }
        else
        {
            sportsExpertise = nullptr;
        }
        assignedLearners = (maxLearners > 0) ? new Student[maxLearners] : nullptr;
    }

    Mentor(const Mentor &m) : mentorID(m.mentorID), name(m.name), maxLearners(m.maxLearners), curLearners(m.curLearners), numOfSportsExpertise(m.numOfSportsExpertise)
    {
        if (numOfSportsExpertise > 0 && m.sportsExpertise != nullptr)
        {
            sportsExpertise = new Sport[numOfSportsExpertise];
            for (int i = 0; i < numOfSportsExpertise; i++)
                sportsExpertise[i] = m.sportsExpertise[i];
        }
        else
        {
            sportsExpertise = nullptr;
        }
        if (maxLearners > 0 && m.assignedLearners != nullptr)
        {
            assignedLearners = new Student[maxLearners];
            for (int i = 0; i < curLearners; i++)
                assignedLearners[i] = m.assignedLearners[i];
        }
        else
        {
            assignedLearners = nullptr;
        }
    }

    ~Mentor()
    {
        delete[] sportsExpertise;
        delete[] assignedLearners;
    }

    void assignLearner(const Student &s)
    {
        if (curLearners < maxLearners)
        {
            assignedLearners[curLearners] = s;
            curLearners++;
            cout << "Student assigned successfully." << endl;
        }
        else
        {
            cout << "Max student limit reached." << endl;
        }
    }

    void removeLearner(const Student &s)
    {
        int index = -1;
        for (int i = 0; i < curLearners; i++)
        {
            if (assignedLearners[i].getID() == s.getID())
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            cout << "Student not found." << endl;
            return;
        }
        for (int i = index; i < curLearners - 1; i++)
            assignedLearners[i] = assignedLearners[i + 1];
        curLearners--;
        cout << "Student removed successfully." << endl;
    }

    void viewLearners() const
    {
        cout << "Mentor " << name << " has the following learners:" << endl;
        for (int i = 0; i < curLearners; i++)
            assignedLearners[i].viewDetail();
    }

    void provideGuidance() const
    {
        cout << "Providing guidance..." << endl;
    }

    bool available() const
    {
        return curLearners < maxLearners;
    }

    void viewDetails() const
    {
        cout << "Mentor ID: " << mentorID << ", Name: " << name << endl;
        cout << "Sports Expertise:" << endl;
        for (int i = 0; i < numOfSportsExpertise; i++)
            sportsExpertise[i].viewDetails();
    }
};

void Student::registerForMentorship(Mentor &m)
{
    if (m.available())
    {
        mentorAssigned = &m;
        cout << "Mentor assigned successfully." << endl;
        m.assignLearner(*this);
    }
    else
    {
        cout << "Mentor is full." << endl;
    }
}

void Student::viewMentorDetails()
{
    if (mentorAssigned)
        mentorAssigned->viewDetails();
    else
        cout << "No mentor assigned." << endl;
}

int main()
{
    // Create some skills
    Skill s1(1, "Dribbling", "Ability to control the ball");
    Skill s2(2, "Shooting", "Ability to shoot accurately");

    // Create a sport (e.g., Tennis) and add skills
    Sport tennis(101, "Tennis", "A racket sport");
    tennis.addSkill(s1);
    tennis.addSkill(s2);

    // Create a student with Tennis as an interest
    Sport interests[1] = {tennis};
    Student student1(1001, "Saad", 20, 1, interests);

    // Create a mentor with capacity 3 and Tennis expertise
    Sport expertise[1] = {tennis};
    Mentor mentor1(501, "Ali", 3, expertise, 1);

    // Register the student for mentorship
    student1.registerForMentorship(mentor1);

    // View mentor details from the student’s perspective
    student1.viewMentorDetails();

    // View the mentor’s learners
    mentor1.viewLearners();

    return 0;
}
