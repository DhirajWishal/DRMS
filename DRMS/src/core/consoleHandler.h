#pragma once

#ifndef _DRMS_CONSOLE_HANDLER_H
#define _DRMS_CONSOLE_HANDLER_H

#include <string>
#include <vector>
#include "data store/structures.h"

namespace DRMS {
	class consoleHandler {
	public:
		consoleHandler();
		~consoleHandler();

		std::string getCommand(bool isLowerCase = true, bool printNew = true);

		void print(std::string_view output);
		void println(std::string_view output);

		DRMSResourceFormDataContainer getFormData(DRMSCommandContainer& container);
		std::string getRepositoryPath();

	private:
		void _printToConsole(std::string_view _output);

		std::vector<std::string> firstOutput = {
			"Dynamik Resource Management System",
			"Version: 0.1v",
			"Resource management system for the Dynamik Studio designed and developed by Dhiraj Wishal",
#ifdef DRMS_DEBUG
			"-- DEBUG STAGE --",
#endif
			"\n\n"
		};
		std::string myCurrentCommand = "";
		std::vector<std::string> myCommandHistory = {};
	};
}

#endif