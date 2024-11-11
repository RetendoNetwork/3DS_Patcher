/**
 * @file frda.h
 * @brief Friend Services (frd:a)
 */
#pragma once
#include <3ds/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include <3ds/services/frd.h>

    /// Enum to use with FRD account management functions
    typedef enum
    {
        NAS_LIVE = 0, ///< https://nasc.nintendowifi.net/ac
        NAS_TEST,     ///< https://nasc.test.nintendowifi.net/ac
        NAS_DEV,      ///< https://nasc.dev.nintendowifi.net/ac
        NAS_UNKNOWN   ///< Empty URL
    } NASType;

    /// Enum to use with FRD account management functions (value)
    typedef enum
    {
        NAS_ENV_L = 0, ///< Live (production)
        NAS_ENV_C,     ///< C
        NAS_ENV_S,     ///< Staging
        NAS_ENV_D,     ///< Devlopment
        NAS_ENV_I,     ///< Internal
        NAS_ENV_T,     ///< Test
        NAS_ENV_J,     ///< J
        NAS_ENV_X,     ///< X
        NAS_ENV_U,     ///< Unknown
    } NASEnvironment;

    /// Initializes FRDA service.
    Result frdaInit();

    /// Exits FRDA.
    void frdaExit();

    /// Get FRDA handle.
    Handle *frdaGetSessionHandle();

    /**
     * @brief Get the current local account ID
     * @param outAccountId Pointer to the output Account ID
     */
    Result FRDA_GetMyLocalAccountId(u8 *outAccountId);

    /**
     * @brief Gets the current user's friend key.
     * @param key Pointer to write the current user's friend key to.
     */
    Result FRDA_GetMyFriendKey(FriendKey *key);

    /**
     * @brief Sets the Friend API to use a specific SDK version.
     * @param sdkVer The SDK version needed to be used.
     */
    Result FRDA_SetClientSdkVersion(u32 sdkVer);

    /**
     * @brief Get the server types of the current local account
     * @param outType Pointer to the output NAS server type (prod/test/dev)
     * @param outEnv Pointer to the output NAS environement (L, C, D, S, T, etc...)
     * @param outEnvNum Pointer to the output NAS environment number ([1-9])
     */
    Result FRDA_GetServerTypes(NASType *outType, NASEnvironment *outEnv, u8 *outEnvNum);

    /**
     * @brief Creates a local account with the specified settings
     * @param accountId Account ID
     * @param nasType NAS server to connect to
     * @param nasEnv "servertype" first character in NASC requests, the specified environment for the user
     * @param nasEnvNumber "servertyp" second character in NASC request, The number of the environment (must be between [1-9])
     */
    Result FRDA_CreateLocalAccount(u8 accountId, NASType nasType, NASEnvironment nasEnv, u8 nasEnvNumber);

    /**
     * @brief Deletes a local account by ID (doesn't seem to really work, but it breaks the account and makes it unloadable...)
     * @param accountId Account ID
     */
    Result FRDA_DeleteLocalAccount(u8 accountId);

    /**
     * @brief Loads a local account (specified by ID) as the current account
     * @param accountId Account ID
     */
    Result FRDA_LoadLocalAccount(u8 accountId);

    /**
     * @brief Unload the current local account (specified by ID)
     * @param accountId Account ID
     */
    Result FRDA_UnloadLocalAccount();

    /**
     * @brief Saves the current local account to filesystem
     */
    Result FRDA_Save();

#ifdef __cplusplus
}
#endif