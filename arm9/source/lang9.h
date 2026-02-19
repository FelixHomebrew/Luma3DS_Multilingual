/**
 * Luma3DS runtime translation system
 * @author Felix Homebrew
 */
#pragma once
#include "types.h"

#define debugShow(F,...) { clearScreens(false); clearScreens(true); drawFormattedString(true, 0, 0, COLOR_GREEN, F, __VA_ARGS__); waitInput(false); }

typedef enum {
    LLID_PRETTY, // Pretty language name

    //----------------------------------------//

    LLID_BOOTCFG_TITLE,
    LLID_BOOTCFG_SUBTITLE,
    LLID_BOOTCFG_BOOTINFO,

    LLID_BOOTCFG_OPT_DEFEMUNAND_NAME,
    LLID_BOOTCFG_OPT_BRIGHT_NAME,
    LLID_BOOTCFG_OPT_SPLASH_NAME,
    LLID_BOOTCFG_OPT_PINLOCK_NAME,
    LLID_BOOTCFG_OPT_NEWCPU_NAME,
    LLID_BOOTCFG_OPT_HBMAUTOBOOT_NAME,
    LLID_BOOTCFG_OPT_LANGUAGE_NAME,
    LLID_BOOTCFG_OPT_EMUNAUTOBOOT_NAME,
    LLID_BOOTCFG_OPT_EXTFIRMSMOD_NAME,
    LLID_BOOTCFG_OPT_PATCHING_NAME,
    LLID_BOOTCFG_OPT_THREADREDIRECT_NAME,
    LLID_BOOTCFG_OPT_NANDUSRSTR_NAME,
    LLID_BOOTCFG_OPT_GBASPLASH_NAME,

    LLID_BOOTCFG_OPT_BOOTCHAINLDR_NAME,
    LLID_BOOTCFG_OPT_SAVEEXIT_NAME,

    LLID_BOOTCFG_OPT_DEFEMUNAND_ABOUT,
    LLID_BOOTCFG_OPT_BRIGHT_ABOUT,
    LLID_BOOTCFG_OPT_SPLASH_ABOUT,
    LLID_BOOTCFG_OPT_PINLOCK_ABOUT,
    LLID_BOOTCFG_OPT_NEWCPU_ABOUT,
    LLID_BOOTCFG_OPT_HBMAUTOBOOT_ABOUT,
    LLID_BOOTCFG_OPT_LANGUAGE_ABOUT,
    LLID_BOOTCFG_OPT_EMUNAUTOBOOT_ABOUT,
    LLID_BOOTCFG_OPT_EXTFIRMSMOD_ABOUT,
    LLID_BOOTCFG_OPT_PATCHING_ABOUT,
    LLID_BOOTCFG_OPT_THREADREDIRECT_ABOUT,
    LLID_BOOTCFG_OPT_NANDUSRSTR_ABOUT,
    LLID_BOOTCFG_OPT_GBASPLASH_ABOUT,

    LLID_BOOTCFG_OPT_BOOTCHAINLDR_ABOUT,
    LLID_BOOTCFG_OPT_SAVEEXIT_ABOUT,

    //----------------------------------------//

    LLID_CHAINLDR_TITLE,
    LLID_CHAINLDR_SUBTITLE,

    //----------------------------------------//

    LLID_ERRFATAL_TITLE,

    LLID_ERRFATAL_ERRNAME_FIQ,
    LLID_ERRFATAL_ERRNAME_UNDEFINST,
    LLID_ERRFATAL_ERRNAME_PREFABORT,
    LLID_ERRFATAL_ERRNAME_DATAABORT,
    LLID_ERRFATAL_ERSNAME_KRNLPANIC,

    LLID_ERRFATAL_FIELD_PROC,
    LLID_ERRFATAL_FIELD_CORE
} LumaLocaleId;

extern const Iso6391 lumaTranslBuiltinI;

void lumaTranslLoad(const Iso6391 lang);

/**
 * @return Translated string
 */
const char* lumaTranslGet(const LumaLocaleId l2id);

/**
 * @return Avaiable languages count
 */
u8 lumaTranslCount();

/**
 * Lists avaiable languages alphabetically by their ISO639-1 code
 * @param out Address where output language codes to
 * @param max Max number of language codes to list
 */
void lumaTranslList(Iso6391* out, u8 max);

/**
 * @return `lang.ini` exists
 */
bool lumaTranslHas(const Iso6391 lang);