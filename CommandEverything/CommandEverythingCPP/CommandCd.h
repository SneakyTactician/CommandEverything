#pragma once

/// <summary>
/// Used to change the directory we are working in. Just like CMD.
/// </summary>
class CommandCd : public ICommand
{
public:
	CommandCd();
	~CommandCd();

	bool ShouldRunThisCommand(ParsedCommand* Parsed);

	void Run(ParsedCommand* Parsed);

	string* GetName();

	string* GetHelp();
};
