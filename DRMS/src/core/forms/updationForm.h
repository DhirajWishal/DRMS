#pragma once

#ifndef _DRMS_UPDATION_FORM_H
#define _DRMS_UPDATION_FORM_H

#include "resourceRequestForm.h"

namespace DRMS {
	class updationForm : public ResourceRequestForm {
	public:
		updationForm(DRMSResourceFormDataContainer container);
		~updationForm() {}

		std::string myDestination = "";
	};
}

#endif
