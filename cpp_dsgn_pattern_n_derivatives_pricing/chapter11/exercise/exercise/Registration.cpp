#include <PayOffConstructible.h>
#include "PayOffConstructibleCRTP.h"
#include "PayOffConstructibleMono.h"

namespace BookExample
{
	PayOffHelper<PayOffCall> RegisterCall("call");

	PayOffHelper<PayOffPut> RegisterPut("put");

	PayOffHelper<PayOffStraddle> RegisterStraddle("straddle");

	PayOffHelper<PayOffDoubleDigital> RegisterDoubleDigital("double digital");

}

namespace CRTP
{
	PayOffHelperCRTP<PayOffCall> RegisterCall("call");

	PayOffHelperCRTP<PayOffPut> RegisterPut("put");

	PayOffHelperCRTP<PayOffStraddle> RegisterStraddle("straddle");

	PayOffHelperCRTP<PayOffDoubleDigital> RegisterDoubleDigital("double digital");

}

namespace Monostate
{
	PayOffHelperMono<PayOffCall> RegisterCall("call");

	PayOffHelperMono<PayOffPut> RegisterPut("put");

	PayOffHelperMono<PayOffStraddle> RegisterStraddle("straddle");

	PayOffHelperMono<PayOffDoubleDigital> RegisterDoubleDigital("double digital");

}