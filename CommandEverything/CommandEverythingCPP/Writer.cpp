#include "stdafx.h"
#include "Writer.h"


Writer::Writer()
{
	Filing* file = new Filing();
	string path;

	//setup converter
	using convert_type = codecvt_utf8<wchar_t>;
	wstring_convert<convert_type, wchar_t> converter;

	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	path = converter.to_bytes(*file->LogDirectoryPath);

	path.append("\\");
	string* now = new string(this->GetTime());
	path.append(*now);
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

	ToDelete->push_back(file);
	ToDelete->push_back(now);
}


Writer::~Writer()
{
	this->Log.close();
	ToDelete->push_back(this->Last);
}

//0 = Red
//1 = Yellow
//2 = Green
//3 = Default/Grey
void Writer::WriteLine(string *Str)
{
	if (Str != NULL && Str->size() > 0)
	{
		this->Last = new string("");
		this->Last->append(this->GetTime());
		this->Last->append(": ");
		this->Last->append(*Str);
		this->Last->append("\r\n");
		cout << this->Last->substr(0, this->Last->size());
		cout.flush();
		this->Log << this->Last->substr(0, this->Last->size());
		this->Log.flush();
	}
	else
	{
		string a = "Someone attempted to write a null or empty string to the console!";
		this->WriteLine(&a);
	}
}

void Writer::WriteLine(const char* Str)
{
	delete this->Msg;
	Msg = new string(Str);
	this->WriteLine(this->Msg);
}

void Writer::LogLine(string *Str)
{
	this->Last = new string("");
	this->Last->append(this->GetTime());
	this->Last->append(": ");
	this->Last->append(Str->c_str());
	this->Last->append("\r\n");
	this->Log << this->Last->substr(0, this->Last->size());
	this->Log.flush();
}

const char * Writer::GetTime()
{
	string* Formatted = new string("[");
	time_t rawtime;
	tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = std::localtime(&rawtime);

	strftime(buffer, 80, "%Y-%m-%d-%H-%M-%S", timeinfo);
	Formatted->append(buffer);
	Formatted->append("]");

	ToDelete->push_back(Formatted);
	ToDelete->push_back(timeinfo);

	const char* Ret = Formatted->c_str();
	return Ret;
}