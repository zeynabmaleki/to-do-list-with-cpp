#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

void menu(void);
void newTask(void);
void viewAll(void);
void deletTask(void);

void menu()
{
    int answer;

    cout << "What do you want to do? (1 - 3)\n 1.Add new task\n 2.Remove a task\n 3.view all tasks\n 4.Exit\n ";
    cin >> answer;
    switch (answer)
    {
    case 1:
        newTask();
        break;
    case 2:
        deletTask();
        break;
    case 3:
        viewAll();
        break;
    case 4:
        cout << " Exiting program!";
        exit(0);
        break;
    default:
        cout << "Wrong option! Please try again.\n";
        break;
    }
}

void newTask()
{
    string task;
    cout << "Enter your task: " << endl;
    cin >> task;
    ofstream todolistFile("todolist.txt", ios::app);
    if (todolistFile.is_open())
    {
        todolistFile << task << endl;
        todolistFile.close();
        cout << "New task added!" << endl;
    }
    else
    {
        cout << "Unable to open the file." << endl;
    }
    todolistFile.close();
    menu();
}

void viewAll()
{
    string data;
    ifstream todolistFile("todolist.txt");
    while (getline(todolistFile, data))
    {
        cout << data << endl;
    }
    menu();
}

void deletTask()
{

    ifstream todolistFile("todolist.txt");
    if (!todolistFile.is_open())
    {
        cout << "Unable to open the file." << endl;
        return;
    }

    string task;
    string taskToDelete;
    vector<string> temp;
    bool found = false;

    cout << "Enter task you want to remove: " << endl;
    //cin >> taskToDelete;
    cin.ignore();
    getline(cin, taskToDelete);

    while (getline(todolistFile, task))
    {
        if (task != taskToDelete)
        {
            temp.push_back(task);
        }
        else
        {
            found = true;
        }
    }
    todolistFile.close();

    if (found)
    {
        ofstream outFile("todolist.txt", ios::trunc);
        // open the file in truncate mode to clear the content
        if (outFile.is_open())
        {
            for (const auto &t : temp)
            {
                outFile << t << endl;
            }
            outFile.close();
            cout << "Task deleted." << endl;
        }
        else
        {
            cout << "Unable to open the file.";
        }
    }
    else
    {
        cout << "Task not found\n";
    }
    menu();
}

int main()
{
    cout << " Welcome to your to do list.\n ";
    menu();
    return 0;
}
