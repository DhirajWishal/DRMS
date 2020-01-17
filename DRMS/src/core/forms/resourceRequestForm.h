#pragma once

#ifndef _DRMS_RESOURCE_REQUEST_FORM_H
#define _DRMS_RESOURCE_REQUEST_FORM_H

#include <string>
#include "core/data store/structures.h"

namespace DRMS {
	class ResourceRequestForm {
	public:
		ResourceRequestForm(DRMSResourceFormDataContainer& container);
		virtual ~ResourceRequestForm() {}

		void setDeveloperID(std::string_view id);
		void setDeveloperName(std::string_view name);
		void setRequestDate(std::string_view date);
		void setFileName(std::string_view name);
		void setReason(std::string_view reason);
		void setETR(std::string_view etr);

	protected:
		std::string myDeveloperID = "";
		std::string myDeveloperName = "";
		std::string myRequestDate = "";
		std::string myFileName = "";
		std::string myReason = "";
		std::string myETR = "";	// Estimated Time of Return
	};
}

#endif // !_DRMS_RESOURCE_REQUEST_FORM_H

