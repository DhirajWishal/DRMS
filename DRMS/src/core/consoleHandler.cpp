#include "drmsafx.h"
#include "consoleHandler.h"

#define _START_COMMAND "DRMS -> "

namespace DRMS {
	consoleHandler::consoleHandler() {
		for (std::string_view output : firstOutput)
			println(output.data());
	}

	consoleHandler::~consoleHandler() {
		firstOutput.clear();
	}

	std::string consoleHandler::getCommand(bool isLowerCase, bool printNew) {
		if (printNew)
			print(_START_COMMAND);
		std::getline(std::cin, myCurrentCommand, '\n');

		if (isLowerCase) {
			std::string _localString = "";
			for (auto i : myCurrentCommand)
				_localString.push_back(std::tolower(i));

			myCurrentCommand = _localString;
		}

		myCommandHistory.push_back(myCurrentCommand);
		return myCurrentCommand;
	}

	void consoleHandler::print(std::string_view output) {
		_printToConsole(output);
	}

	void consoleHandler::println(std::string_view output) {
		_printToConsole(std::string(output) + "\n");
	}

	DRMSResourceFormDataContainer consoleHandler::getFormData(DRMSCommandContainer& container) {
		DRMSResourceFormDataContainer _localContainer = {};
		if (container.type != DRMSCommandType::DRMS_COMMAND_TYPE_REQUEST_FORM)
			return _localContainer;

		std::vector<std::string_view> _localCommands = {
			"Developer ID: ",
			"Developer Name: ",
			"Date (Requested on (DD/MM/YYYY)): ",
			"File Name: ",
			"Reason: ",
			"Estimated Time of Return: "
		};
		std::vector<std::string> _localCommandContainer = {};

		for (std::string_view _command : _localCommands) {
			_printToConsole("\t" + std::string(_command));
			_localCommandContainer.push_back(getCommand(false, false));
		}

		_localContainer.developerID = ((_localCommandContainer[0].size()) ? _localCommandContainer[0] : "NULL");
		_localContainer.developerName = ((_localCommandContainer[1].size()) ? _localCommandContainer[1] : "NULL");
		_localContainer.requestDate = ((_localCommandContainer[2].size()) ? _localCommandContainer[2] : "NULL");
		_localContainer.fileName = ((_localCommandContainer[3].size()) ? _localCommandContainer[3] : "NULL");
		_localContainer.reason = ((_localCommandContainer[4].size()) ? _localCommandContainer[4] : "NULL");
		_localContainer.ETR = ((_localCommandContainer[5].size()) ? _localCommandContainer[5] : "NULL");

		if (container.subType == DRMSCommandSubType::DRMS_COMMAND_SUB_TYPE_UPDATION_FORM) {
			_printToConsole("\tDestination: ");
			_localCommandContainer.push_back(getCommand(false, false));
			_localContainer.destination = ((_localCommandContainer[6].size()) ? _localCommandContainer[6] : "C:\\Users\\USER\\Documents\\");
		}

		return _localContainer;
	}

	std::string consoleHandler::getRepositoryPath() {
		_printToConsole("\t" + std::string("Repository Path: "));
		return getCommand(false, false);
	}

	/* INTERNAL FUNCTIONS */
	void consoleHandler::_printToConsole(std::string_view _output) {
		if (_output.size())
			printf(_output.data());
	}
}