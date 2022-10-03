#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <map>
#include <cstring>
#include <iostream>
#include "project.h"


using namespace std;

// returns a set of int from a string input 0 1 2 3 
set<int> splitLine(string input)
{
    istringstream ss(input);
    string token;
    int temp;
    set<int> tempvect;

    while (getline(ss, token, ' '))
    {
        //cout << token << endl;
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
    //cout << tempvect.size() << endl;
    return tempvect;
}


// work on sprint
void workOnSprint(Project* proj) {

    int temp;
    cout << "You are working on project " << proj->getTitle() << ", logged in as " << proj->getLoggedIn() << endl;
    cout << "1 - Change sprint status" << endl;
    cout << "2 - Transfer an issue from one sprint to another (Only for project leads +)" << endl;
    cout << "3 - Edit the timeframe of a project (only for project leads +)" << endl;

    cin >> temp;
    switch (temp) {
    case 1:
        proj->changeSprintStatus(proj->getInprogress()[0]);
    }

}
void workOnProject(Project* proj, Date date)
{ // everything that has to do with issues

    while (true)
    {
        int temp;
        cout << "Working on project: " << proj->getTitle() << ", logged in as " << proj->getLoggedIn() << endl;
        cout << "Date: " << date.asString() << endl;
        cout << "1 - Create an issue" << endl;
        cout << "2 - Create a sprint" << endl;
        cout << "3 - Work on a sprint" << endl;
        // option 3 work on sprint, loops thru active sprints and let user choose sprint to work on, opens a sub fucntion to work on sprint
        // in sub function, work on sprint (enter issue number) working is just changing status (open = in progress) only option is working on done
        // project lead + option - transfer issue in between sprints
        // another option is edit the timeframe of a current sprint for projects lead only 
        // option 4 is delete project owner only
        // option 5 edit issue (enter issue id and you are able to edit issue fields) project lead only
        // option 6 is create a user
        // option7 is edit user to change their role (delete old user make new) (before making loop to make sure user doesnt exist) project lead+
        cin >> temp;
        switch (temp)
        {
        case 1:
            proj->addToDo(date);
            break;
        case 2:
            proj->createSprint();
            break;
        case 3:
            workOnSprint(proj);
            break;
        }
    }
}

int selectProject(size_t size)
{
    cout << "Enter project number" << endl;
    int num;
    while (true)
    {
        cin >> num;

        if (num >= 0 && num < size)
        {
            return num;
        }
        else
        {
            cout << "See list to get a valid project number" << endl;
        }
    }
}


//checks if a user is in the list of users, returns user*
User* checkValidUser(const vector<User*>& ul) {
    User* usertemp = new Developer();
    string name;
    bool found = false;
    cout << "Enter username: ";
    //flushing buffer
    cin.ignore();
    while (true) {
        getline(cin, name);
        for (int i = 0; i < ul.size(); i++) {
            if (name == ul[i]->getName()) {
                usertemp = ul[i];
                found = true;
                break;
            }
        }
        if (found == false) {
            cout << "Invalid name: Try Again: ";
        }
        else {
            break;
        }
    }
    return usertemp;
}

bool checkUserinVec(User* temp, vector<User*> vec) {
    for (auto ptr : vec) {
        if (ptr->getName() == temp->getName()) {
            return true;
        }
    }
    return false;
}


//checks to make sure users are unique
bool checkUnique(vector<User*>& allUsers, User* temp) {
    for (auto up : allUsers) {
        if (up->getName() == temp->getName()) {
            cout << "Usernames must be unique\n";
            return false;
        }
    }
    return true;
}



// option to create initial project
void initProject(vector<Project*>& allprojects, vector<User*>& allUsers)
{ // to do with projects and sprints
    Date currentdate = Date(20, 02, 2001);
    int temp  = 0;
    int temp2 = 0;
    // loops until there is at least 1 project
    while (temp != 5)
    {
        
        cout << "Welcome project owner" << endl;
        cout << "Date: " << currentdate.asString() << endl;
        cout << "1 - Create a project" << endl;
        cout << "2 - List all the projects" << endl;
        cout << "3 - Select a project to work on" << endl;
        cout << "5 - quit" << endl;
        // option 4 move time forward
        cin >> temp;
        switch (temp)
        {
        case 1:
        {
            Project* projecttemp = createProject(currentdate);
            allprojects.push_back(projecttemp);
            //adds project owner to userList
            allUsers.push_back(projecttemp->getOwner());   
            //adding project name to the user project_name memeber
            //projecttemp->getOwner()->addString(projecttemp->getTitle());

            break;
        }
        case 2:
        {
            for (int i = 0; i < allprojects.size(); i++)
            {
                cout << i << " " << allprojects[i]->asString() << endl;
            }
            break;
        }
        case 3:
        {
            temp2 = selectProject(allprojects.size());
            cin.ignore(1000, '\n');
            allprojects[temp2]->logIn(); // logs in the user
            workOnProject(allprojects[temp2], currentdate);
            break;
        }
        }
    }
}

// creates users
void createUsers(vector<User*>& allUsers) {
    int temp = 0;
    while (temp != 3) {
        cout << "1 - create a new user" << endl;
        cout << "2 - view all users" << endl;
        cout << "3 - quit" << endl;
        cin >> temp;
        if (temp == 1) {
            User* usertemp = createUser();
            if (checkUnique(allUsers, usertemp)) {
                allUsers.push_back(usertemp);
            }
          
        }
        if (temp == 2) {
            cout << "List of Users:\n";
            for (auto u : allUsers) {
                cout << u->get_title() << endl;
            }

        }
    }
};

//modifying issuse properties
void modifyProperty(Project* pPtr, Issue* iPtr, int num, string type) {
    string input;
    int inputI;
    int month, day, year;
    User* tempu;
    Date tempd;
    switch (num) {
    case 0:
        cout << "Enter new issue title:";
        cin.ignore();
        getline(cin, input);
        iPtr->setTitle(input);
        break;
    case 1:
        if (type == "owner") {
            cout << "Enter new project name:";
            cin.ignore();
            getline(cin, input);
            iPtr->setProjectName(input);
        }
        else {
            cout << "Must be owner\n";
        }
        break;
    case 2:
        if (type != "developer") {
            cout << "List of users in this project, Enter username to reassign\n";

            for (auto up : pPtr->getVecUser()) {
                cout << up->getName() << endl;
            }
            tempu = checkValidUser(pPtr->getVecUser());
            iPtr->setReporter(tempu);
        }
        else {
            cout << "Must be owner or leader\n";
        }
        break;
    case 3:
        if (type != "developer") {
            cout << "List of users in this project, Enter username to reassign\n";
            for (auto up : pPtr->getVecUser()) {
                cout << up->getName() << endl;
            }
            tempu = checkValidUser(pPtr->getVecUser());
            iPtr->setAssignee(tempu);
        }
        else {
            cout << "Must be owner or leader\n";
        }
        break;
    case 4:
        if (type != "developer") {
            cout << "USERSTORY = 0, TASK = 1, BUILD = 2, TEST = 3, DEBUG = 4 , DOCUMENTATION = 5" << endl;
            cout << "Enter new type:";
            cin >> inputI;
            iPtr->setType(static_cast<issuetype>(inputI));
        }
        else {
            cout << "Must be owner or leader\n";
        }
        break;
    case 5:
        if (type != "developer") {
            cout << "OPEN = 0, INPROGRESS = 1 , DONE = 2, OVERDUE =3" << endl;
            cout << "Enter new type:";
            cin >> inputI;
            iPtr->setStatus(static_cast<issuestatus>(inputI));
        }
        else {
            cout << "Must be owner or leader\n";
        }
        break;
    case 6:
        if (type != "developer") {
            cout << "Change the due date\n";
            cout << "Enter your date in format: mm/dd/yyyy" << endl;
            scanf("%d/%d/%d", &month, &day, &year);
            tempd = Date(day, month, year);
            iPtr->setDueDate(tempd);
        }
        else {
            cout << "Must be owner or leader\n";
        }
        break;
    case 7:
        if (type != "developer") {
            cout << "HIGH=0, MEDIUM=1, LOW=2" << endl;
            cout << "Enter new priority:";
            cin >> inputI;
            iPtr->setPriority(static_cast<issuepriority>(inputI));
        }
        else {
            cout << "Must be owner or leader\n";
        }
        break;
    case 8:
        if (type != "developer") {
            cout << "Enter new issue description:";
            cin.ignore();
            getline(cin, input);
            iPtr->setDescription(input);
        }
        else {
            cout << "Must be owner or leader\n";
        }
        break;
    case 9:
        if (type != "developer") {
            cout << "Enter new issue comments:";
            cin.ignore();
            getline(cin, input);
            iPtr->setComments(input);
        }
        else {
            cout << "Must be owner or leader\n";
        }
        break;
    default:
        cout << "Invalid input\n";
        break;
    }
}



// starts working on projects
void startWorking(vector<Project*>& allprojects, vector<User*>& allUsers) {
    User* utemp = checkValidUser(allUsers);
    if (utemp->getType() == "owner") {
        cout << "Welcome project owner "<< endl;
        //select a project
        cout << "Select a project to work on\n";
        for (int i = 0; i < allprojects.size(); i++) {
            cout << i << "- " << allprojects[i]->getTitle() << endl;
        }
        int temp0;
        cin >> temp0;
        Project* tempPro;
        //checking valid boundry in allprojects vector
        if (temp0 <= allprojects.size() - 1) {
            tempPro = allprojects[temp0];
            cout << "Working on " << tempPro->getTitle() << "\n";
        }
        else {
            cout << "Invalid choice\n";
        }

        int temp = 0;
        while (temp != 5) {
            cout << "1- invite other users to project" << endl;
            cout << "2- create and modify issue properties" << endl;
            cout << "3- create and update sprints" << endl;
            cout << "4- delete project" << endl;
            cout << "5- quit" << endl;
            cin >> temp;
            switch (temp) {
            case 1:
            {
                string input;
                cout << "List of available users: \n";
                for (int i = 0; i < allUsers.size(); i++) {
                    if (allUsers[i]->getType() != "owner") {
                        cout << i << "- " << allUsers[i]->get_title() << endl;
                    }
                }
                cout << "Enter user IDs that you want to add, separated by a space" << endl;
                cin.ignore();
                getline(cin, input);
                set<int> s = splitLine(input);
                //adding the users to the project
                for (int i : s) {
                    allprojects[temp0]->addUser(allUsers[i]);
                }
                cout << "Project " << allprojects[temp0]->getTitle() << " now has users:\n";
                //printing users of the project
                for (auto up : allprojects[temp0]->getVecUser()) {
                    cout << up->get_title() << endl;
                }
                break;
            }
            case 2:
            {
                cout << "1- create an issue for " << allprojects[temp0]->getTitle() << "\n";
                cout << "2- modify an issue for " << allprojects[temp0]->getTitle() << "\n";
                int tempC2 = 0;
                cin >> tempC2;
                if (tempC2 == 1) {
                    //creates an issue
                    allprojects[temp0]->addToDo(allprojects[temp0]->getDate());
                    cout << "All issues for " << allprojects[temp0]->getTitle() << "\n";
                    cout << allprojects[temp0]->getTodo().asString();
                        
                }
                if (tempC2 == 2) {
                    cout << "Select an issue to modify\n";
                    // loops through all the projects in progress
                    for (int i = 0; i < allprojects[temp0]->getTodo().size(); i++) {
                        cout << i << "- " << allprojects[temp0]->getTodo().getIssues()[i]->getTitle() << endl;
                    }
                    int tempIS5;
                    cin >> tempIS5;
                    cout << "Select an issue property to modify:\n";
                    cout << "0- issuetitle\n";
                    cout << "1- projectname\n";
                    cout << "2- reporter\n";
                    cout << "3- assignee\n";
                    cout << "4- type\n";
                    cout << "5- status\n";
                    cout << "6- duedate\n";
                    cout << "7- priority\n";
                    cout << "8- description\n";
                    cout << "9- comments\n";
                    int numTemp0;
                    cin >> numTemp0;
                    modifyProperty(allprojects[temp0], allprojects[temp0]->getTodo().getIssues()[tempIS5], numTemp0, "owner");
                    cout << "Modified issue\n";
                    cout << allprojects[tempIS5]->getTodo().asString();
                }
                break;
            }
            case 3: 
            {
                int case3I;
                cout << "0- create a sprint\n";
                cout << "1- print all sprints\n";
                cout << "2- modify a sprint\n";
                cin >> case3I;
                
                if (case3I == 0) {
                    allprojects[temp0]->createSprint();
                }
                if (case3I == 1) {
                    for (auto ptr : allprojects[temp0]->getInprogress()) {
                        cout << ptr->printSprint() << endl;;
                    }
                }
                if (case3I == 2) {
                    int case333;
                    //print all sprints
                    for (int i = 0; i < allprojects[temp0]->getInprogress().size(); i++) {
                        cout << i << "- " << allprojects[temp0]->getInprogress()[i]->printSprint() << endl;
                    }
                    cout << "Enter sprint id you want to modify:";
                    cin >> case333;
                    allprojects[temp0]->changeSprintStatus(allprojects[temp0]->getInprogress()[case333]);
                }

               
                break;
            }
            case 4:
            {
                int i = 0;
                int case4i;
                cout << "Select a project to delete\n";
                for (i = 0; i < allprojects.size(); i++) {
                    cout << i << "- " << allprojects[i]->asString() << endl;
                }
                cin >> case4i;
                cout << "Deleted " << allprojects[case4i]->asString() << endl;
                allprojects.erase(allprojects.begin() + case4i);
                break;
            }
            case 5:
            {
                cout << "Logging out...\n";
            }
            }
        }
    }
    if (utemp->getType() == "leader") {
        cout << "Welcome project leader\n";
        cout << "Select a project to work on";
        int temp0;
        //prints all the projects that the leader is a part of 
        for (int i = 0; i < allprojects.size(); i++) {
            if (checkUserinVec(utemp, allprojects[i]->getVecUser())) {
                cout << i << "- " << allprojects[i]->asString() << endl;
            }
        }
        cin >> temp0;
    }
}

int main()
{
    // vector of projects
    vector<Project*> ProjectList;
    // vector of Users
    vector<User*> userList;
    
    initProject(ProjectList, userList);
    createUsers(userList);
    startWorking(ProjectList, userList);
    startWorking(ProjectList, userList);


}
