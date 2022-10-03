#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>


#include <ctime>
#include <cstdlib>
#include <map>
#include <cstring>
#include <iostream>
#include <set>
#include "sprint.h"
using namespace std;

class Project
{

private:
    string title;
    Date createddate;
    ProjectOwner* owner;
    vector<User*> users;
    IssueList todo;
    vector<Sprint*> inprogress;
    IssueList done;
    int issueId;
    User* loggeduser;

    // returns a set of int from a string input 0,1,2,3...
    static set<int> splitLine(string input)
    {

        istringstream ss(input);
        string token;
        int temp;
        set<int> tempvect;

        while (getline(ss, token, ' '))
        {
          //  cout << token << endl;
            try
            {
                temp = stoi(token);
                tempvect.insert(temp);
            }

            catch (invalid_argument)
            {
                continue;
            };
        }
      //  cout << tempvect.size() << endl;
        return tempvect;
    }

public:
    Project(string title, Date createddate, ProjectOwner* owner)
    {
        this->title = title;
        this->createddate = createddate;
        this->owner = owner;
        this->issueId = 0;
       // this->loggeduser = owner;
    }

    /*   Project()
       {
       }*/

    ~Project()
    {
        for (auto p : inprogress)
        {
            delete p;
        }
    }

    IssueList getTodo()
    {
        return this->todo;
    }

    void setTodo(IssueList val)
    {
        this->todo = val;
    }

    string getTitle()
    {
        return this->title;
    }

    IssueList getDone()
    {
        return this->done;
    }

    void setDone(IssueList val)
    {
        this->done = val;
    }

    string getLoggedIn()
    {
        return loggeduser->getName();
    }

    vector<Sprint*> getInprogress()
    {
        return this->inprogress;
    }

    void setInprogress(vector<Sprint*> val)
    {
        this->inprogress = val;
    }
    // gets the owner of this project
    ProjectOwner* getOwner() {
        return this->owner;
    }
    // gets the vector of users
    vector<User*> getVecUser() {
        return this->users;
    }
    //gets the date
    Date getDate() {
        return this->createddate;
    }


    void addToDo(Date date)
    {

        issuetype typetemp = readIssueType();
        issuepriority priotemp = readIssuePriority();
        string titletemp;
        Date datetemp = Date::createDate();

        string desc;
        string comm;

        cin.ignore(1000, '\n');
        cout << "Enter a description for the project" << endl;
        getline(cin, desc);
        cout << "Enter any comments" << endl;
        getline(cin, comm);
        cout << "Enter issue title" << endl;
        getline(cin, titletemp);
        cout << "Enter the assignee for this issue" << endl;
        User* assigneetemp;
        assigneetemp = this->searchForUser();
        cout << "Enter the reporter for this issue" << endl;
        User* reporttemp;
        reporttemp = this->searchForUser();

        Issue* issue = new Issue(titletemp, this->title, reporttemp, assigneetemp, this->issueId, typetemp, issuestatus::OPEN, createddate, datetemp, priotemp, desc, comm);

        todo.add(issue);

        issueId += 1;
    }

    void addUser(User* u)
    {
        users.push_back(u);
    }

    string asString()
    {
        stringstream ss;
        ss << "Project title:  " << this->title << ", with owner " << this->owner->getName() << endl;
        return ss.str();
    }

    User* searchForUser()
    {
        User* usertemp = new Developer();
        cout << "Existing users:" << endl;
        for (int i = 0; i < users.size(); i++)
        {
            cout << users[i]->get_title() << ", ";
        }
        cout << owner->getName() << endl;
        cout << "Enter user:" << endl;
        string name;
        bool found = false;

        while (true)
        {
            getline(cin, name);
            for (int i = 0; i < users.size(); i++)
            {
                if (name == users[i]->getName())
                {
                    usertemp = users[i];
                    found = true;
                    break;
                }
            }
            if (name == owner->getName())
            {
                found = true;
                usertemp = owner;
            }
            if (found == false)
            {
                cout << "Name not found, enter a new name" << endl;
            }
            else
            {
                break;
            }
        }
        return usertemp;
      
    }

    void logIn() //logs in a user for a project
    {
        loggeduser = searchForUser();
    }

   

    void createSprint() // creates a sprint
    {

     /*   if (!loggeduser->hasLeadAccess())
        {
            cout << "You don't have authority to create sprints" << endl;
            return;
        }*/
        int temp;
        cout << "Enter timeframe for sprint in weeks" << endl;

        while (true)
        {
            cin >> temp;
            if (temp >= 3)
            {
                cout << "Sprint can be 1-2 weeks long" << endl;
            }
            else
            {
                break;
            }
        }
        cout << "Existing backlog issues:" << endl;
        cout << todo.asString() << endl;
        cout << "Enter issue IDs that you want to add, separated by a space" << endl;

        cin.ignore(1000, '\n');
        string stringtemp;
        getline(cin, stringtemp);

        set<int> settemp;
        settemp = splitLine(stringtemp);

        IssueList issuevect;
        issuevect = todo.transferIssueId(settemp);

        if (issuevect.size() == 0)
        {
            cout << "Cant add issues, no valid IDs entered, canceling sprint" << endl;
            return;
        }

        Sprint* newsprint = new Sprint(issuevect, temp);
        inprogress.push_back(newsprint);
        cout << "Created sprint with a timeframe of " << temp << " weeks and " << issuevect.size() << " issues" << endl;
        cout << newsprint->printSprint();
    }

    

    void readIssues()
    {
        cout << "Please enter the IDs of the issues you'd like to transfer separated by spaces" << endl;
        string temp;
        getline(cin, temp);
    }


    void changeSprintStatus(Sprint* sprint) {
        cout << "Available issues in sprint" << endl;
        cout << sprint->printSprint() << endl;
        cout << "Please enter issue id that you'd like to change the working status of" << endl;

        int temp;
        cin >> temp;

        if (!(sprint->issueExist(temp))) {
            cout << "Enter a valid id number" << endl;
            return;
        }

        int temp2;

        cout << "You may mark an issue as completed or continue working." << endl;
        cout << "1 - Mark as complete" << endl;
        cout << "2 - Continue working" << endl;
        cin >> temp2;


        if (temp2 == 1) {
            Issue* issuetemp;
            issuetemp = sprint->returnIssue(temp);
            done.add(issuetemp);
            sprint->deleteIssue(temp);

            cout << "Marked issue # " << temp << " as done" << endl;
        }

        else {
            return;
        }


    }
};

Project* createProject(Date createddate) // creates a project
{
    string titletemp;
    cin.ignore(1000, '\n');
    cout << "Enter project title" << endl;
    getline(cin, titletemp);
    cout << "Enter the name of the owner" << endl;
    string ownername;
    getline(cin, ownername);

    

    ProjectOwner* owner = new ProjectOwner(ownername, titletemp);
    Project* projecttemp = new Project(titletemp, createddate, owner);
    cout << "Created " << projecttemp->asString() << endl;

    return projecttemp;
}
