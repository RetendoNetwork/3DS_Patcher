/**
 * @file acta.h
 * @brief Account Services (act:a)
 */
#pragma once
#include <3ds/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define ACT_CURRENT_SLOT_ID 0xFE

    typedef enum
    {
        ACT_COMMON_INFO_ACCOUNT_COUNT = 1,
        ACT_COMMON_INFO_CURRENT_SLOT_ID = 2,
        ACT_COMMON_INFO_DEFAULT_SLOT_ID = 3,
    } CommonInfoType;

    typedef enum
    {
        ACT_ACCOUNT_INFO_PERSISTENT_ID = 5,
        ACT_ACCOUNT_INFO_NNID = 11,
        ACT_ACCOUNT_INFO_PRINCIPAL_ID = 12,
        ACT_ACCOUNT_INFO_ASSIGNED_NNID = 21,
        ACT_ACCOUNT_INFO_MII_NAME = 27,
        ACT_ACCOUNT_INFO_ASSIGNED_PRINCIPAL_ID = 38,
        ACT_ACCOUNT_INFO_FRIEND_LOCAL_ACCOUNT_ID = 43,
    } AccountInfoType;

    /// Initializes ACTA service.
    Result actaInit();

    /// Exits ACTA.
    void actaExit();

    /// Get ACTA handle.
    Handle *actaGetSessionHandle();

    /**
     * @brief Initialize Account API with shared memory to use.
     * "Shared memory initialization is optional, but some service calls require it"
     * https://www.3dbrew.org/wiki/ACT:Initialize
     * @param sdk_ver SDK version
     * @param sharedmem Handle to the shared memory (see \ref svcCreateMemoryBlock)
     * @param sharedmem_size Shared memory size
     * @return Result
     */
    Result ACTA_Initialize(u32 sdk_ver, Handle sharedmem, u32 sharedmem_size);

    /**
     * @brief Returns the common information of the specified type
     * @param out_buffer Output buffer
     * @param buffer_size Output buffer size
     * @param info_type Type of information to get
     * @return Result
     */
    Result ACTA_GetCommonInfo(u8 *out_buffer, u32 buffer_size, CommonInfoType info_type);

    /**
     * @brief Returns the account information of the specified type
     * @param slot_id The account ID (slot ID)
     * @param out_buffer Output buffer
     * @param buffer_size Output buffer size
     * @param info_type Type of information to get
     * @return Result
     */
    Result ACTA_GetAccountInfo(u8 slot_id, u8 *out_buffer, u32 buffer_size, AccountInfoType info_type);

    /**
     * @brief Creates a local account (bound to the current friend/nasc account )
     * @return Result
     */
    Result ACTA_CreateLocalAccount();

    /**
     * @brief Deletes a local account
     * @param slot_id The account ID (slot ID)
     * @return Result
     */
    Result ACTA_DeleteLocalAccount(u8 slot_id);

    /**
     * @brief Unloads a local account
     * @param slot_id The account ID (slot ID)
     * @return Result
     */
    Result ACTA_UnloadLocalAccount(u8 slot_id);

    /**
     * @brief Commits a local account
     * @param slot_id The account ID (slot ID)
     * @return Result
     */
    Result ACTA_CommitLocalAccount(u8 slot_id);

    /**
     * @brief Sets the default account
     * @param slot_id The account ID (slot ID)
     * @return Result
     */
    Result ACTA_SetDefaultAccount(u8 slot_id);

    /**
     * @brief Saves the account data (? does many things like the WiiU "commit" equivalent)
     * @return Result
     */
    Result ACTA_Save();

#ifdef __cplusplus
}
#endif