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
		uint32_t _count = myCommands.size();
		if (!_count)
			return _localContainer;


		if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[0]
			&& _commandCheck(_count, DRMSCommandType::DRMS_COMMAND_TYPE_END_SESSION))	// end session
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_END_SESSION;
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[1]
			&& _commandCheck(_count, DRMSCommandType::DRMS_COMMAND_TYPE_REQUEST_FORM)) {	// request
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_REQUEST_FORM;
			return _secondaryCheck(myCommands, _localContainer);
		}
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[2]
			&& _commandCheck(_count, DRMSCommandType::DRMS_COMMAND_TYPE_SUBMIT_FORM)) {	// submit
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_SUBMIT_FORM;
			return _secondaryCheck(myCommands, _localContainer);
		}
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[3]
			&& _commandCheck(_count, DRMSCommandType::DRMS_COMMAND_TYPE_RESOURCE_CHECK)) {	// resource
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_RESOURCE_CHECK;
			return _secondaryCheck(myCommands, _localContainer, 3);
		}
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[4]
			&& _commandCheck(_count, DRMSCommandType::DRMS_COMMAND_TYPE_REQUEST_CANCELATION)) {	// request cancelation
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_REQUEST_CANCELATION;
			return _secondaryCheck(myCommands, _localContainer);
		}
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[5]
			&& _commandCheck(_count, DRMSCommandType::DRMS_COMMAND_TYPE_FOLDER_HIERARCHY)) 	// folder hierarchy
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_FOLDER_HIERARCHY;
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[6]
			&& _commandCheck(_count, DRMSCommandType::DRMS_COMMAND_TYPE_VERIFICATION)) {	// verification
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_VERIFICATION;
			return _secondaryCheck(myCommands, _localContainer);
		}
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[7]
			&& _commandCheck(_count, DRMSCommandType::DRMS_COMMAND_TYPE_PUSH)) 	// push
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_PUSH;
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[8]
			&& _commandCheck(_count, DRMSCommandType::DRMS_COMMAND_TYPE_BUILD_SOLUTION)) 	// build solution
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_BUILD_SOLUTION;
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[9]
			&& _commandCheck(_count, DRMSCommandType::DRMS_COMMAND_TYPE_EXECUTE))	// execute
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_EXECUTE;
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[10]
			&& _commandCheck(_count, DRMSCommandType::DRMS_COMMAND_TYPE_REGISTER))	// register
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_REGISTER;
		else if (myCommands[DRMS_COMMAND_PRIMARY] == myPrimaryCommandTypes[11]
			&& _commandCheck(_count, DRMSCommandType::DRMS_COMMAND_TYPE_ADD)) {	// add
			_localContainer.type = DRMSCommandType::DRMS_COMMAND_TYPE_ADD;
			if (myCommands[DRMS_COMMAND_SECONDARY] == mySecondaryCommandTypes[6])
				_localContainer.subType = DRMSCommandSubType::DRMS_COMMAND_SUB_TYPE_ADD_REPOSITORY;
		}
		else {
			printf("Invalid Command!\n");
		}

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

	bool commandProcessor::_commandCheck(uint32_t count, DRMSCommandType type) {
		switch (type) {
		case DRMSCommandType::DRMS_COMMAND_TYPE_END_SESSION:
			if (count >= 1) return true;
			break;
		case DRMSCommandType::DRMS_COMMAND_TYPE_REQUEST_FORM:
			if (count > 1) return true;
			break;
		case DRMSCommandType::DRMS_COMMAND_TYPE_SUBMIT_FORM:
			if (count > 1) return true;
			break;
		case DRMSCommandType::DRMS_COMMAND_TYPE_RESOURCE_CHECK:
			if (count > 1) return true;
			break;
		case DRMSCommandType::DRMS_COMMAND_TYPE_REQUEST_CANCELATION:
			if (count > 1) return true;
			break;
		case DRMSCommandType::DRMS_COMMAND_TYPE_FOLDER_HIERARCHY:
			if (count >= 1) return true;
			break;
		case DRMSCommandType::DRMS_COMMAND_TYPE_VERIFICATION:
			if (count > 1) return true;
			break;
		case DRMSCommandType::DRMS_COMMAND_TYPE_PUSH:
			if (count >= 1) return true;
			break;
		case DRMSCommandType::DRMS_COMMAND_TYPE_BUILD_SOLUTION:
			if (count >= 1) return true;
			break;
		case DRMSCommandType::DRMS_COMMAND_TYPE_EXECUTE:
			if (count >= 1) return true;
			break;
		case DRMSCommandType::DRMS_COMMAND_TYPE_REGISTER:
			if (count >= 1) return true;
			break;
		case DRMSCommandType::DRMS_COMMAND_TYPE_ADD:
			if (count > 1) return true;
			break;
		default:
			return false;
			break;
		}

		return false;
	}
}