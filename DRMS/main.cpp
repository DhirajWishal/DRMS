#include "drmsafx.h"
#include "src/DRMS.h"
using namespace DRMS;

consoleHandler myCosoleHandler = {};
commandProcessor myCommandProcessor = {};

int main(int argc, char* argv[]) {
	try {
		while (true) {
			auto command = myCosoleHandler.getCommand();
			auto container = myCommandProcessor.process(command);

			auto test = myCosoleHandler.getFormData(container);

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