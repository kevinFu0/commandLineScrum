#include <algorithm> 
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <map>
#include <cstring>
#include <iostream>
#include "date.h"
#include "user.h"

using namespace std;

enum class issuetype {
    USERSTORY = 0,
    TASK = 1, BUILD = 2, TEST = 3, DEBUG = 4, DOCUMENTATION = 5
};

enum class issuestatus {
    OPEN = 0, INPROGRESS = 1, DONE = 2, OVERDUE = 3
};

enum class issuepriority {
    HIGH = 0, MEDIUM = 1, LOW = 2
};

string streamIssueType(issuetype type) {
    switch (static_cast<int>(type)) {
    case 0:
        return "USERSTORY";
    case 1:
        return "TASK";
    case 2:
        return "BUILD";
    case 3:
        return "TEST";
    case 4:
        return "DEBUG";
    case 5:
        return "DOCUMENTATION";
    }
    return "";
}
string streamIssueStatus(issuestatus type) {
    switch (static_cast<int>(type)) {
    case 0:
        return "OPEN";
    case 1:
        return "INPROGRESS";
    case 2:
        return "DONE";
    case 3:
        return "OVERDUE";
    }

    return "";
}
string streamIssuePriority(issuepriority type) {
    switch (static_cast<int>(type)) {
    case 0:
        return "HIGH";
    case 1:
        return "MEDIUM";
    case 2:
        return "LOW";
    }

    return "";
}


class Issue {
private:
    string issuetitle;
    string projectname;
    User* reporter;
    User* assignee;
    int id;
    issuetype type;
    issuestatus status;
    Date createddate;
    Date duedate;
    issuepriority priority;
    string description;
    string comments;


public:

    Issue(string issuetitle, string projectname, User* reporter, User* assignee, int id, issuetype type, issuestatus status, Date createddate, Date duedate, issuepriority priority, string description, string comments) {
        this->issuetitle = issuetitle;
        this->projectname = projectname;
        this->reporter = reporter;
        this->assignee = assignee;
        this->id = id;
        this->type = type;
        this->status = status;
        this->createddate = createddate;
        this->duedate = duedate;
        this->priority = priority;
        this->description = description;
        this->comments = comments;
    }

    Issue() {
        User* empty = new Developer();
        Date emptyd = Date();
        this->issuetitle = "N/A";
        this->projectname = "N/A";
        this->reporter = empty;
        this->assignee = empty;
        this->id = 0;
        this->type = issuetype::BUILD;
        this->status = issuestatus::DONE;
        this->createddate = emptyd;
        this->duedate = emptyd;
        this->priority = issuepriority::HIGH;
        this->description = "";
        this->comments = "";
    }

    string getProjectName() {
        return this->projectname;
    }

    void setProjectName(string val) {
        this->projectname = val;
    }

    User* getReporter() {
        return this->reporter;
    }

    void setReporter(User* val) {
        this->reporter = val;
    }

    User* getAssignee() {
        return this->assignee;
    }

    void setAssignee(User* val) {
        this->assignee = val;
    }

    int getId() {
        return this->id;
    }

    void setId(int val) {
        this->id = val;
    }

    issuetype getType() {
        return this->type;
    }

    void setType(issuetype val) {
        this->type = val;
    }

    issuestatus getStatus() {
        return this->status;
    }

    void setStatus(issuestatus val) {
        this->status = val;
    }

    Date getCreatedDate() {
        return this->createddate;
    }

    void setCreatedDate(Date val) {
        this->createddate = val;
    }

    Date getDueDate() {
        return this->duedate;
    }

    void setDueDate(Date val) {
        this->duedate = val;
    }

    issuepriority getPriority() {
        return this->priority;
    }

    void setPriority(issuepriority val) {
        this->priority = val;
    }

    string getDescription() {
        return this->description;
    }

    void setDescription(string val) {
        this->description = val;
    }

    string getComments() {
        return this->comments;
    }

    void setComments(string val) {
        this->comments = val;
    }

    string getTitle() {
        return this->issuetitle;
    }

    void setTitle(string val) {
        this->issuetitle = val;
    }


    string asString() {
       
        return "ID:" + to_string(id) + "- " + projectname + " " + issuetitle + ",Reporter: " + reporter->getName() + ",Assignee:" + assignee->getName() + ", " + description + ", " + comments + +", " + streamIssueType(type) + ", " + streamIssuePriority(priority) + ", " + streamIssueStatus(status) + ", Created: " + createddate.asString() + ", Due: " + duedate.asString() + "\n";
    }




};


issuetype readIssueType() {
    cout << "Select issue type:" << endl;
    cout << "USERSTORY = 0, TASK = 1, BUILD = 2, TEST = 3, DEBUG = 4 , DOCUMENTATION = 5" << endl;

    int val;
    cin >> val;

    issuetype temp = static_cast<issuetype>(val);
    return temp;
}

issuestatus readIssueStatus() {
    cout << "Select issue status:" << endl;
    cout << "OPEN = 0, INPROGRESS = 1 , DONE = 2, OVERDUE =3" << endl;

    int val;
    cin >> val;

    issuestatus temp = static_cast<issuestatus>(val);
    return temp;
}


issuepriority readIssuePriority() {
    cout << "Select issue priority:" << endl;
    cout << "HIGH=0, MEDIUM=1, LOW=2" << endl;

    int val;
    cin >> val;

    issuepriority temp = static_cast<issuepriority>(val);
    return temp;
}

