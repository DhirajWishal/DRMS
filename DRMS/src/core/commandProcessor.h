#pragma once

#ifndef _DRMS_COMMAND_PROCESSOR_H
#define _DRMS_COMMAND_PROCESSOR_H

#include <string>
#include <vector>

#include "data store/structures.h"

namespace DRMS {
	class commandProcessor {
	public:
		commandProcessor();
		~commandProcessor();

		DRMSCommandContainer process(std::string_view command);

	private:
		DRMSCommandContainer _secondaryCheck(std::vector<std::string> commands,
			DRMSCommandContainer container, uint32_t indexOffset = 0);

		bool _commandCheck(uint32_t count, DRMSCommandType type);

		const std::vector<std::string_view> myPrimaryCommandTypes = {
			"terminate",
			"request",
			"submit",
			"rescheck",
			"reqcancel",
			"fh",
			"verification",
			"push",
			"bs",
			"execute",
			"register",
			"add"
		};
		const std::vector<std::string_view> mySecondaryCommandTypes = {
			"creation",
			"updation",
			"deletion",
			"crch",
			"avch",
			"dech",
			"repository"
		};
		const std::vector<std::string_view> myTernaryCommandTypes = {};

		std::vector<std::string> myCommands = {};
	};
}

#endif
