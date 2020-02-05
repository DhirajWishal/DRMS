#pragma once

#ifndef _DRMS_REPOSITORY_MANAGER_H
#define _DRMS_REPOSITORY_MANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include "data store/enumerations.h"
#include "forms/creationForm.h"
#include "forms/updationForm.h"
#include "forms/deletionForm.h"

namespace DRMS {
	class repositoryManager {
	public:
		repositoryManager() {}
		~repositoryManager();

		void addRepository(std::string_view path, DRMSProjectType projectType = DRMSProjectType::DRMS_PROJECT_TYPE_CPP);

		bool selectAllFiles = false;

		void creationRequest(creationForm form);
		void updationRequest(updationForm form);
		void deletionRequest(deletionForm form);

		void showRepositoryFileHierarchy();

	private:
		bool _isLockableFile(std::string_view path);
		uint32_t _getFileIndex(std::string_view fileName);

		std::string myPath = "";
		std::vector<std::string> myProjectPaths = {};
		std::vector<std::string> myFilePaths = {};
		std::vector<std::string> myFileNames = {};
		std::vector<bool> isFileLocked = {};
		std::vector<std::fstream> myFiles = {};
		DRMSProjectType myProjectType = DRMSProjectType::DRMS_PROJECT_TYPE_CPP;

		std::vector<std::string_view> defaultProjectFiles = {
			".sln", ".vcxproj", ".vcxproj.filters", "vcxproj.user",
			".lua", ".md", ".txt"
		};
		std::vector<std::string_view> projectCppFiles = {
			".c", ".cpp", ".cxx",
			".h"
		};
	};
}

#endif // !_DRMS_FILE_HANDLER_H
