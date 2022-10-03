#include <algorithm> 
#include <iomanip>
#include <string>
#include <vector>

#include <ctime>
#include <cstdlib>
#include <map>
#include <cstring>
#include <iostream>
using namespace std;

class User {

protected:
    string name;
    // keeps track of which project a user is assigned to
    string project;

public:

    User(string name) {
        this->name = name;
    }

    User()
    {
        this->name = "";
    }

   
    void setName(string val) {
        this->name = val;
    }


    virtual bool hasOwnerAccess() {
        return false;
    }

    virtual bool hasLeadAccess() {
        return false;
    }
    //virtual function
    virtual string get_title() const = 0;
    virtual string getName() const = 0;
    //type checker
    virtual string getType() const = 0;


    


};

class ProjectOwner : public User {

private:
    string projectName;


public:

    ProjectOwner(string name, string pn) : User(name) {
        projectName = pn;
    }

    void addString(string pn) {
        projectName = projectName + "," + pn;
    }

    bool hasOwnerAccess() {
        return true;
    }

    bool hasLeadAccess() {
        return true;
    }

    string get_ProjectName() {
        return projectName;
    }

  

    //overriding virutal function get_name()
    string get_title() const override {
        return name + ": Project Owner " + projectName;
    }

    string getName() const override {
        return name;
    }

    string getType() const override {
        return "owner";
    }
  
   

};

class ProjectLead : public User {

private:
    

public:

    ProjectLead(string name) : User(name) {
    }


    bool hasLeadAccess() {
        return true;
    }

    //overriding virutal function get_name()
    string get_title() const override {
        return name + ": Project Leader";
    }

    string getName() const override {
        return name;
    }

    string getType() const override {
        return "leader";
    }


};

class Developer : public User {

private:

    

public:

    Developer(string name) : User(name) {
    }

    Developer() : User() {}


    //overriding virutal function get_name()
    string get_title() const override {
        return name + ": Developer";
    }

    string getName() const override {
        return name;
    }

    string getType() const override {
        return "developer";
    }
};


User* createUser() {
    cin.ignore(1000, '\n');
    cout << "Enter name of user" << endl;
    string name;
    getline(cin, name);
    cout << "Enter role of user, d for developer, l for lead" << endl;
    string role;

    while (true) {
        cin >> role;

        if (role == "d") {
            return new Developer(name);
        }
        else if (role == "l") {
            return new ProjectLead(name);
        }
        else {
            cout << "please enter a valid letter" << endl;
        }
    }

}

