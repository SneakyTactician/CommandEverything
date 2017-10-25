#include "stdafx.h"
#include "StepMath.h"

using namespace mth;

StepMath::StepMath()
{
}


StepMath::~StepMath()
{
}

Number StepMath::add(Number a, Number b)
{
	if (b.number < 0)
	{
		string step1 = to_string(a.number);
		step1.append(" +");
		step1.append(to_string(b.number));
		step1.append(" = ");
		this->shownSteps->push_back(step1);
		return this->subtract(a, Number(b.number * -1));
	}
	else 
	{
		string step2 = to_string(a.number);
		step2.append(" + ");
		step2.append(to_string(b.number));
		step2.append(" = ");
		step2.append(to_string(a.number + b.number));
		this->shownSteps->push_back(step2);

	}
	return a.number + b.number;
}

Number StepMath::subtract(Number a, Number b)
{
	if (b.number == 0)
	{
		string step1 = to_string(a.number);
		step1.append(" - 0 = ");
		step1.append(to_string(a.number));
		this->shownSteps->push_back(step1);
		return a.number;
	}

	if (b.number > 0)
	{
		string step2 = to_string(a.number);
		step2.append(" - ");
		step2.append(to_string(b.number));
		step2.append(" = ");
		step2.append(to_string(a.number - b.number));
		this->shownSteps->push_back(step2);
		return Number(a.number - b.number);
	}
	else
	{
		string step3 = to_string(a.number);
		step3.append(" -");
		step3.append(to_string(b.number));
		step3.append(" = ");
		this->shownSteps->push_back(step3);
		return this->add(a, Number(b.number * -1));
	}
}

__int64 StepMath::multiply(__int64 a, __int64 b)
{
	string step1 = to_string(a);
	step1.append(" * ");
	step1.append(to_string(b));
	step1.append(" = ");
	step1.append(to_string(a * b));
	this->shownSteps->push_back(step1);
	return a * b;
}

__int64 StepMath::divide(__int64 a, __int64 b, __int8& errorCode)
{
	if (b == 0)
	{
		errorCode = DIVIDE_BY_ZERO;
		this->shownSteps->push_back("Divide by Zero: Undefined");
	}
	else
	{
		string step = to_string(a);
		step.append(" / ");
		step.append(to_string(b));
		step.append(" = ");
		step.append(to_string(a / b));
		this->shownSteps->push_back(step);
		if (a % b != 0)
		{
			this->shownSteps->push_back("Precision loss!");
		}
		return a / b;
	}
}

void mth::IMathObject::toString(string& out)
{
	out = "SOMEONE FORGOT TO DEFINE TOSTRING(). OOPS.";
}