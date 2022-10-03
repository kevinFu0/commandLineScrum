#include <algorithm> 
#include <iomanip>
#include <string>
#include <vector>


#include <ctime>
#include <cstdlib>
#include <map>
#include <cstring>
#include <iostream>
#include "issuelist.h"
using namespace std;

class Sprint {

private:
    IssueList issues;
    int timeframe;


public:

    Sprint(IssueList issues, int timeframe) {
        this->issues = issues;
        this->timeframe = timeframe;
    }

    /*Sprint() {
    }*/




    IssueList getIssues() {
        return this->issues;
    }

    void setIssues(IssueList val) {
        this->issues = val;
    }

    int getTimeframe() {
        return this->timeframe;
    }

    void setTimeframe(int val) {
        this->timeframe = val;
    }


    bool issueExist(int id) { // returns if an issue exists in this sprint
        return issues.hasIssue(id);
    }

    string printSprint() {
        return issues.asString();
    }

    Issue* returnIssue(int id) {
        return issues.returnIssue(id);
    }

    void deleteIssue(int id) {
        issues.deleteIssue(id);
    }

};
