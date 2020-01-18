#include "drmsafx.h"
#include "updationForm.h"

namespace DRMS {
	updationForm::updationForm(DRMSResourceFormDataContainer container) : ResourceRequestForm(container) {
		myDestination = container.destination;
	}
}
