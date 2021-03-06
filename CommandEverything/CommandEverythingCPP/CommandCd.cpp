#include "stdafx.h"
#include "CommandCd.h"

CommandCd::CommandCd()
{
}

CommandCd::~CommandCd()
{
}

bool CommandCd::shouldRunThisCommand(ParsedCommand* Parsed)
{
	return (Parsed->words->at(0) == "cd");
}

void CommandCd::run(ParsedCommand* Parsed)
{
	//If there is a space in the filepath, we need to reparse the input directly.
	//https://github.com/tronkko/dirent/blob/master/examples/ls.c
	if (Parsed->words->size() < 2)
	{
		Console->WriteLine("Missing required argument.");
	}
	else
	{
		//If we need to go up a directory.
		if (Parsed->words->at(1) == "..")
		{
			this->GotoParentDir();
			Console->WriteLine(FilePath);
			return;
		}

		//If we need to stay at the same one.
		if (Parsed->words->at(1) == ".")
		{
			return;
		}

		//If we want to go deeper into a subdirectory.
		this->cdNormal(Parsed);

		Console->WriteLine(FilePath);
	}
}

string* CommandCd::getName()
{
	return new string("CD");
}

string* CommandCd::getHelp()
{
	return new string("Changes the directory we are working from, just like in CMD. Cd \"..\" goes up to the parent directory, while cd \".\" goes to the current directory.");
}

void CommandCd::GotoParentDir()
{
	bool Slashfound = false;

	register size_t i = FilePath->size();

	while (i != 0)
	{
		if (FilePath->at(i - 1) == '\\')
		{
			if (!Slashfound)
			{
				//Found the first slash
				Slashfound = true;
			}
			else
			{
				//Found the second slash, calculating how many characters to remove from the end of the path string.
				size_t pop = FilePath->size() - i;

				while (pop != 0)
				{
					FilePath->pop_back();
					--pop;
				}
				break;
			}
		}
		--i;
	}
}

void CommandCd::cdNormal(ParsedCommand* Parsed)
{
	string arg = *FilePath;

	register unsigned __int64 length = Input.size();

	for (register unsigned __int64 i = 0; i < length; i++)
	{
		if (Input[i] == 'c' || Input[i] == 'C')
		{
			arg.append(Input.substr(i + 3));
			break;
		}
	}

	if (Files->DoesDirectoryExist(&arg))
	{
		delete FilePath;
		FilePath = new string(arg);
		FilePath->append("\\");
	}
	else
	{
		string invalid = "Invalid directory: ";
		invalid.append(arg);
		Console->WriteLine("Directory does not exist!");
		Console->WriteLine(&invalid);
	}
}