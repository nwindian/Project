  /*
    COPYRIGHT (C) 2017 Joseph Cochran (jmc361) All rights reserved.
    Project Part A
    Author. Joseph Cochran
            jmc361@zips.uakron.edu
    Version 1.01.07.09.2017
    Purpose: The purpose of this part of the project is to make sure that you know how to write a program that declare and use classes and objects, and extends the practice into the use of arrays of objects.
*/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>

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
        //Listnode::next = nullptr;
    }
    ~myListLab();
    void insertNode(Lab, int, int);
    void deleteNode(Lab);
    void appendNode(Lab&);
    friend void login(myListLab array[]);
    friend void display(myListLab array[]);
    //void display(myLab* arr[]);
    friend void logout(myListLab array[]);
    friend void searchArray(myListLab array[]);
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
bool checkLab(myListLab [], int, int );
bool CheckStation(myListLab [], int , int );
void menu();

int getlabnum(myListLab [], int);
int getStationNum(int, myListLab []);
string getName();
int getTime();
void putInArray (Lab **, Lab &, int, int);
void search(Lab **);
void display(Lab **);
//void logout(Lab **);
int getID();
Lab startup(Lab **);
int choicee();
void universities();
myListLab *createArrayofListLabs();
//Const variables
const int NUMLABS = 8;
const int LABSIZES[NUMLABS] = {19, 15, 24, 33, 61, 17, 55,37};
const std::string UNIVERSITYNAMES[NUMLABS] = {"The University of Michigan", "The University of Pittsburgh", "Stanford University", "Arizona State University", "North Texas State University", "The University of Alabama, Huntsville", "Princeton University", "Duquesne University"};
//Main function
int main()
{
    // Create validation and jagged array/menu, then run through program loop.
    universities();
    bool repeat = false;
//
    myListLab universityLabs[NUMLABS];
    for (int i = 0; i < NUMLABS; ++i)
    {
       // universityLabs[i].head = new myListLab::Listnode;
    }

//
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
            //Logs out user
           // logout(ptr);
            repeat = false;
        }
        else if (choice == 3)
        {
            searchArray(universityLabs);
            //Searchs for user
           // search(ptr);
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

//myListLab * createArrayofListLabs()
//{
//
//    myListLab universityLabs[NUMLABS];
//    for (int i = 0; i < NUMLABS; ++i)
//    {
//        cout << "LAB " << i+1 << ":";
//        universityLabs[i].head = new myListLab::Listnode;
////        for (int j = 0; j < LABSIZES[i]; ++j)
////        {
////            Lab* obj = new Lab;
////            cout << " " << j;
////        }
////        cout << endl;
//    }
//    return universityLabs;
//}

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
    cout << setw(65)<< "|                      5) Quit                               |\n";
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

//int getUserID(myListLab ary[],int lab, int station)
//{
//    myListLab::Listnode *nodePtr;
//    myListLab::prevnode *priorNode = nullptr;
//    nodePtr = ary[lab-1].head;
//
//    while (nodePtr && nodePtr->lab != lab)
//    {
//        priorNode = nodePtr;
//        nodePtr = nodePtr->next;
//    }
//    return nodePtr->Stations->getUserID(station);
//}
//Function to check if station is full
//precond: Takes in double pointer, int lab, and int station
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
//precond: Takes in Lab double pointer to navigate and store lab number
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
//Function to search for user
//precond: Takes in Lab double pointer array to search through
//postcond: returns nothing
void search(Lab * ptr[])
{
    //for validation
    bool repeat = true;
    int counter = 0;
    int ID;
    while(repeat == true)
    {
        cout << "Enter the 5 digit ID number of the user to find" << endl;
        //gets id
        cin >> ID;
        //validation
        if (cin.fail())
        {
            repeat = true;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Please enter a number." << endl;
        }
        else
        {
            repeat = false;
        }
    }
    //searches through array
    for (int i = 0; i < NUMLABS; i++)
    {
        for (int j = 0; j < LABSIZES[i]; j++)
        {
            Lab person = ptr[i][j];
            //if found, prints out where user is
            if (person.getUID() == ID)
            {
                ++counter;
                cout << "User " << ID << " is in lab " << i + 1 << " at computer " << j + 1 << endl;
            }
        }
    }
    //if user is not found
    if (counter == 0)
    {
        cout << "User not found!" << endl;
    }
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
        if (cin.fail() || choice > 5 || choice < 1)
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

    newNode = new Listnode;
    newNode->object.setID(obj.getUID());
    newNode->object.setName(obj.getName());
    newNode->object.setTime(obj.gettime());
    newNode->station = stationNum;
    newNode->lab = labChoice;

    if(!head)
    {
        head = newNode;
        newNode->next = nullptr;
    }
    else
    {
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
//class function
void myListLab::appendNode(Lab& obj)
{
    Listnode *node;
    Listnode *nodeptr;
    node = new Listnode;
    //Assign values for append
    node->object = obj;
    node->next = nullptr;

    if(!head)
    {
        //Assign the head value to the new node
        head = node;
    }
    else
    {
        nodeptr = head;
        while(nodeptr->next)
        {
            nodeptr = nodeptr->next;
        }
        nodeptr->next = node;
    }
}

void login(myListLab arr[])
{
    int labchoice = getlabnum(arr);
    int stationchoice = getStationNum(labchoice,arr);
    int ID = getID();
    string name = getName();
    int time = getTime();
    Lab person(ID, name, time);
    arr[labchoice-1].insertNode(person, stationchoice,labchoice);
    ++arr[labchoice-1].size;




}


void logout(myListLab arr[])
{
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

void searchArray(myListLab arr[])
{
        myListLab::Listnode *nodePtr;
    //for validation
    bool repeat = true;
    int ID;
    //int arrcounter = 0;
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
            if (counter == 18)
            {
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
