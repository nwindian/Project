 /*
    COPYRIGHT (C) 2017 Joseph Cochran (jmc361) All rights reserved.



    Project Part C
Test
    Author. Joseph Cochran
            jmc361@zips.uakron.edu
    Version 1.01.07.09.2017
    Purpose: Purpose of this part of the project is to make sure that you know how to write a program
            that will leverage linked lists, and leverages file usage and file operations as well
*/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <fstream>

using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::setw;
using std::numeric_limits;
// Lab class for all objects
class Lab
{
private:
    //Data for class
    int userID;
    std::string name;
    int time;
public:
    //Default constructor
    Lab();
    //Constructor
    Lab(int id,string namee, int timee);
    //Setters and Getters and other functions
    void setID(int IDD);
    int getUID();
    string getName();
    void setName(string namee);
    int gettime();
    void setTime(int timee);
    bool operator==(const Lab&);
};
//Class for my list lab
class myListLab
{
public:
    myListLab(){
        head = nullptr;
        size = 0;
    }
    ~myListLab();
    void insertNode(Lab, int, int);
    void deleteNode(Lab);
    void appendNode(Lab&);
    friend void login(myListLab array[]);
    friend void display(myListLab array[]);
    friend void logout(myListLab array[]);
    friend void searchArray(myListLab array[]);
    friend void recover(myListLab array[]);
    //Node for linked list
    struct Listnode
    {
        Lab object;
        int station;
        int lab;
        int count;
        struct Listnode *next;
    };
    Listnode *head;
    int size;
};
// Nonmember functions
char *timeStamp();
bool checkLab(myListLab [], int, int );
bool CheckStation(myListLab [], int , int );
void menu();
void logFile(Lab , bool);
int getlabnum(myListLab [], int);
int getStationNum(int, myListLab []);
string getName();
int getTime();
int getID();
int choicee();
void universities();
//Const variables
const int NUMLABS = 8;
const int LABSIZES[NUMLABS] = {19, 15, 24, 33, 61, 17, 55,37};
const std::string UNIVERSITYNAMES[NUMLABS] = {"The University of Michigan", "The University of Pittsburgh", "Stanford University", "Arizona State University", "North Texas State University", "The University of Alabama, Huntsville", "Princeton University", "Duquesne University"};
//Main function
int main()
{
    universities();
    bool repeat = false;
    myListLab universityLabs[NUMLABS];
    int labChoice;
    int capacity = 0;
    int stationN;
    string name;
    int time;
    while(repeat == false)
    {
        //Get choice
        int choice = choicee();
        if (choice == 1)
        {
            login(universityLabs);
            ++capacity;
            repeat = false;
        }
        else if (choice == 2)
        {
            logout(universityLabs);
            repeat = false;
        }
        else if (choice == 3)
        {
            searchArray(universityLabs);
            repeat = false;
        }
        else if (choice == 4)
        {
            //Displays lab
            display(universityLabs);
            repeat = false;
        }
        else if (choice == 5)
        {
            recover(universityLabs);
            repeat = false;
        }
        else if (choice == 6)
        {
            //returns if quit
            return 0;
        }
    //To continue on
    cout << endl << "Press any key to continue." << endl;
    cin.ignore();
    cin.get();
    }
    return 0;
}
//Default constructor for Lab
//precond: takes in nothing
//postcond: returns nothing
Lab::Lab()
{
    userID = -1;
    name = " ";
    time = 0;
}
//Overloaded constructor for lab
//precond: Takes in data for class
//postcond: returns nothing
Lab::Lab(int id, string namee, int timee)
{
    userID = id;
    name = namee;
    time = timee;
}
//Menu for the program
//precond: Takes in nothing, just prints menu
//postcond: returns nothing
void menu()
{
    //menu
    cout << std::internal << std::setprecision(1) << std::fixed << std::showpoint << endl;
    cout << setw(64)<< "____________________________________________________________\n";
    cout << setw(65)<< "|------------------------------------------------------------|\n";
    cout << setw(65)<< "|                  Joseph Cochran Incorporated               |\n";
    cout << setw(65)<< "|                      Computer Lab System                   |\n";
    cout << setw(65)<< "|                                                            |\n";
    cout << setw(65)<< "|____________________________________________________________|\n";
    cout << setw(65)<< "|                          MAIN MENU                         |\n";
    cout << setw(65)<< "|                      1) Simulate login                     |\n";
    cout << setw(65)<< "|                      2) Simulate logoff                    |\n";
    cout << setw(65)<< "|                      3) Search                             |\n";
    cout << setw(65)<< "|                      4) Display a lab                      |\n";
    cout << setw(65)<< "|                      5) Recover User                       |\n";
    cout << setw(65)<< "|                      6) Quit                               |\n";
    cout << setw(65)<< "|____________________________________________________________|\n";
}
//Function to check if lab is full
//precond: Takes in Lab double pointer and int
//postcond: returns true or false whether lab is full
bool checkLab(myListLab ary[], int labChoice)
{
    if(!ary[labChoice-1].size)
    {
        return false;
    }
    if(ary[labChoice-1].size < LABSIZES[labChoice-1])
    {
        return false;
    }
    else
    {
        return true;
    }
}
//Function to check if station is full
//precond: Takes in mylistlab array, int lab, and int station
//postcond: returns true or false depending on if full
bool CheckStation(myListLab ary[], int labChoice, int Station)
{
    int count = -1;
    int ID;
    myListLab::Listnode *nodePtr;
    myListLab::Listnode *tailNode;
    nodePtr = ary[labChoice - 1].head;

    //Validates if station is empty or not.
    if (!ary[labChoice - 1].head)
    {
        return false;
    }
    //goes through linked list to get a match
    while (count != ary[labChoice-1].size -1)
    {
        if (nodePtr->station == Station)
        {
            if (nodePtr->object.getUID() == -1)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        nodePtr = nodePtr->next;
        ++count;
    }
    tailNode = nodePtr;
    nodePtr = ary[labChoice-1].head;
    return false;
}

//Function to get random id of user
//precond: Takes in nothing, creates random int
//postcond: returns Random number int
int getID()
{
    std::srand(std::time(NULL));
    int ID = (std::rand() % 99998) + 1;
    cout << endl << endl << "User Id: " << std::setw(5) << std::setfill('0') << ID << std::setfill(' ') << endl;
    return ID;
}
//Function to get lab number from user
//precond: Takes in mylistlab array to navigate and store lab number
//postcond: returns int lab choice
int getlabnum(myListLab obj[])
{
    bool repeat = true;
    int labChoice;
    //Put in loop for validation
    while (repeat == true)
    {
        cout << "Enter the lab number the user is logging in from : ";
        //get lab number
        cin >> labChoice;
        if (cin.fail() || labChoice < 1 || labChoice > 8)
        {
            //validation
            repeat = true;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Please enter valid input" << endl;
        }
        else
        {
            //Checks if lab is full
            bool ifFull = checkLab(obj, labChoice);
            if (ifFull == true)
            {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Lab is full, please choose another lab." << endl;
                repeat = true;
            }
            else
            {
                repeat = false;
            }
            if (repeat == true)
            {
                repeat = true;
            }
            else
            {
                repeat = false;
            }
        }
    }
    return labChoice;
}
//Function to get station number from user
//precond: takes in int lab choice and Lab double pointer to navigate and store station
//postcond: returns int for station
int getStationNum(int labChoice, myListLab obj[])
{
    bool repeat = true;
    int stationNum;
    //Goes through set of operations from what lab the user chose.
    if (labChoice == 1)
    {
        while (repeat == true)
        {
            //Asks for station
            cout << "Enter the station" << endl;
            cin >> stationNum;
            //validates
            if(cin.fail() || stationNum < 1 || stationNum > 19)
            {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Please enter number 1-19" << endl;
            }
            else
            {
                //Checks if station is full
                bool isFull = CheckStation(obj, labChoice, stationNum);
                if (isFull == true)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Full, please choose another station." << endl;
                    repeat = true;
                }
                else
                {
                    repeat = false;
                }
            }
        }
    }
    else if (labChoice == 2)
    {
        while (repeat == true)
        {
            cout << "Enter the station" << endl;
            cin >> stationNum;
            //validates
            if(cin.fail() || stationNum < 1 || stationNum > 15)
            {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Please enter number 1-15" << endl;
            }
            else
            {
                //Checks if station is full
                bool isFull = CheckStation(obj, labChoice, stationNum);
                if (isFull == true)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Full, please choose another station." << endl;
                    repeat = true;
                }
                else
                {
                    repeat = false;
                }
            }
        }
    }
    else if (labChoice == 3)
    {
        while (repeat == true)
        {
            cout << "Enter the station" << endl;
            cin >> stationNum;
            //validation
            if(cin.fail() || stationNum < 1 || stationNum > 24)
            {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Please enter number 1-24" << endl;
            }
            else
            {
                //checks if station is full
                bool isFull = CheckStation(obj, labChoice, stationNum);
                if (isFull == true)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Full, please choose another station." << endl;
                    repeat = true;
                }
                else
                {
                    repeat = false;
                }
            }
        }
    }
    else if (labChoice == 4)
    {
        while (repeat == true)
        {
            cout << "Enter the station" << endl;
            cin >> stationNum;
            //validation
            if(cin.fail() || stationNum < 1 || stationNum > 33)
            {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Please enter number 1-33" << endl;
            }
            else
            {
                //checks if station is full
                bool isFull = CheckStation(obj, labChoice, stationNum);
                if (isFull == true)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Full, please choose another station." << endl;
                    repeat = true;
                }
                else
                {
                    repeat = false;
                }
            }
        }
    }
    else if (labChoice == 5)
    {
        while (repeat == true)
        {
            cout << "Enter the station" << endl;
            cin >> stationNum;
            //validation
            if(cin.fail() || stationNum < 1 || stationNum > 61)
            {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Please enter number 1-61" << endl;
            }
            else
            {
                //checks if station is full
                bool isFull = CheckStation(obj, labChoice, stationNum);
                if (isFull == true)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Full, please choose another station." << endl;
                    repeat = true;
                }
                else
                {
                    repeat = false;
                }
            }
        }
    }
    else if (labChoice == 6)
    {
        while (repeat == true)
        {
            cout << "Enter the station" << endl;
            cin >> stationNum;
            //validation
            if(cin.fail() || stationNum < 1|| stationNum > 17)
            {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Please enter number 1-17" << endl;
            }
            else
            {
                //checks if station is full
                bool isFull = CheckStation(obj, labChoice, stationNum);
                if (isFull == true)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Full, please choose another station." << endl;
                    repeat = true;
                }
                else
                {
                    repeat = false;
                }
            }
        }
    }
    else if (labChoice == 7)
    {
        while (repeat == true)
        {
            cout << "Enter the station" << endl;
            cin >> stationNum;
            //validation
            if(cin.fail() || stationNum < 1 || stationNum > 55)
            {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Please enter number 1-55" << endl;
            }
            else
            {
                //checks if station is full
                bool isFull = CheckStation(obj, labChoice, stationNum);
                if (isFull == true)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Full, please choose another station." << endl;
                    repeat = true;
                }
                else
                {
                    repeat = false;
                }
            }
        }
    }
    else if (labChoice == 8)
    {
        while (repeat == true)
        {
            cout << "Enter the station" << endl;
            cin >> stationNum;
            //validation
            if(cin.fail() || stationNum < 1 || stationNum > 37)
            {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Please enter number 1-37" << endl;
            }
            else
            {
                //checks if station is full
                bool isFull = CheckStation(obj, labChoice, stationNum);
                if (isFull == true)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Full, please choose another station." << endl;
                    repeat = true;
                }
                else
                {
                    repeat = false;
                }
            }
        }
    }
    return stationNum;
}
//Function to get name of user
//precond: Takes in nothing
//postcond: returns the string name of the user.
string getName()
{
    //for validation
    bool repeatT = true;
    string name;
    cin.ignore();
    while(repeatT == true)
    {
        cout << "Please enter the name of this user: " << endl;
        getline(cin,name);
        if(name == "" || name == " " || name.size() > 35)
        {
            cin.clear();
            repeatT = true;
        }
        else
        {
            repeatT = false;
        }
    }
    return name;
}
//Function to get time User is on
//precond: takes in nothing
//posotcond: returns int time of the user.
int getTime()
{
    //for validation
    bool repeatM = true;
    int minutes;
    while(repeatM == true)
    {
        cout << setw(15) << "Please enter the minutes of use for the work station (15/30/45/60) " << endl;
        cin >> minutes;
        //validation
        if (minutes == 15 || minutes == 30 || minutes == 45 || minutes == 60)
        {
            repeatM = false;
        }
        else
        {
            repeatM = true;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Enter time" << endl;
        }
    }
    return minutes;
}
//Class member function to get id of person
//precond:takes in nothing
//postcond:returns person object id
int Lab::getUID()
{
    return userID;
}

int Lab::gettime()
{
    return time;
}
//Lab member function for changing persons id
//precond: takes in int id to change the person id to that.
//postcond: returns nothing
void Lab::setID(int IDD)
{
    userID = IDD;
}
//Lab member function for changing persons time
//precond: takes in int time to change the person time to that.
//postcond: returns nothing
void Lab::setTime(int timee)
{
    time = timee;
}
//Lab member function for changing persons name
//precond: takes string name to change the person name to that.
//postcond: returns nothing
void Lab::setName(string namee)
{
    name = namee;
}
//Lab member function for getting objects name
//precond: takes in nothing
//postcond: returns string name of object
string Lab::getName()
{
    return name;
}
//Function so the user can logout of station
//precond: takes in Lab double pointer array to search through array to find user
//postcond: returns nothing

//Function to get first choice of user
//precond: Takes in nothing, just gets choice
//postcond: returns the choice of the user
int choicee()
{
    menu();
    //for validation
    int choice;
    bool repeat = true;
    while (repeat == true)
    {
        cout << endl << std::setw(35) << "Your Choice: ";
        cin >> choice;
        //validation
        if (cin.fail() || choice > 6 || choice < 1)
        {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Please enter valid number" << endl;
            repeat = true;
        }
        else
        {
            repeat = false;
        }
    }
    //returns the choice
    return choice;
}
//Function to print out universities
//precond:Takes in nothing, just prints out universities
//postcond: returns nothing
void universities()
{
    //prints them out
    cout << "       Welcome - here is our list of available labs" << endl;
    //Prints out schools with available labs
    for (int i = 1; i <= NUMLABS; i++)
    {
        cout << "lab # " << i << " " << UNIVERSITYNAMES[i-1] << endl;
    }
}
//destructor for mylistlab
//precond: takes in nothing
//postcond: returns nothing, just destroys node.
myListLab::~myListLab()
{
    Listnode *nodePtr;   // To traverse the list
    Listnode *nextNode;  // To point to the next node
    // Position nodePtr at the head of the list.
    nodePtr = head;
    // While nodePtr is not at the end of the list...
    while (nodePtr != nullptr)
    {
        // Save a pointer to the next node.
        nextNode = nodePtr->next;
        // Delete the current node.
        delete nodePtr;
        // Position nodePtr at the next node.
        nodePtr = nextNode;
    }
}
//Operator overloader for ==
//precond: passes reference to lab object
//postcond: returns bool for if the obejcts are equivalent
bool Lab::operator==(const Lab &obj)
{
    if (userID == obj.userID)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//class function to insert node to linked list
//precond:passes the lab, stationNum, and lab choice for the node to be inserted
//postcond: returns nothing
void myListLab::insertNode(Lab obj, int stationNum, int labChoice)
{
    Listnode *newNode;
    Listnode *nodePtr;
    Listnode *prevNode = nullptr;
    //assigns values
    newNode = new Listnode;
    newNode->object.setID(obj.getUID());
    newNode->object.setName(obj.getName());
    newNode->object.setTime(obj.gettime());
    newNode->station = stationNum;
    newNode->lab = labChoice;
    //check if head is there
    if(!head)
    {
        head = newNode;
        newNode->next = nullptr;
    }
    else
    {
        //assign nodePtr and go through to insert node
        nodePtr = head;
        while(nodePtr && nodePtr->station < stationNum)
        {
            prevNode = nodePtr;
            nodePtr = nodePtr->next;
        }

        if (prevNode == nullptr)
        {
            head = newNode;
            newNode->next = nodePtr;
        }
        else
        {
            prevNode->next = newNode;
            newNode->next = nodePtr;
        }
    }
}
//Class function to delete node from list node
//precond: passes object to delete the node with that object
//postcond: returns nothing
void myListLab::deleteNode(Lab obj)
{
    Listnode *nodePtr;
    Listnode *previousNode;
    // Checks for head value
    if(!head)
    {
        return;
    }
    //Checks if head value is equivalent to value passed
    if (head->object == obj)
    {
        nodePtr = head->next;
        delete head;
        head = nodePtr;
    }
    else
    {
        nodePtr = head;
        // loops through to assign the previous node and node pointer
        while(nodePtr!=nullptr && nodePtr->object.getUID() != obj.getUID())
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }
        //Checks for  the new node pointer
        if(nodePtr)
        {
            previousNode->next = nodePtr->next;
            delete nodePtr;
        }
    }
}
//function to print the current time
//precond: takes in nothing, just prints current time
//postcond: returns cstring that holds time
char* timeStamp()
{
    // current date/time based on current system
    time_t Ctime = time(0);
    // convert now to c-string form
    char* Ptime = ctime(&Ctime);
    // we want a way to limit the size to be just 20 in length
    Ptime[20] = '\0'; // this effectively truncates the c-string
    return Ptime;
}
//Function that logs info into a file
//precond: Takes in a Lab object and bool to see if its input or output
//postcond: returns nothing
void logFile(Lab obj, bool log)
{
    std::ofstream logFile;
    logFile.open("logf.txt", std::ofstream::app);
    //checks if file exists
    if (!logFile)
    {
        logFile << std::setw(5) << std::left << "  Name" << std::right
            << "UserID " << "Time " << "Date" << std::endl;
    }
    if (log)
    {
        logFile << std::setw(5) << std::setfill('0') << obj.getUID() << std::setfill(' ') << " I " << obj.getName() << " " << obj.gettime() << " " << timeStamp() << endl;
    }
    else
    {
        logFile << std::setw(5) << std::setfill('0') << obj.getUID() << std::setfill(' ') << " O " << obj.getName() << " " << obj.gettime() << " " << timeStamp() << endl;
    }
    logFile.close();

}
//friend function that logs a user in to the linked list. Also logs them into the file;
//precond: Takes in nothing, just logs in user
//postcond: returns nothing
void login(myListLab arr[])
{
    bool login = true;
    int labchoice = getlabnum(arr);
    int stationchoice = getStationNum(labchoice,arr);
    int ID = getID();
    string name = getName();
    int time = getTime();
    Lab person(ID, name, time);
    arr[labchoice-1].insertNode(person, stationchoice,labchoice);
    ++arr[labchoice-1].size;
    logFile(person, login);
}
//friend function that logs out the user and removes from linked list
//precond: Takes in myListLab Array to search through
//postcond: returns nothing
void logout(myListLab arr[])
{
    bool logoutt = false;
    myListLab::Listnode *nodePtr;
    //for validation
    bool repeat = true;
    int ID;
    //int arrcounter = 0;
    while(repeat == true)
    {
        cout << "Enter your 5 digit ID to logout" << endl;
        //get id to logout
        cin >> ID;
        //validation
        if (cin.fail())
        {
            repeat = true;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Please enter a valid ID." << endl;
        }
        else
        {
            repeat = false;
        }
    }
    //search array for user
    for (int i = 0; i < NUMLABS; ++i)
    {
        int count = -1;
        nodePtr = arr[i].head;
        while (count != arr[i].size - 1)
        {
            if (ID == nodePtr->object.getUID())
            {
                logFile(nodePtr->object,logoutt);
                cout << "Thank you for signing out " << nodePtr->object.getName() << endl;
                arr[i].deleteNode(nodePtr->object);
                --arr[i].size;
                return;
            }
            nodePtr = nodePtr->next;
            ++count;
        }
    }
    cout << "User not found! "<< endl;
    return;
}
//function to search through linked list and print the user if found
//precond: Takes in myListLab to help search through
//postcond: returns nothing.
void searchArray(myListLab arr[])
{
    myListLab::Listnode *nodePtr;
    //for validation
    bool repeat = true;
    int ID;
    while(repeat == true)
    {
        cout << "Enter your 5 digit ID for the user to find" << endl;
        //get id to logout
        cin >> ID;
        //validation
        if (cin.fail())
        {
            repeat = true;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Please enter a valid ID." << endl;
        }
        else
        {
            repeat = false;
        }
    }
    //search array for user
    for (int i = 0; i < NUMLABS; ++i)
    {
        int count = -1;
        nodePtr = arr[i].head;
        while (count != arr[i].size - 1)
        {
            if (ID == nodePtr->object.getUID())
            {
                cout << "User " << std::setw(5) << std::setfill('0') << nodePtr->object.getUID() << std::setfill(' ') << ", " << nodePtr->object.getName() << ", is in lab "<<
                nodePtr->lab << " at computer " << nodePtr->station <<  endl;
                return;
            }
            nodePtr = nodePtr->next;
            ++count;
        }
    }
    cout << "User not found! "<< endl;
    return;
}
//Function to display the lab the user wants
//precond: takes in mylistlab array containing the mylistlab linked lists
//postcond: returns nothing
void display(myListLab ary[])
{
    //for validation
    int counter = 0;
    int count = 0;
    int labN;
    bool repeat = true;
    myListLab::Listnode * nodeptr;
    while (repeat == true)
    {
        //gets lab to display
        cout << "Please enter the lab to display: ";
        cin >> labN;
        //validation
        if (cin.fail() || labN < 1 || labN > 8)
        {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Please enter valid lab." << endl;
            repeat = true;
        }
        else
        {
            repeat = false;
        }
    }
    //Goes through array and displays lab
    int size = ary[labN-1].size;
    cout << "LAB STATUS" << endl << "Lab    # " << labN << " for " << UNIVERSITYNAMES[labN-1] << endl << "Computer Stations " << endl;
    //checks if head
    if (!ary[labN-1].head)
    {
        for (int i = 0; i < LABSIZES[labN-1]; ++i)
        {
            if (counter % 5 == 0 && counter != 0)
            {
                cout << endl << i + 1 << " : " << "empty  ";
                counter++;
            }
            else
            {
                cout << i + 1 << " : empty  ";
                counter++;
            }
        }
    }
    else
    {
        nodeptr = ary[labN-1].head;
        for (int i = 0; i < LABSIZES[labN-1]; ++i)
        {
            //checks if the end of the linked list
            if (count == ary[labN-1].size)
            {
                while(counter < LABSIZES[labN-1])
                {
                    if (counter % 5 == 0 && counter != 0)
                    {
                        cout << endl << counter + 1 << " : " << "empty  ";
                        counter++;
                    }
                    else
                    {
                        cout << counter + 1 << " : empty  ";
                        counter++;
                    }
                }
                break;
            }
            //checks if it is the end of the number of stations
            if (counter == LABSIZES[labN-1]-1)
            {
                //checks if empty or not
                if (nodeptr->object.getUID() == -1)
                {
                    if (counter % 5 == 0 && counter != 0)
                    {
                        cout << endl << i + 1 << " : " << "empty  ";
                        ++counter;
                        break;
                    }
                    else
                    {
                        cout << i + 1 << " : " << "empty  ";
                        ++counter;
                        break;
                    }

                }
                else
                {
                    if (counter % 5 == 0 && counter != 0)
                    {
                        cout << endl << i + 1 << " : " << std::setw(5) << std::setfill('0') << nodeptr->object.getUID() << std::setfill(' ') << "  ";
                        ++counter;
                        break;
                    }
                    else
                    {
                        cout << i + 1 << " : " << std::setw(5) << std::setfill('0') << nodeptr->object.getUID() << std::setfill(' ') << "  ";
                        ++counter;
                        break;
                    }
                }
            }
            else
            {
                //checks if it is empty
                if (nodeptr->station != i+1)
                {
                    if (counter % 5 == 0 && counter != 0)
                    {
                        cout << endl << i + 1 << " : " << "empty  ";
                        ++counter;
                    }
                    else
                    {
                        cout << i + 1 << " : " << "empty  ";
                        ++counter;
                    }

                }
                else
                {
                    //checks if 5 users are listed on the line
                    if (counter % 5 == 0 && counter != 0)
                    {
                        cout << endl << i + 1 << " : " << std::setw(5) << std::setfill('0') << nodeptr->object.getUID() << std::setfill(' ') << "  ";
                        ++counter;
                        ++count;
                            nodeptr = nodeptr->next;
                    }
                    else
                    {
                        cout << i + 1 << " : " << std::setw(5) << std::setfill('0') << nodeptr->object.getUID() << std::setfill(' ') << "  ";
                        ++counter;
                        ++count;
                            nodeptr = nodeptr->next;
                    }
                }
            }
        }
    }
}
//function to recover a person from the file and log them in
//precond: Takes in myListLab array to help search through
//postCond: returns nothing
void recover(myListLab ary[])
{
    //All variables used for counting and files
    int count = 0;
    std::ifstream log;
    log.open("logf.txt");
    int ID;
    int labN;
    bool repeat = true;
    string timeS;
    string IorO;
    int fileID;
    string name;
    int time;
    bool found = true;
    bool repWhile = true;
    //create a nodePtr for linked list
    myListLab::Listnode *nodeptr;
    //validation
    while (repeat == true)
    {
        cout << "Please enter an ID to recover: " << endl;
        cin >> ID;
        //validation
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Please enter valid ID." << endl;
            repeat = true;
        }
        else
        {
            repeat = false;
        }
    }
    repeat = true;
    while (repeat == true)
    {
        cout << "Please enter the lab: ";
        cin >> labN;
        //validation
        if (cin.fail() || labN < 1 || labN > 8)
        {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Please enter valid lab." << endl;
            repeat = true;
        }
        else
        {
            repeat = false;
        }
    }
    //Search through file to check if user is there
    while(log >> fileID)
    {
        log >> IorO >> name >> time;
        log.ignore(numeric_limits<std::streamsize>::max(), '\n');
        if (fileID == ID)
        {
            found = true;
            break;
        }
        else
        {
            found = false;
        }
    }
    if (found == false)
    {
        cout << "User Not found!!" << endl;
        return;
    }
    else
    {
        //This is to check what the next open station is.
        int openStat = 1;
        Lab person(fileID,name,time);
        nodeptr = new myListLab::Listnode;
        nodeptr = ary[labN-1].head;
        while(nodeptr && count < ary[labN-1].size)
        {
            if (repWhile == false)
            {
                break;
            }
            for (int i = 0; i < LABSIZES[labN-1]; ++i)
            {
                if (count == ary[labN-1].size)
                {
                    openStat = i+1;
                    repWhile = false;
                    break;
                }
                else if (nodeptr->station == i + 1)
                {
                    nodeptr = nodeptr->next;
                    ++count;
                }
                else
                {
                    openStat = i+1;
                    repWhile = false;
                    break;
                }
            }
        }
        //log the user in
        ary[labN-1].insertNode(person,openStat,labN);
        cout << "Thanks for recovering!" << endl;
        ++ary[labN-1].size;
        return;
    }
}
