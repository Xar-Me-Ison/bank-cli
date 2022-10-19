/* ------------------
PRE-DEFINED LIBRARIES
--------------------- */
#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm> 

#include <cstdlib>
#include <cstring>
#include <chrono>
#include <ctime>

#include <thread>

#include <conio.h>
#include <Windows.h> 


/* -------------
GLOBAL VARIABLES 
---------------- */
std::string APPLICATION_VERSION = "[Version 1.00]";

std::string USER_INPUT = "";
std::string USER_LOGGED_DIRECTORY = "";
std::string USER_GUEST_DIRECTORY = "";

std::string UNRECOGNIZED_COMMAND = " is not a recognized command.";

std::string LINE_SEPARATOR = 
"---------------------------------------------------------------------------------";
std::string UNDERLINE_SEPARATOR = 
"_________________________________________________________________________________";

bool STATUS_EXIT_ON = false;
bool TEXT_DELAY_ON = true;
bool MESSAGE_HELP_ON = false;
bool ACCOUNT_CREATED_SUCCESSFULLY = false;


/* ---------------
USER-DEFINED TYPES 
------------------ */
enum TT_Input
{
	BACKSPACE = 8,
	RETURN = 32
};


/* ---------------
CLASS DECLARATIONS 
------------------ */
class BankAccount 
{
	/* Class methods */
public:
	BankAccount(); // Default constructor, to sign up..
	BankAccount(int); // Overloaded constructor, to login..
	~BankAccount(); 


	// Setters 
	void fullNameSetter();
	void genderSetter();
	void ageSetter();

private:
	// Invoked by the default constructor (signing up)..
	void createFullNameFromUser();
	void createGenderFromUser();
	void createUsernameFromUser(); void createPasswordFromUser();
	void createAgeFromUser();

	std::string getPasswordFromUser();
	// Invoked by the overloaded constructor (logging in)..


	/* Class variables */
public:

private:
	std::string fullName;
	std::string gender;
	std::string username, password;
	int age = 0;

	float balance = 0;
};


/* --------------------------
THREAD FUNCTIONS DECLARATIONS 
----------------------------- */
void threadIntroduction();
void threadLogInOrSignUp();


/* ------------------
FUNCTION DECLARATIONS 
--------------------- */
/* Text Effects Functions */
void staticTextEffect(std::string text, int newline);
void typewriterTextEffect(std::string text, int newline, int low_delay = 10, int high_delay = 30);


/* I/O Functions */
void checkYesOrNo(std::string &answer);

/* ----------
MAIN FUNCTION 
------------- */
int main()
{

	while (!STATUS_EXIT_ON)
	{
		threadIntroduction();
		threadLogInOrSignUp();
	}
}


/* --------------
CLASS DEFINITIONS 
----------------- */
/* 	Public */
BankAccount::BankAccount()
{
	std::string input;
	int loop_counter = 0;


	typewriterTextEffect(LINE_SEPARATOR, 1, 1, 1);
 	typewriterTextEffect("GNB - Signing up", 2);

 	if (MESSAGE_HELP_ON)
 	{
	 	typewriterTextEffect("  ' Please note, that the username and password are '", 1);
 		typewriterTextEffect("  ' case-sensitive, the rest are not.               '", 2);
	
 		typewriterTextEffect("  ' In the case of any mistakes, you will be given  '", 1);
 		typewriterTextEffect("  ' the chance to correct them but be aware there's '", 1);
 		typewriterTextEffect("  ' a limit in place.                               '", 2);
 	}

	// May be a bad practice, but leave it like this for now..
 	while (true) 
 	{
 		if (loop_counter == 0)
 		{
 			typewriterTextEffect("Full name: ", 0); createFullNameFromUser();
			typewriterTextEffect("Is your full name \'" +  fullName + "\'? ", 0);
			typewriterTextEffect("[Y/n] > ", 	0); checkYesOrNo(input);

			if (input == "Y")
			{
				loop_counter++;
				continue;
			}
 		}
 		else if (loop_counter == 1)
 		{
			typewriterTextEffect("\nGender: ", 	0); createGenderFromUser();

			typewriterTextEffect("Is your gender \'" +  gender + "\'? ", 0);
			typewriterTextEffect("[Y/n] > ", 	0); checkYesOrNo(input);

			if (input == "Y")
			{
				loop_counter++;
				continue;
			}
 		}
 		else if (loop_counter == 2)
 		{
			typewriterTextEffect("\nAge: ", 	0); createAgeFromUser();

			typewriterTextEffect("Is your age " +  std::to_string(age) + "? ", 0);
			typewriterTextEffect("[Y/n] > ", 	0); checkYesOrNo(input);

			if (input == "Y")
			{
				loop_counter++;
				continue;
			}
 		}
 		else
 		{
			typewriterTextEffect("\nSUCCESS: You're almost set up, please choose a username and password.", 1);
			typewriterTextEffect(LINE_SEPARATOR, 1, 1, 17);

			typewriterTextEffect("Username: ", 0); createUsernameFromUser();
			typewriterTextEffect("Password: ", 0); createPasswordFromUser();

			break;
 		}
	}

	if (ACCOUNT_CREATED_SUCCESSFULLY)
	{
		typewriterTextEffect("\nSUCCESS: Your account has been created, you can now log in.", 1);
	}
	else
	{
		typewriterTextEffect("FAILURE: Your account was not created due to an error.", 1);	
	}

}

BankAccount::BankAccount(int access) 
{
	std::string input;
	int loop_counter = 0;

	typewriterTextEffect(LINE_SEPARATOR, 1, 1, 1);
 	typewriterTextEffect("GNB - Logging in", 2);

 	if (MESSAGE_HELP_ON)
 	{
 		typewriterTextEffect("  ' Help will not come, even you beg for it. The programmer is utterly '", 1);
 		typewriterTextEffect("  ' incompetent at his job and therefore cannot assist further.        '", 2);
 	}

	 typewriterTextEffect("\nFAILURE: Cannot create an account due to the incompetence of the programmer. ", 2);

}
BankAccount::~BankAccount() { }

/*	Private */
/* 	Invoked by the default constructor */
void BankAccount::createFullNameFromUser()
{
	std::string input;

	getline(std::cin, input);

	while (input.size() > 60 || input.size() == 0)
	{
		typewriterTextEffect("Incorrect formatting; try again", 1);
		typewriterTextEffect("Full name: ", 0); getline(std::cin, input);
	}

	std::transform(input.begin(), input.end(), input.begin(), ::toupper);
	fullName = input;
}

void BankAccount::createGenderFromUser()
{
	std::string input;

	getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::toupper);

	while (!(input == "M" || input == "F" || input == "O" ||
		input == "MALE" || input == "FEMALE" || input == "OTHER"))
	{
		typewriterTextEffect("Incorrect formatting; try again.", 1);
		typewriterTextEffect("Gender: ", 0); getline(std::cin, input);

		std::transform(input.begin(), input.end(), input.begin(), ::toupper);
	}

	if (input == "M" || input == "MALE")
	{
		input = "MALE";
	}
	else if (input == "F" || input == "FEMALE")
	{
		input = "FEMALE";
	}
	else
	{
		input = "OTHER";
	}

	gender = input;
}

void BankAccount::createUsernameFromUser()
{
	std::string input;

	getline(std::cin, input);


	// Add another parameter evaluation to check whether the username is already 
	// taken or not based on the database of usernames..
	while (input.size() > 60 || input.size() == 0)
	{
		typewriterTextEffect("Incorrect formatting; try again.", 1);
		typewriterTextEffect("Username: ", 0); getline(std::cin, input);
	}

	username = input;
}

void BankAccount::createPasswordFromUser()
{
	std::string input1, input2;
	bool passwword_match;
	int password_counter = 0;

	do
	{
		if (password_counter != 0)
		{
			typewriterTextEffect("Password: ", 0);
		}

		input1 = getPasswordFromUser();
		while (input1.size() > 40 || input1.size() == 0)
		{	
			typewriterTextEffect("Incorrect formatting; try again.", 2);
			typewriterTextEffect("Password: ", 0); input1 = getPasswordFromUser();
		}

		typewriterTextEffect("Retype password: ", 0); input2 = getPasswordFromUser();

		if (input1 != input2)
		{
			typewriterTextEffect("\nERROR: Passwords do not match; try again.", 1);
			typewriterTextEffect("-", 1);

			if (password_counter > 3)
			{
				ACCOUNT_CREATED_SUCCESSFULLY = false;
				break;
			}
			passwword_match = false;
		}
		else
		{
			ACCOUNT_CREATED_SUCCESSFULLY = true;
			passwword_match = true;
		}

		password_counter++;

	} while (!passwword_match);
}

void BankAccount::createAgeFromUser()
{
	std::string input;

	getline(std::cin, input);

	// Check this one later, there's a problem with the input when 
	// a string is first entered [https://bit.ly/3iofqx0]
	// if (std::isdigit())
	std::stringstream(input) >> age;

	while (age < 16 || age > 120)
	{
		typewriterTextEffect("Incorrect formatting; try again.", 1);
		typewriterTextEffect("Age: ", 0); getline(std::cin, input);
		std::stringstream(input) >> age;
	}
}

std::string BankAccount::getPasswordFromUser()
{
	std::string input = "";	
	char input_ch;

	while (true)
	{
		input_ch = getch();

		if (input_ch < TT_Input::RETURN && input_ch != TT_Input::BACKSPACE)
		{
			typewriterTextEffect("", 1);
			return input;
		}

		// Check whether the user pressed backspace 
		if (input_ch == TT_Input::BACKSPACE)
		{
			if (input.length() == 0)
			{
				continue;
			}
			else
			{
				input.pop_back();
				continue;
			}
		}

		input.push_back(input_ch);
	}
}


/* -------------------------
THREAD FUNCTIONS DEFINITIONS 
---------------------------- */
void threadIntroduction()
{
	system("cls");
	typewriterTextEffect(LINE_SEPARATOR, 1, 1, 1);
	typewriterTextEffect("GNB - Banking Application " + APPLICATION_VERSION, 1);
	typewriterTextEffect("Copyright (C) GNB Corporation. All rights reserved.", 2);
}

void threadLogInOrSignUp()
{
	USER_INPUT = "";
	std::string input;

	BankAccount *accountPtr;
	accountPtr = nullptr;


	do
	{
		// CLI-interface for the default user..
		typewriterTextEffect(USER_GUEST_DIRECTORY + "> ", 0); 

		// Getting the default user's input..
		getline(std::cin, input);

		// If the user's input is empty or whitespace, continue..
		if (!(input.find_first_not_of(' ') != std::string::npos))
			continue;

		USER_INPUT = input;

		// Transforming the user's input to lowercase for easier case matching..
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);

		if (input == "help")
		{
			typewriterTextEffect("Default user's commands. For full functionality please login, or sign up.", 1);
			typewriterTextEffect("DELAY           Allows the default user to turn on/off the text delay.", 1);
			typewriterTextEffect("MESSAGE         Allows the default user to turn on/off helpful messages.", 1);
			typewriterTextEffect("LOGIN           Allows the default user to login to their existing account.", 1);
			typewriterTextEffect("SIGNUP          Allows the default user to create an account.", 1);
			typewriterTextEffect("VERION          Allows the user to the current running version of the app", 1);
			typewriterTextEffect("EXIT            Allows the default user to exit from the application.", 2);
			
		}
		else if (input == "delay") 
		{
			TEXT_DELAY_ON = !TEXT_DELAY_ON;
			typewriterTextEffect("Text delay has been turned ", 0); 
			typewriterTextEffect((TEXT_DELAY_ON) ? "on." : "off.", 2);
		}
		else if (input == "message" || input == "msg")
		{
			MESSAGE_HELP_ON = !MESSAGE_HELP_ON;
			typewriterTextEffect("Helpful messages have been turned ", 0);
			typewriterTextEffect((MESSAGE_HELP_ON) ? "on." : "off.", 2);
		}
		else if (input == "signup" || input == "sign") 
		{
			if (accountPtr == nullptr)
			{
				typewriterTextEffect("\nSUCCESS: Get ready to sign up.", 1);
				accountPtr = new BankAccount;
			}
			else 
			{
				typewriterTextEffect("\nFAILURE:  Unable to create account.", 1);
				continue;
			}
			break;
		}
		else if (input == "login" || input == "log")	
		{
			
			typewriterTextEffect("\nSUCCESS: Get ready to log in.", 1);
			accountPtr = new BankAccount(42);	// The 42 is just a little joke for now, will be changed...

			if (accountPtr == nullptr)
			{
				typewriterTextEffect("\nFAILURE: Unable to log in at this moment.", 1);
				continue;
			}

			delete accountPtr; accountPtr = nullptr;
		}
		else if (input == "version" || input == "ver")
		{
			system("cls");
			typewriterTextEffect(LINE_SEPARATOR, 0, 1, 1);
			typewriterTextEffect("\n" + APPLICATION_VERSION + " | 2021.02 - Developed by Harrison L.", 1);
			typewriterTextEffect("Copyright (C) GNB Corporation. All rights reserved.", 2);
		}
		else if (input == "cls" || input == "clear" || input == "clean")
		{

			system("cls");
		}
		else if (input == "exit" || input == "quit")
		{
			typewriterTextEffect("\nSUCCESS: The process \"GNB.exe\" with PID " + std::to_string(rand()) + " has been terminated.", 1);
			STATUS_EXIT_ON = true;
			return;
		}
		else
		{

			typewriterTextEffect("'" + USER_INPUT + "'" + UNRECOGNIZED_COMMAND, 2); 
		}

	} while (true);
}



/* -----------------
FUNCTION DEFINITIONS  
-------------------- */
/* Text Effects Functions */
void staticTextEffect(std::string text, int newline)
{
	std::cout << text;

	// For the console interface spacing..
	if (newline == 1)
	{
		std::cout << std::endl;
	}
	else if (newline == 2)
	{
		std::cout << std::endl << std::endl;
	}
	else if (newline == 3)
	{
		if (USER_LOGGED_DIRECTORY == "")
		{
			std::cout << std::endl << std::endl << USER_GUEST_DIRECTORY << "> ";	
		}
		else
		{
			std::cout << std::endl << std::endl << USER_LOGGED_DIRECTORY << "> ";
		}
	}
}

void typewriterTextEffect(std::string text, int newline, int low_delay, int high_delay)
{
	srand(time(NULL));

	int rand_sleep = low_delay + (rand() % high_delay);

	// For the static effect..
	if (TEXT_DELAY_ON == false)
	{
		staticTextEffect(text, newline);
		return;
	}

	// For the typewriter effect..
	for (std::string::iterator letter = text.begin(); letter != text.end(); letter++)
	{
		std::cout << *letter;
		Sleep(rand_sleep);
	}


	// For the console interface spacing..
	if (newline == 1)
	{
		std::cout << std::endl;
	}
	else if (newline == 2)
	{
		std::cout << std::endl << std::endl;
	}
	else if (newline == 3)
	{
		if (USER_LOGGED_DIRECTORY == "")
		{
			std::cout << std::endl << std::endl << USER_GUEST_DIRECTORY << "> ";	
		}
		else
		{
			std::cout << std::endl << std::endl << USER_LOGGED_DIRECTORY << "> ";
		}
	}
}

/* I/O Functions */
void checkYesOrNo(std::string &answer)
{
	getline(std::cin, answer);
	std::transform(answer.begin(), answer.end(), answer.begin(), ::toupper);

	while (!(answer == "" || answer == "Y" || answer == "N" || answer == "YES" || answer == "NO" || answer == "YE"))
	{
		typewriterTextEffect("> ", 0); getline(std::cin, answer);
		std::transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
	}

	if (answer == "" || answer == "Y" || answer == "YES"|| answer == "YE")
	{
		answer = "Y";
	}
	else
	{
		answer = "N";
	}
}
