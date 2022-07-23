#pragma once
#include <ntifs.h>
#include <stdarg.h>
#include "encryptXOR.hpp"

namespace n_log
{
	void printf(const char* text, ...)
	{
		va_list(args);
		va_start(args, text);

		vDbgPrintExWithPrefix(XorString("[EAC.LOL] : "), 0, 0, text, args);

		va_end(args);
	}
}