#pragma once

#ifndef _DRMS_CREATION_FORM_H
#define _DRMS_CREATION_FORM_H

#include "resourceRequestForm.h"

namespace DRMS {
	class creationForm : public ResourceRequestForm {
	public:
		creationForm(DRMSResourceFormDataContainer container) : ResourceRequestForm(container) {}
		~creationForm() {}
	};
}

#endif // !_DRMS_CREATION_FORM_H

