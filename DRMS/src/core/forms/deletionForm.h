#pragma once

#ifndef _DRMS_DELETION_FORM_H
#define _DRMS_DELETION_FORM_H

#include "resourceRequestForm.h"

namespace DRMS {
	class deletionForm : public ResourceRequestForm {
	public:
		deletionForm(DRMSResourceFormDataContainer container) : ResourceRequestForm(container) {}
		~deletionForm() {}
	};
}

#endif // !_DRMS_DELETION_FORM_H

