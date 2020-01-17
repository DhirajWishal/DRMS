#pragma once

#ifndef _DRMS_STRUCTURES_H
#define _DRMS_STRUCTURES_H

#include <string>
#include "enumerations.h"

namespace DRMS {
	struct DRMSCommandContainer {
		DRMSCommandType type = DRMSCommandType::DRMS_COMMAND_TYPE_UNKNOWN;
		DRMSCommandSubType subType = DRMSCommandSubType::DRMS_COMMAND_SUB_TYPE_UNKNOWN;
	};

	struct DRMSResourceFormDataContainer {
		std::string developerID = "";
		std::string developerName = "";
		std::string requestDate = "";
		std::string fileName = "";
		std::string reason = "";
		std::string ETR = "";
	};
}

#endif // !_DRMS_STRUCTURES_H

