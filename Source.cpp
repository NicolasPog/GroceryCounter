#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("python");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"python");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"python");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}




void main()
{
	//Define variables
	int userEntry = 0;
	string produceItem;
	int produceNumber;


	//Ask for user input
	while (userEntry != 4)
	{
		cout << "1 : Dispaly the list of produce that was purchased today." << endl;
		cout << "2 : Dispaly a specific produce and how many times it was purchased." << endl;
		cout << "3 : Generate a histogram of the produce." << endl;
		cout << "4 : Exit" << endl;
		cout << "Choose from 1, 2, 3, 4." << endl;

		cin >> userEntry; //Get user input
		cout << endl;

		//Error handling if user doesnt pick a correct answer
		if (userEntry != 1 && userEntry != 2 && userEntry != 3 && userEntry != 4) {
			cout << endl;
			cout << "Please select one of the option. ";
			cout << endl;
		}
		//call on python to display pruchases
		if (userEntry == 1)
		{
			CallProcedure("DisplayPurchases");
			cout << endl;
		}

		//Stores the item that was specificed by the user and then stores it into a variable
		//Calls displayList from python and displays the produce and the number of times it appeared on the list
		else if (userEntry == 2)
		{
			cout << "Enter a produce name: " << endl;
			cin >> produceItem;
			cout << endl;
			produceNumber = callIntFunc("DisplayList", produceItem);
			cout << "# of " << produceItem << ": " << produceNumber << endl;
			cout << endl;
		}

		//Runs the python DisplayHistorgram function then grabs the data
		//Will interpret the data and display it as * baed on the quantity of the items
		else if (userEntry == 3)
		{
			//defines variables
			string datProduce;
			int datProduceQuantity;

			CallProcedure("DisplayHistogram");

			ifstream datData;//Uses ifstream from the openstream of the .dat file
			datData.open("C:/Users/Nicolas/Desktop/NICK SNHU/Section 7/FinalProjectCPP/FinalProjectCPP/frequency.dat");//location of the .dat file

			if (!datData) { //Error handling if there is no file found
				cout << "Could not open file. \n";
			}
			else { //when the file is able to be opened it will do the following
				while (datData >> datProduce >> datProduceQuantity) {
					cout << datProduce;
					cout << string(datProduceQuantity, '*') << endl; //uses string() to turn the numbers as *
				}
			}
			datData.close();
			cout << endl;
		}
	}
}



