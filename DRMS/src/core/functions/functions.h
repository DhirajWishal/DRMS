#pragma once

#ifndef _DRMS_FUNCTIONS_H
#define _DRMS_FUNCTIONS_H

#include <string>
#include <vector>

namespace DRMS {
	std::vector<std::string> splitLine(std::string_view line, char splitBy);
}
#endif // !_DRMS_FUNCTIONS_H

