#include "stdafx.h"
#include "Writer.h"

Writer::Writer()
{
	string path;

	//setup converter
	using convert_type = codecvt_utf8<wchar_t>;
	wstring_convert<convert_type, wchar_t> converter;
	wstring* a = Files->LogDirectoryPath;
	path = converter.to_bytes(*Files->LogDirectoryPath);

	path.append("\\");
	path.append(*this->GetTime());
	path.pop_back();
	path.pop_back();
	path.append(".txt");

	this->Log.open(path, fstream::out);

	if (!Log)
	{
		throw new exception("Can't access file!");
	}
	else
	{
		string message = "Log has initialized successfully";
		this->WriteLine(&message);
	}

	string fileName = *this->GetTime();
	fileName.pop_back();
	fileName.pop_back();
	fileName.append(".txt");
	this->RAIDLog = new RAIDFile(Files->instanceRootDirs, Files->arraySize, "Logs\\", fileName.c_str());
}

Writer::~Writer()
{
	this->Log.close();
}

void Writer::WriteLine(string *Str)
{
	if (Str != NULL && Str->size() > 0)
	{
		cout << *Str;
		cout << "\r\n";
		cout.flush();
		this->LogLine(Str);
	}
	else
	{
		string a = "Someone attempted to write a null or empty string to the console!";
		this->WriteLine(&a);
	}
}

void Writer::WriteLine(const char* Str)
{
	string* Msg = new string(Str);
	this->WriteLine(Msg);
	delete Msg;
}

void Writer::putLine(const char * Str)
{
	//string* time = this->GetTime();
	//this->Log << *time;
	//this->Log << Str;
	//this->Log << "\r\n";
	////this->Log.flush();
	//delete time;
	this->RAIDLog->writeLine(Str);
}

void Writer::LogLine(string *Str)
{
	string* time = this->GetTime();
	this->Log << *time;
	this->Log << *Str;
	this->Log << "\r\n";
	this->Log.flush();
	delete time;
}

string* Writer::GetTime()
{
	string* Formatted = new string("[");
	time_t rawtime;
	tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = std::localtime(&rawtime);

	strftime(buffer, 80, "%Y-%m-%d-%H-%M-%S", timeinfo);
	Formatted->append(buffer);
	Formatted->append("]: ");
	return Formatted;
}