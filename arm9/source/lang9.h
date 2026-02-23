/**
 * @file lang9.h
 * @brief Luma3DS UI runtime translation (ARM9 side)
 * 
 * @author Felix Homebrew
 *
 *   This file is part of Luma3DS
 *   Copyright (C) 2016-2020 Aurora Wright, TuxSH
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
 *       * Requiring preservation of specified reasonable legal notices or
 *         author attributions in that material or in the Appropriate Legal
 *         Notices displayed by works containing it.
 *       * Prohibiting misrepresentation of the origin of that material,
 *         or requiring that modified versions of such material be marked in
 *         reasonable ways as different from the original version.
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

    LLID_BOOTCFG_ERROR_OVERFLOW,
    LLID_BOOTCFG_ERROR_SAVE,
    LLID_BOOTCFG_ERROR_PINDEL,

    //----------------------------------------//

    LLID_CHAINLDR_TITLE,
    LLID_CHAINLDR_SUBTITLE,

    //----------------------------------------//

    LLID_BOOTPIN_COMMON_FORMAT,

    LLID_BOOTPIN_NEW_HINT,
    LLID_BOOTPIN_NEW_SKIP,
    LLID_BOOTPIN_NEW_RESET,
    LLID_BOOTPIN_NEW_ERROR,

    LLID_BOOTPIN_VERIFY_HINT,
    LLID_BOOTPIN_VERIFY_CLEAR,
    LLID_BOOTPIN_VERIFY_ERROR,

    //----------------------------------------//

    LLID_ERRGEN_TITLE,
    LLID_ERRGEN_FOOTER,

    LLID_ERRGEN_MISC_CRYPTO_ARM9DECRY,
    
    LLID_ERRGEN_MISC_FIRM_EXTFIRM,
    LLID_ERRGEN_MISC_FIRM_CERTKMC,
    LLID_ERRGEN_MISC_FIRM_FIRMDECRY,
    LLID_ERRGEN_MISC_FIRM_EXTFIRMINVCOR,
    LLID_ERRGEN_MISC_FIRM_CTRNANDLOAD,
    LLID_ERRGEN_MISC_FIRM_CTRNANDUNKN, LLID_ERRGEN_MISC_FIRM_CTRNANDUNKN_EXT, LLID_ERRGEN_MISC_FIRM_CTRNANDUNKN_CTRNAND,
    LLID_ERRGEN_MISC_FIRM_INVEMUNAND,
    LLID_ERRGEN_MISC_FIRM_SAFEMODE,
    LLID_ERRGEN_MISC_FIRM_INVPAYLOAD,
    LLID_ERRGEN_MISC_FIRM_FIRMMODTOOLARGE,
    LLID_ERRGEN_MISC_FIRM_FIRMMODLAYOUT,
    LLID_ERRGEN_MISC_FIRM_FIRMMODINVCOR,
    LLID_ERRGEN_MISC_FIRM_SYSMODULES,

    LLID_ERRGEN_MISC_FS_MKDIRLUMA,

    LLID_ERRGEN_MISC_MAIN_MCUFWWRONG,
    LLID_ERRGEN_MISC_MAIN_LOADERWRONG,
    LLID_ERRGEN_MISC_MAIN_MOUNTFAIL,
    LLID_ERRGEN_MISC_MAIN_MOUNTFAIL_SD,
    LLID_ERRGEN_MISC_MAIN_MOUNTFAIL_CTRNAND,
    LLID_ERRGEN_MISC_MAIN_MOUNTFAIL_BOTH,
    LLID_ERRGEN_MISC_MAIN_LAUNCHLCWRONG,
    LLID_ERRGEN_MISC_MAIN_SDLOCKED,
    LLID_ERRGEN_MISC_MAIN_FIRMPATCHES,

    LLID_ERRGEN_MISC_PATCHES_GETPROC9,
    LLID_ERRGEN_MISC_PATCHES_GETK11,

    //----------------------------------------//

    LLID_ERRFATAL_TITLE,

    LLID_ERRFATAL_ERRNAME_UNDEFINST,
    LLID_ERRFATAL_ERRNAME_PREFABORT,
    LLID_ERRFATAL_ERRNAME_DATAABORT,
    LLID_ERRFATAL_ERSNAME_KRNLPANIC,

    LLID_ERRFATAL_FIELD_PROCESSOR,
    LLID_ERRFATAL_FIELD_EXCTYPE,
    LLID_ERRFATAL_FIELD_FAULTSTATUS,
    LLID_ERRFATAL_FIELD_CURPROCESS,

    LLID_ERRFATAL_BFIELD_ACCESSTYPE,
    LLID_ERRFATAL_BFIELD_STACKDUMP,

    LLID_ERRFATAL_GWORD_CORE,
    LLID_ERRFATAL_GWORD_READ,
    LLID_ERRFATAL_GWORD_WRITE,

    LLID_ERRFATAL_INFO_ARM9MEMDUMP,
    LLID_ERRFATAL_INFO_INCORRDUMP,
    LLID_ERRFATAL_INFO_DUMPSAVE,
    LLID_ERRFATAL_INFO_DUMPIGNORE,
    LLID_ERRFATAL_INFO_DUMPRESYES,
    LLID_ERRFATAL_INFO_DUMPRESNO,
    LLID_ERRFATAL_INFO_GOODBYE,
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