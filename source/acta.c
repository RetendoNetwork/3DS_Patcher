#include <string.h>
#include <3ds/types.h>
#include <3ds/svc.h>
#include <3ds/synchronization.h>
#include <3ds/ipc.h>
#include <3ds/result.h>
#include <3ds/srv.h>

#include "acta.h"

static Handle actaHandle;
static int actaRefCount;

Result actaInit(void)
{
    Result ret = 0;

    if (AtomicPostIncrement(&actaRefCount))
        return 0;

    ret = srvGetServiceHandle(&actaHandle, "act:a");
    if (R_FAILED(ret))
        AtomicDecrement(&actaRefCount);

    return ret;
}

void actaExit(void)
{
    if (AtomicDecrement(&actaRefCount))
        return;
    svcCloseHandle(actaHandle);
}

Handle *actaGetSessionHandle(void)
{
    return &actaHandle;
}

Result ACTA_Initialize(u32 sdk_ver, Handle sharedmem, u32 sharedmem_size)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x1, 2, 4);
    cmdbuf[1] = sdk_ver;
    cmdbuf[2] = sharedmem_size;
    cmdbuf[3] = IPC_Desc_CurProcessId();
    cmdbuf[4] = IPC_Desc_CurProcessHandle();
    cmdbuf[5] = IPC_Desc_SharedHandles(1);
    cmdbuf[6] = sharedmem;

    if (R_FAILED(ret = svcSendSyncRequest(actaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}

Result ACTA_GetCommonInfo(u8 *out_buffer, u32 buffer_size, CommonInfoType info_type)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x5, 2, 2);
    cmdbuf[1] = buffer_size;
    cmdbuf[2] = info_type;
    cmdbuf[3] = (buffer_size << 4) | 12;
    cmdbuf[4] = (u32)out_buffer;

    if (R_FAILED(ret = svcSendSyncRequest(actaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}

Result ACTA_GetAccountInfo(u8 slot_id, u8 *out_buffer, u32 buffer_size, AccountInfoType info_type)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x6, 3, 2);
    cmdbuf[1] = slot_id;
    cmdbuf[2] = buffer_size;
    cmdbuf[3] = info_type;
    cmdbuf[4] = (buffer_size << 4) | 12;
    cmdbuf[5] = (u32)out_buffer;

    if (R_FAILED(ret = svcSendSyncRequest(actaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}

Result ACTA_CreateLocalAccount()
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x402, 0, 0);

    if (R_FAILED(ret = svcSendSyncRequest(actaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}

Result ACTA_DeleteLocalAccount(u8 slot_id)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x405, 1, 0);
    cmdbuf[1] = slot_id;

    if (R_FAILED(ret = svcSendSyncRequest(actaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}

Result ACTA_UnloadLocalAccount(u8 slot_id)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x407, 1, 0);
    cmdbuf[1] = slot_id;

    if (R_FAILED(ret = svcSendSyncRequest(actaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}

Result ACTA_CommitLocalAccount(u8 slot_id)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x403, 1, 0);
    cmdbuf[1] = slot_id;

    if (R_FAILED(ret = svcSendSyncRequest(actaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}

Result ACTA_SetDefaultAccount(u8 slot_id)
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x409, 1, 0);
    cmdbuf[1] = slot_id;

    if (R_FAILED(ret = svcSendSyncRequest(actaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}

Result ACTA_Save()
{
    Result ret = 0;
    u32 *cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x10, 0, 0);

    if (R_FAILED(ret = svcSendSyncRequest(actaHandle)))
        return ret;

    return (Result)cmdbuf[1];
}