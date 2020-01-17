#include "drmsafx.h"
#include "resourceRequestForm.h"

namespace DRMS {
	ResourceRequestForm::ResourceRequestForm(DRMSResourceFormDataContainer& container) {
		setDeveloperID(container.developerID);
		setDeveloperName(container.developerName);
		setRequestDate(container.requestDate);
		setFileName(container.fileName);
		setReason(container.reason);
		setETR(container.ETR);
	}

	void ResourceRequestForm::setDeveloperID(std::string_view id) {
		myDeveloperID = id;
	}

	void ResourceRequestForm::setDeveloperName(std::string_view name) {
		myDeveloperName = name;
	}

	void ResourceRequestForm::setRequestDate(std::string_view date) {
		myRequestDate = date;
	}

	void ResourceRequestForm::setFileName(std::string_view name) {
		myFileName = name;
	}

	void ResourceRequestForm::setReason(std::string_view reason) {
		myReason = reason;
	}

	void ResourceRequestForm::setETR(std::string_view etr) {
		myETR = etr;
	}
}
