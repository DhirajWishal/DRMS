#include "drmsafx.h"
#include "repositoryManager.h"
#include "utils/timer.h"
#include "functions/functions.h"

namespace DRMS {
	repositoryManager::~repositoryManager() {
	}

	void repositoryManager::addRepository(std::string_view path, DRMSProjectType projectType) {
		myPath = path;
		myProjectType = projectType;

		printf("Loading files from '%s' directory...\n", myPath.c_str());
		Timer myTimer = {};

		std::filesystem::create_directories(myPath);
		std::string _localFileName = "";
		std::string _localFilePath = "";
		for (auto& p : std::filesystem::recursive_directory_iterator(myPath)) {
			_localFileName = p.path().filename().string();
			_localFilePath = p.path().string();
			if (_isLockableFile(_localFileName) && !selectAllFiles) {

				myFiles.push_back(std::fstream(_localFilePath));
				myFilePaths.push_back(_localFilePath);
				myFileNames.push_back(_localFileName);
				isFileLocked.push_back(false);

				if (_localFileName.size() > 9)
					if (_localFileName.substr(_localFileName.size() - std::string(".vcxproj").size(),
						std::string(".vcxproj").size()).find(".vcxproj") != std::string::npos)
						myProjectPaths.push_back(_localFilePath);
			}
			else if (selectAllFiles) {
				myFiles.push_back(std::fstream(_localFilePath));
				myFilePaths.push_back(_localFilePath);
				myFileNames.push_back(_localFileName);
				isFileLocked.push_back(false);

				if (_localFileName.size() > 9)
					if (_localFileName.substr(_localFileName.size() - std::string(".vcxproj").size(), std::string(".vcxproj").size()).find(".vcxproj") != std::string::npos)
						myProjectPaths.push_back(_localFilePath);
			}
		}

		printf("Loaded %d files from '%s' directory in %fms.\n", myFiles.size(), myPath.c_str(), myTimer.end());
	}

	void repositoryManager::creationRequest(creationForm form) {
		if (_getFileIndex(form.myFileName))
			printf("%s file already exists.\n", form.myFileName);
		else
			printf("Creation request Accepted!\n");
	}

	void repositoryManager::updationRequest(updationForm form) {
		std::string_view _fileName = form.myFileName;
		std::string_view _separator;
		std::vector<std::string> _subPaths = {};
		if (_fileName.find("/") == std::string::npos) {
			_subPaths = splitLine(_fileName, '/');
			_separator = "/";
		}
		else if (_fileName.find("\\") == std::string::npos) {
			_subPaths = splitLine(_fileName, '\\');
			_separator = "\\";
		}

		_fileName = _subPaths[_subPaths.size() - 1];

		uint32_t _index = _getFileIndex(_fileName);

		if (!isFileLocked[_index]) {
			myFiles[_index].close();
			isFileLocked[_index] = true;
			std::filesystem::copy((const std::filesystem::path)myFilePaths[_index],
				(form.myDestination + _separator.data() + _fileName.data()));
		}
		else
			printf("Request file of '%s' is already in use.\n", _fileName.data());
	}

	void repositoryManager::deletionRequest(deletionForm form) {
		std::string_view _fileName = form.myFileName;
		uint32_t _index = _getFileIndex(_fileName);

		if ((_fileName.find(":/") != std::string::npos
			|| _fileName.find(":\\") != std::string::npos)
			&& !isFileLocked[_index] && false /* TODO: Verification */) {
			if (!remove(myFilePaths[_index].c_str()))
				printf("%s file successfully deleted.\n", _fileName.data());
			else
				printf("Error deleting %s file.\n", _fileName.data());
		}
		else
			printf("%s file is not allowed to be deleted.\n", _fileName.data());
	}

	void repositoryManager::showRepositoryFileHierarchy() {
		uint32_t _filesSize = myFilePaths.size();
		if (!_filesSize) {
			printf("No files to show!\n");
			return;
		}

		uint32_t _index = 0;
		while (++_index < _filesSize)
			printf("%s\n", myFilePaths[_index].c_str());
	}

	bool repositoryManager::_isLockableFile(std::string_view path) {
		uint32_t _pathSize = path.size();

		for (std::string_view itr : defaultProjectFiles)
			if (itr.size() < _pathSize)
				if (path.substr(_pathSize - itr.size(), itr.size()).find(itr) != std::string::npos)
					return true;

		if (myProjectType == DRMSProjectType::DRMS_PROJECT_TYPE_CPP)
			for (std::string_view itr : projectCppFiles)
				if (itr.size() < _pathSize)
					if (path.substr(_pathSize - itr.size(), itr.size()).find(itr) != std::string::npos)
						return true;

		return false;
	}

	uint32_t repositoryManager::_getFileIndex(std::string_view fileName) {
		std::string_view _path;

		for (uint32_t itr = 0; itr < myFilePaths.size(); itr++) {
			_path = myFilePaths[itr];

			if (_path.substr(_path.size() - fileName.size(), fileName.size()).find(fileName) != std::string::npos)
				return itr;
		}
	}
}