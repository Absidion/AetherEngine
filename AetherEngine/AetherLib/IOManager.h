#pragma once

#include <vector>

namespace Aether
{
	class IOManager
	{
	public:

		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);

	};
}

