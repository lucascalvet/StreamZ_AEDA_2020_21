#include "menu.h"
#include <limits>
#include <iostream>

using namespace std;

///Handles an invalid input
bool cinFail() {
    if (!cin) {
        cin.clear(); //reset fail bit
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  //ignore bad input
        return true;
    }
    return false;
}

///Checks if user didn't input a number or a number in a determined range
void inputChecker(unsigned &selected, unsigned options) {
    bool in_input = true;
    cout << "Input: ";
    while (in_input) {
        cin >> selected;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (cinFail()) {
            cout << "Please input a number!" << endl;
            cout << "Input: ";
        } else if (selected < options && selected >= 0)
            in_input = false;
        else {
            cout << "Input a number in the options range!" << endl;
            cout << "Input: ";
        }
    }
}

///Stops the console until user presses anything
void stopConsole() {
    cout << endl; //formatting console
    cout << "Press enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * Construct a menu object
 * @param title the menu title
 * @param options the number of options in the menu
 */
Menu::Menu(const string &title, unsigned options) {
    this->title = title;
    this->options = options;
    for (int i = 0; i < options; i++) {
        optionNaming.emplace_back("Default");
    }
}

/**
 * Get the option selected in the menu
 *
 * @return
 */
unsigned int Menu::getSelected() const {
    return selected;
}

/**
 * Change a menu option
 *
 * @param index the option number
 * @param opName the option name
 */
void Menu::changeOption(unsigned int index, const string &opName) {
    if (index > options) {
        cout << "ERROR" << endl;
    } else {
        optionNaming[index] = to_string(index) + ": " + opName;
    }
}

/**
 * Change the menu title
 * @param newTitle the new title
 */
void Menu::changeTitle(const string &newTitle) {
    title = newTitle;
}

/**
 * Add an option to the menu
 *
 * @param opName the option to add
 */
void Menu::addOption(const string &opName) {
    optionNaming.push_back(opName);
    options++;
}

/**
 * Start the menu
 */
void Menu::startMenu() {
    cout << endl << string(title.size(), '*') << endl;
    cout << title << endl;
    cout << string(title.size(), '*') << endl << endl;


    for (int i = 0; i < options; i++) {
        cout << optionNaming[i] << endl;
    }
    inputChecker(selected, options);

    //what to do for each option is coded next
}
