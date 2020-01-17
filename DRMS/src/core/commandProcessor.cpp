#include "drmsafx.h"
#include "commandProcessor.h"
#include "functions/functions.h"

namespace DRMS {
	commandProcessor::commandProcessor() {
	}

	commandProcessor::~commandProcessor() {
	}

	DRMSCommandContainer commandProcessor::process(std::string_view command) {
		myCommands = splitLine(command, ' ');
		DRMSCommandContainer _localContainer = {};
		if (!myCommands.size())
			return _localContainer;

		if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[0])	// end session
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_END_SESSION;
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[1]) {	// request
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_REQUEST_FORM;
			return _secondaryCheck(myCommands, _localContainer);
		}
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[2]) {	// submit
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_SUBMIT_FORM;
			return _secondaryCheck(myCommands, _localContainer);
		}
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[3]) {	// resource
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_RESOURCE_CHECK;
			return _secondaryCheck(myCommands, _localContainer, 3);
		}
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[4]) {	// request cancelation
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_REQUEST_CANCELATION;
			return _secondaryCheck(myCommands, _localContainer);
		}
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[5]) 	// folder hierarchy
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_FOLDER_HIERARCHY;
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[6]) {	// verification
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_VERIFICATION;
			return _secondaryCheck(myCommands, _localContainer);
		}
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[7]) 	// push
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_PUSH;
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[8]) 	// build solution
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_BUILD_SOLUTION;
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[9])	// execute
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_EXECUTE;
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[10])	// register
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_REGISTER;

		return _localContainer;
	}

	DRMSCommandContainer commandProcessor::_secondaryCheck(std::vector<std::string> commands, DRMSCommandContainer container, uint32_t indexOffset) {
		if (commands[DRMS_COMMAND_SECONDARY] == mySecondaryCommandTypes[0 + indexOffset])
			container.subType = DRMSCommandSubType::DRMS_COMMAND_SUB_TYPE_CREATION_FORM;
		else if (commands[DRMS_COMMAND_SECONDARY] == mySecondaryCommandTypes[1 + indexOffset])
			container.subType = DRMSCommandSubType::DRMS_COMMAND_SUB_TYPE_UPDATION_FORM;
		else if (commands[DRMS_COMMAND_SECONDARY] == mySecondaryCommandTypes[2 + indexOffset])
			container.subType = DRMSCommandSubType::DRMS_COMMAND_SUB_TYPE_DELETION_FORM;

		return container;
	}
}