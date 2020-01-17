#include "drmsafx.h"
#include "functions.h"

namespace DRMS {
	// var = utils::splitLine(line, character);
	std::vector<std::string> splitLine(std::string_view line, char splitBy)
	{
		std::vector<std::string> _splits = {};
		if (line.find(splitBy) != std::string::npos)
		{
			std::string _split = "";
			uint32_t _lineSize = line.size();
			uint32_t _index = 0;

			while (_index < _lineSize)
			{
				if ((line[_index] == splitBy))
				{
					_splits.push_back(_split);
					_split.clear();
					_index++;
					continue;
				}
				if (_index == (_lineSize - 1))
				{
					_split.push_back(line[_index]);
					_splits.push_back(_split);
					_index++;
					break;
				}

				_split.push_back(line[_index]);
				_index++;
			}

			return _splits;
		}
		else if (line.size())
			return { line.data() };

		return std::vector<std::string>();
	}
}