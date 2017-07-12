#pragma once

#include <string>
#include <Windows.h>
#include <conio.h>

using namespace std;

/// <summary>
/// Used to do some utility functions.
/// </summary>
class Util
{
public:

	/// <summary>
	/// Converts a string to a wstring.
	/// </summary>
	/// <param name="Str"></param>
	/// <returns></returns>
	wstring StringToWString(const string& Str);

	/// <summary>
	/// Returns the next line inputted by the console.
	/// </summary>
	/// <returns></returns>
	string* GetLine();
};