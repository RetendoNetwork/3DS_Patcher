#include <string.h>
#include <3ds/types.h>
#include <3ds/svc.h>
#include <3ds/synchronization.h>
#include <3ds/ipc.h>
#include <3ds/result.h>
#include <3ds/srv.h>

#include "frda.h"

static Handle frdaHandle;
static int frdaRefCount;

Result frdaInit(void)
{
    Result ret = 0;

    if (AtomicPostIncrement(&frdaRefCount))
        return 0;

    ret = srvGetServiceHandle(&frdaHandle, "frd:a");
    if (R_FAILED(ret))
        AtomicDecrement(&frdaRefCount);

    return ret;
}

void frdaExit(void)
{
    if (AtomicDecrement(&frdaRefCount))
        return;
    svcCloseHandle(frdaHandle);
}

Handle *frdaGetSessionHandle(void)
{
    return &frdaHandle;
}

Result FRDA_GetMyLocalAccountId(u8 *outAccountId)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();
    cmdbuf[0] = IPC_MakeHeader(0xB, 0, 0);

    if (R_FAILED(ret = svcSendSyncRequest(frdaHandle)))
        return ret;

    *outAccountId = (u8)cmdbuf[2];

    return (Result)cmdbuf[1];
}

Result FRDA_GetMyFriendKey(FriendKey *key)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x5, 0, 0);

    if (R_FAILED(ret = svcSendSyncRequest(frdaHandle)))
        return ret;

    memcpy(key, &cmdbuf[2], sizeof(FriendKey));

    return (Result)cmdbuf[1];
}

Result FRDA_SetClientSdkVersion(u32 sdkVer)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x32, 1, 2);
    cmdbuf[1] = sdkVer;
    cmdbuf[2] = IPC_Desc_CurProcessId();

    if (R_FAILED(ret = svcSendSyncRequest(frdaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}

Result FRDA_GetServerTypes(NASType *outType, NASEnvironment *outEnv, u8 *outEnvNum)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();
    cmdbuf[0] = IPC_MakeHeader(0x30, 0, 0);

    if (R_FAILED(ret = svcSendSyncRequest(frdaHandle)))
        return ret;

    *outType = (NASType)cmdbuf[2];
    *outEnv = (NASEnvironment)cmdbuf[3];
    *outEnvNum = (u8)cmdbuf[4];

    return (Result)cmdbuf[1];
}

Result FRDA_CreateLocalAccount(u8 accountId, NASType nasType, NASEnvironment nasEnv, u8 nasEnvNumber)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x401, 4, 0);
    cmdbuf[1] = accountId;
    cmdbuf[2] = (u8)nasType;
    cmdbuf[3] = nasEnv;
    cmdbuf[4] = (u8)nasEnvNumber;

    if (R_FAILED(ret = svcSendSyncRequest(frdaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}

Result FRDA_DeleteLocalAccount(u8 accountId)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x402, 1, 0);
    cmdbuf[1] = accountId;

    if (R_FAILED(ret = svcSendSyncRequest(frdaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}

Result FRDA_LoadLocalAccount(u8 accountId)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x403, 1, 0);
    cmdbuf[1] = accountId;

    if (R_FAILED(ret = svcSendSyncRequest(frdaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}

Result FRDA_UnloadLocalAccount()
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x404, 0, 0);

    if (R_FAILED(ret = svcSendSyncRequest(frdaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}

Result FRDA_Save()
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x405, 0, 0);

    if (R_FAILED(ret = svcSendSyncRequest(frdaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}