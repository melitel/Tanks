#pragma once
#include <string>
#include <windows.h>
#include <string>
#include "ExportMacro.h"

class EXPORT_TANKS FileManager
{
public:
	static std::string GetExecutablePath();
	static std::string GetImagePath(const std::string& imageName);

};

