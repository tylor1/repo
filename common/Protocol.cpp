
#include "StdAfx.h"
#include "Protocol.h"

IMPLEMENT_SERIAL(TPackFile, TNetPack,0)
IMPLEMENT_SERIAL(TPackCmd, TNetPack,0)
IMPLEMENT_SERIAL(TPackBuf, TNetPack,0)
IMPLEMENT_SERIAL(TPackScore, TNetPack,0)
IMPLEMENT_SERIAL(TPackList, TNetPack,0)
IMPLEMENT_SERIAL(TPackCheck, TNetPack,0)
IMPLEMENT_SERIAL(TNetPack, CObject,0)


