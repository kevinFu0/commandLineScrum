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
#include "issue.h"
using namespace std;

class IssueList {
private:
    vector<Issue*> issues;

public:
    IssueList(vector<Issue*> issues) {
        this->issues = issues;
    }

    IssueList() {

    }

    vector<Issue*> getIssues() {
        return issues;
    }


    void add(Issue* issue) {
        issues.push_back(issue);
    }

    string asString() {
        stringstream ss;
        for (auto i : issues) {
            //ss << "ID:" << item->getId() << "- " << item->getProjectName() << " " << item->getTitle() << " assignee:" << item->getAssignee()->getName() << "\n";
                //"reporter " << item->getReporter()->getName() << "\n";
            //ss << i->getTitle() << ", " << i->getProjectName() << ", " << i->getReporter()->getName() << ", " + i->getAssignee()->getName() << "ID: "  << to_string(i->getId()) << ", " << streamIssueType(i->getType()) << ", " << streamIssueStatus(i->getStatus()) << ", " << i->getCreatedDate().asString() << ", " << i->getDueDate().asString() << ", " << streamIssuePriority(i->getPriority()) << ", " << i->getDescription() << ", " << i->getComments() << "\n";
            ss << i->asString();
        }
        return ss.str();
    }

    bool hasIssue(int id) {

        for (auto item : issues) {
            if (id == item->getId()) {
                return true;
            }
        }
        return false;
    }

    /*Issue* getIssue(int id) {

        for (auto item : issues) {
            if (id == item->getId()) {
                return item;
            }
        }
    }*/

    size_t size() {
        return issues.size();
    }

    IssueList transferIssueId(set<int> idset) {

        IssueList vecttemp;
        for (auto id : idset) {
            for (int i = 0; i < issues.size(); i++) {
                if (id == issues[i]->getId()) {
                    vecttemp.add(issues[i]);
                    issues.erase(issues.begin() + i);
                    break;
                }
            }
        }
        return vecttemp;
    }


    void deleteIssue(int id) {

        for (int i = 0; i < issues.size(); i++) {
            if (id == issues[i]->getId()) {
                issues.erase(issues.begin() + i);
                break;
            }
        }
    }

    Issue* returnIssue(int id) {
        Issue* emptyTemp = new Issue();
        for (int i = 0; i < issues.size(); i++) {
            if (id == issues[i]->getId()) {
                return issues[i];

            }
        }
        return emptyTemp;

    }
};
