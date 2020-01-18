#include "drmsafx.h"
#include "src/DRMS.h"
using namespace DRMS;

consoleHandler myConsoleHandler = {};
commandProcessor myCommandProcessor = {};
repositoryManager myRepositoryManager = {};

int main(int argc, char* argv[]) {
	try {
		myRepositoryManager.selectAllFiles = true;

		while (true) {
			auto container = myCommandProcessor.process(myConsoleHandler.getCommand());

			switch (container.type) {
			case DRMSCommandType::DRMS_COMMAND_TYPE_REQUEST_FORM: {
				switch (container.subType) {
				case DRMSCommandSubType::DRMS_COMMAND_SUB_TYPE_CREATION_FORM:
					myRepositoryManager.creationRequest(creationForm(myConsoleHandler.getFormData(container)));
					break;
				case DRMSCommandSubType::DRMS_COMMAND_SUB_TYPE_UPDATION_FORM:
					myRepositoryManager.updationRequest(updationForm(myConsoleHandler.getFormData(container)));
					break;
				case DRMSCommandSubType::DRMS_COMMAND_SUB_TYPE_DELETION_FORM:
					myRepositoryManager.deletionRequest(deletionForm(myConsoleHandler.getFormData(container)));
					break;
				default:
					break;
				}
				break;
			}
			case DRMSCommandType::DRMS_COMMAND_TYPE_SUBMIT_FORM:
				break;
			case DRMSCommandType::DRMS_COMMAND_TYPE_RESOURCE_CHECK:
				break;
			case DRMSCommandType::DRMS_COMMAND_TYPE_REQUEST_CANCELATION:
				break;
			case DRMSCommandType::DRMS_COMMAND_TYPE_FOLDER_HIERARCHY:
				myRepositoryManager.showRepositoryFileHierarchy();
				break;
			case DRMSCommandType::DRMS_COMMAND_TYPE_VERIFICATION:
				break;
			case DRMSCommandType::DRMS_COMMAND_TYPE_PUSH:
				break;
			case DRMSCommandType::DRMS_COMMAND_TYPE_BUILD_SOLUTION:
				break;
			case DRMSCommandType::DRMS_COMMAND_TYPE_EXECUTE:
				break;
			case DRMSCommandType::DRMS_COMMAND_TYPE_REGISTER:
				break;
			case DRMSCommandType::DRMS_COMMAND_TYPE_ADD:
				myRepositoryManager.addRepository(myConsoleHandler.getRepositoryPath());
				break;
			case DRMSCommandType::DRMS_COMMAND_TYPE_UNKNOWN:
				break;
			default:
				break;
			}

			if (container.type == DRMSCommandType::DRMS_COMMAND_TYPE_END_SESSION)
				break;
		}
	}
	catch (std::exception & e) {
		std::cout << e.what() << "\n";
		return -1;
	}

	return 0;
}