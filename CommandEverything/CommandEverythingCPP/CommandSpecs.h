#pragma once

#include <VersionHelpers.h>

extern "C"
{
#include <Powrprof.h>
}
#pragma comment(lib, "Powrprof.lib")

/// <summary>
/// Puts out some computer specs for you.
/// </summary>
class CommandSpecs : public ICommand
{
public:
	CommandSpecs();
	~CommandSpecs();

	bool ShouldRunThisCommand(ParsedCommand* Parsed);

	void Run(ParsedCommand* Parsed);

	string* GetName();

	string* GetHelp();
private:
	/// <summary>
	/// Writes some information about the OS to the console.
	/// </summary>
	void GetOSInfo();

	/// <summary>
	/// Writes some information about the current state of the processors.
	/// </summary>
	void GetProcessorInfo();
};

typedef struct _PROCESSOR_POWER_INFORMATION {
	ULONG Number;
	ULONG MaxMhz;
	ULONG CurrentMhz;
	ULONG MhzLimit;
	ULONG MaxIdleState;
	ULONG CurrentIdleState;
} PROCESSOR_POWER_INFORMATION, *PPROCESSOR_POWER_INFORMATION;