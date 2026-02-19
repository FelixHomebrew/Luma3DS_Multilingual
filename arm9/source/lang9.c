/**
 * @file lang9.c
 * Luma3DS UI runtime translation (ARM9 side)
 * 
 * @author Felix Homebrew
 */
#include "lang9.h"

#include "config.h"
#include "ini.h"
#include "fatfs/ff.h"
#include "fs.h"
#include "stdarg.h"
#include "string.h"

#define STRCOUNT (sizeof(llidTable)/sizeof(llidTable[0]))
#define MAX_INILANG_SIZE 4096

#define LANGS_DIR "langs"

#include "draw.h"
#include "screen.h"
#include "utils.h"

static const char* llidTable[] = {
    "PRETTY",

    //----------------------------------------//

    "BOOTCFG_TITLE",
    "BOOTCFG_SUBTITLE",
    "BOOTCFG_BOOTINFO",
    
    "BOOTCFG_OPT_DEFEMUNAND_NAME",
    "BOOTCFG_OPT_BRIGHT_NAME",
    "BOOTCFG_OPT_SPLASH_NAME",
    "BOOTCFG_OPT_PINLOCK_NAME",
    "BOOTCFG_OPT_NEWCPU_NAME",
    "BOOTCFG_OPT_HBMAUTOBOOT_NAME",
    "BOOTCFG_OPT_LANGUAGE_NAME",
    "BOOTCFG_OPT_EMUNAUTOBOOT_NAME",
    "BOOTCFG_OPT_EXTFIRMSMOD_NAME",
    "BOOTCFG_OPT_PATCHING_NAME",
    "BOOTCFG_OPT_THREADREDIRECT_NAME",
    "BOOTCFG_OPT_NANDUSRSTR_NAME",
    "BOOTCFG_OPT_GBASPLASH_NAME",

    "BOOTCFG_OPT_BOOTCHAINLDR_NAME",
    "BOOTCFG_OPT_SAVEEXIT_NAME",

    "BOOTCFG_OPT_DEFEMUNAND_ABOUT",
    "BOOTCFG_OPT_BRIGHT_ABOUT",
    "BOOTCFG_OPT_SPLASH_ABOUT",
    "BOOTCFG_OPT_PINLOCK_ABOUT",
    "BOOTCFG_OPT_NEWCPU_ABOUT",
    "BOOTCFG_OPT_HBMAUTOBOOT_ABOUT",
    "BOOTCFG_OPT_LANGUAGE_ABOUT",
    "BOOTCFG_OPT_EMUNAUTOBOOT_ABOUT",
    "BOOTCFG_OPT_EXTFIRMSMOD_ABOUT",
    "BOOTCFG_OPT_PATCHING_ABOUT",
    "BOOTCFG_OPT_THREADREDIRECT_ABOUT",
    "BOOTCFG_OPT_NANDUSRSTR_ABOUT",
    "BOOTCFG_OPT_GBASPLASH_ABOUT",

    "BOOTCFG_OPT_BOOTCHAINLDR_ABOUT",
    "BOOTCFG_OPT_SAVEEXIT_ABOUT",

    //----------------------------------------//

    "CHAINLDR_TITLE",
    "CHAINLDR_SUBTITLE",

    //----------------------------------------//

    "BOOTPIN_COMMON_FORMAT",

    "BOOTPIN_NEW_HINT",
    "BOOTPIN_NEW_SKIP",
    "BOOTPIN_NEW_RESET",
    "BOOTPIN_NEW_ERROR",

    "BOOTPIN_VERIFY_HINT",
    "BOOTPIN_VERIFY_CLEAR",
    "BOOTPIN_VERIFY_ERROR",

    //----------------------------------------//

    "ERRFATAL_TITLE",

    "ERRFATAL_ERRNAME_UNDEFINST",
    "ERRFATAL_ERRNAME_PREFABORT",
    "ERRFATAL_ERRNAME_DATAABORT",
    "ERRFATAL_ERSNAME_KRNLPANIC",

    "ERRFATAL_FIELD_PROCESSOR",
    "ERRFATAL_FIELD_EXCTYPE",
    "ERRFATAL_FIELD_FAULTSTATUS",
    "ERRFATAL_FIELD_CURPROCESS",

    "ERRFATAL_BFIELD_ACCESSTYPE",
    "ERRFATAL_BFIELD_STACKDUMP",

    "ERRFATAL_GWORD_CORE",
    "ERRFATAL_GWORD_READ",
    "ERRFATAL_GWORD_WRITE",

    "ERRFATAL_INFO_ARM9MEMDUMP",
    "ERRFATAL_INFO_INCORRDUMP",
    "ERRFATAL_INFO_DUMPSAVE",
    "ERRFATAL_INFO_DUMPIGNORE",
    "ERRFATAL_INFO_DUMPRESYES",
    "ERRFATAL_INFO_DUMPRESNO",
    "ERRFATAL_INFO_GOODBYE",
};
//^([A-Z9_]+)=.*$
// Built-in language (english by default)
const Iso6391 lumaTranslBuiltinI = "en";
static char* lumaTranslBuiltinV[] = {
    "English",

    //----------------------------------------//

    "%s configuration",
    "Use the DPAD and A to change settings",
    "Booted from %s via %s",

    "Default EmuNAND: 1( ) 2( ) 3( ) 4( )",
    "Screen brightness: 4( ) 3( ) 2( ) 1( )",
    "Splash: Off( ) Before( ) After( ) payloads",
    "PIN lock: Off( ) 4( ) 6( ) 8( ) digits",
    "New 3DS CPU: Off( ) Clock( ) L2( ) Clock+L2( )",
    "Hbmenu autoboot: Off( ) 3DS( ) DSi( )",
    "Language: <%s>",
    "( ) Autoboot EmuNAND",
    "( ) Enable loading external FIRMs and modules",
    "( ) Enable game patching",
    "( ) Redirect app. syscore threads to core2",
    "( ) Show NAND or user string in System Settings",
    "( ) Show GBA boot screen in patched AGB_FIRM",

    "\nBoot chainloader",
    "Save and exit",

    "Select the default EmuNAND.\n\n"
    "It will be booted when no directional\n"
    "pad buttons are pressed (Up/Right/Down\n"
    "/Left equal EmuNANDs 1/2/3/4).",

    "Select the screen brightness.",

    "Enable splash screen support.\n\n"
    "\t* 'Before payloads' displays it\n"
    "before booting payloads\n"
    "(intended for splashes that display\n"
    "button hints).\n\n"
    "\t* 'After payloads' displays it\n"
    "afterwards.\n\n"
    "Edit the duration in config.ini (3s\n"
    "default).",

    "Activate a PIN lock.\n\n"
    "The PIN will be asked each time\n"
    "Luma3DS boots.\n\n"
    "4, 6 or 8 digits can be selected.\n\n"
    "The ABXY buttons and the directional\n"
    "pad buttons can be used as keys.\n\n"
    "A message can also be displayed\n"
    "(refer to the wiki for instructions).",

    "Select the New 3DS CPU mode.\n\n"
    "This won't apply to\n"
    "New 3DS exclusive/enhanced games.\n\n"
    "'Clock+L2' can cause issues with some\n"
    "games.",

    "Enable autobooting into homebrew menu,\n"
    "either into 3DS or DSi mode.\n\n"
    "Autobooting into a gamecard title is\n"
    "not supported.\n\n"
    "Refer to the \"autoboot\" section in the\n"
    "configuration file to configure\n"
    "this feature.",

    "Set the Luma3DS display language.",

    "If enabled, an EmuNAND\n"
    "will be launched on boot.\n\n"
    "Otherwise, SysNAND will.\n\n"
    "Hold L on boot to switch NAND.\n\n"
    "To use a different EmuNAND from the\n"
    "default, hold a directional pad button\n"
    "(Up/Right/Down/Left equal EmuNANDs\n"
    "1/2/3/4).",

    "Enable loading external FIRMs and\n"
    "system modules.\n\n"
    "This isn't needed in most cases.\n\n"
    "Refer to the wiki for instructions.",

    "Enable overriding the region and\n"
    "language configuration and the usage\n"
    "of patched code binaries, exHeaders,\n"
    "IPS code patches and LayeredFS\n"
    "for specific games.\n\n"
    "Also makes certain DLCs for out-of-\n"
    "region games work.\n\n"
    "Refer to the wiki for instructions.",

    "Redirect app. threads that would spawn\n"
    "on core1, to core2 (which is an extra\n"
    "CPU core for applications that usually\n"
    "remains unused).\n\n"
    "This improves the performance of very\n"
    "demanding games (like Pok\x82mon US/UM)\n" // CP437
    "by about 10%. Can break some games\n"
    "and other applications.\n",

    "Enable showing the current NAND:\n\n"
    "\t* Sys  = SysNAND\n"
    "\t* Emu  = EmuNAND 1\n"
    "\t* EmuX = EmuNAND X\n\n"
    "or a user-defined custom string in\n"
    "System Settings.\n\n"
    "Refer to the wiki for instructions.",

    "Enable showing the GBA boot screen\n"
    "when booting GBA games.",

    "Boot to the Luma3DS chainloader menu.",

    "Save the changes and exit. To discard\n"
    "any changes press the POWER button.\n"
    "Use START as a shortcut to this entry.",

    //----------------------------------------//

    "Luma3DS chainloader",
    "Press A to select, START to quit",

    //----------------------------------------//

    "PIN (%u digits):",

    "Enter a new PIN using ABXY and the DPad",
    "Press START to skip, SELECT to reset",
    "Press SELECT to reset",
    "Error writing the PIN file",

    "Enter the PIN using ABXY and the DPad to proceed",
    "Press START to shutdown, SELECT to clear",
    "Wrong PIN, try again",

    //----------------------------------------//

    "An exception occurred",

    "undefined instruction",
    "prefetch abort",
    "data abort",
    "kernel panic",

    "Processor:",
    "Exception type:",
    "Fault status:",
    "Current process:",

    "Access type:",
    "Stack dump:",

    "core",
    "Read",
    "Write",

    "Arm9 memory dump at offset %X size %lX",
    "Incorrect dump: failed to dump code and/or stack",
    "Press A to save the crash dump",
    "Press any other button to shutdown",
    "You can find the dump in the following file:",
    "Error writing the dump file",
    "Press any button to shutdown"
};

// Current strings
static char** lumaTranslCurrent = NULL;

/*static int iniHandler(LumaLocaleUser* user, const char* section, const char* name, const char* value, int lineno) {
    for (u8 i = 0; i < sizeof(llidTable)/4; i++) {
        if (strcmp(name, llidTable[i]) == 0) {
            strcpy(user->translated, value);
        }
    }
    return 0;
}*/

static void strrep(char* out, const char* src, const char* sub, const char* by) {
    const u16 subLen = strlen(sub), byLen = strlen(by);

    if (!subLen) {
        strcpy(out, src);
        return;
    }
    const char* p = src;
    char* w = out;
    while (*p) {
        if (!strncmp(p, sub, subLen)) {
            memcpy(w, by, byLen);
            w += byLen;
            p += subLen;
        } else *w++ = *p++;
    }
    *w = '\0';
}

bool lumaTranslHas(const Iso6391 lang) {
    u8 cnt = lumaTranslCount();
    Iso6391* lst = malloc(sizeof(Iso6391)*cnt);
    lumaTranslList(lst, cnt);
    for (u8 i = 0; i < cnt; i++) {
        if (strcmp(lst[i], lang) == 0) {
            free(lst);
            return true;
        }
    }
    free(lst);
    return false;
}

static void formatTStr(char* out, const char* src, size_t size) {
    char* bufn = malloc(size);
    strrep(bufn, src, "\\n", "\n");
    strrep(out, bufn, "\\t", "\t");
    free(bufn);
}

static int iniHandler(void* user, const char* section, const char* name, const char* value) {
    char** usert = (char**)user;

    for (u8 i = 0; i < STRCOUNT; i++) {
        if (!i) {
            if (!strcmp(name, llidTable[0]) && !strlen(section)) {
                if (usert[i]) free(usert[i]);
                usert[i] = malloc(strlen(value)+1);
                formatTStr(usert[i], value, strlen(value)+1);
                return 1;
            }
        }
        const size_t sectionLen = strlen(section);
        if (!strncmp(section, llidTable[i], sectionLen)) {
            if (!strcmp(name, llidTable[i]+sectionLen+1)) {
                if (usert[i]) free(usert[i]);
                usert[i] = malloc(strlen(value)+1);
                formatTStr(usert[i], value, strlen(value)+1);
                return 1;
            }
        }
    }
    return 0;
}

void lumaTranslLoad(const Iso6391 lang) {
    if (strcmp(lang, lumaTranslBuiltinI) == 0) {
        if (lumaTranslCurrent && lumaTranslCurrent != lumaTranslBuiltinV) free(lumaTranslCurrent);
        lumaTranslCurrent = lumaTranslBuiltinV;

        /*for (u8 i = 0; i < STRCOUNT; i++) {
            if (lumaTranslCurrent[i]) free(lumaTranslCurrent[i]);
            lumaTranslCurrent[i] = malloc(strlen(lumaTranslBuiltinV[i]));
            strcpy(lumaTranslCurrent[i], lumaTranslBuiltinV[i]);
        }*/
    } else if (!lumaTranslHas(lang)) {
        lumaTranslLoad(lumaTranslBuiltinI);
    } else {
        if (lumaTranslCurrent == lumaTranslBuiltinV) lumaTranslCurrent = NULL;
        char fpath[17];
        snprintf(fpath, sizeof(fpath), LANGS_DIR "/%s.ini", lang);
        FSIZE_t fsize;
        {
            FILINFO finfo;
            f_stat(fpath, &finfo);
            fsize = finfo.fsize;
        }
        char* ini = calloc(fsize, sizeof(char));
        if (!ini) {
            //error("Unable to allocate %lu bytes for %s strings.", fsize, lang);
            lumaTranslLoad(lumaTranslBuiltinI);
            return;
        }
        u32 frsize = fileRead(ini, fpath, fsize);
        if (frsize != fsize || !ini) {
            debugShow(
                "Could not read language '%s': %lu != %lu\n",
                lang, frsize, fsize
            )
            free(ini);
            lumaTranslLoad(lumaTranslBuiltinI);
            return;
        }
        /*for (u16 i = 0x10; i < 0xFF; i += 2) {
            debugShow(
            "%02hhX='%c'\n%02hhX='%c'",
                (u8)i, (char)i, (u8)i+1, (char)i+1
            )
        }*/
        if (lumaTranslCurrent) free(lumaTranslCurrent);
        lumaTranslCurrent = (char**)calloc(STRCOUNT, sizeof(char*));

        for (u8 i = 0; i < STRCOUNT; i++) {
            if (lumaTranslCurrent[i]) free(lumaTranslCurrent[i]);
            lumaTranslCurrent[i] = malloc(10);
            strcpy(lumaTranslCurrent[i], "<UNKNOWN>");
        }

        ini_parse_string(ini, iniHandler, lumaTranslCurrent);
        free(ini);
    }
    strcpy(configData.language, lang);
}

const char* lumaTranslGet(const LumaLocaleId l2id) {
    if (!lumaTranslCurrent) return "<UNLOADED>";
    if (!lumaTranslCurrent[l2id]) return "<NULL>";
    return lumaTranslCurrent[l2id];

    /*u8 maxInd = 0;
    for (const char* frmt = format; *frmt != '\0'; frmt++) {
        if (*frmt == '$' && (*frmt)+1 >= '0' && (*frmt)+1 <= '9') {
            u8 ind = (*frmt++)+1 - '0';
            if (ind > maxInd) maxInd = ind;
        }
    }

    char** params = malloc(4 * maxInd+1);
    for (u8 i = 0; i < maxInd; i++) {
        params[i] = va_arg(args, char*);
    }
    va_end(args);

    char res[0x180];
    char* resCur = res;

    for (const char* frmt = format; *frmt != '\0'; frmt++) {
        if (*frmt == '$' && (*frmt)+1 >= '0' && (*frmt)+1 <= '9') {
            u8 ind = (*frmt)+1 - '0';
            u8 paramLen = strlen(params[ind]);

        }
        *resCur++ = *frmt;
    }

    return res;*/
}

u8 lumaTranslCount() {
    DIR dir;

    if (f_opendir(&dir, LANGS_DIR) != FR_OK) return 1;
    u8 count = 1;

    FILINFO info;
    while (f_readdir(&dir, &info) == FR_OK && info.fname[0] != 0) {
        if (info.fname[0] == '.') continue;
        u8 fnl = strlen(info.fname);
        if (fnl != 6) continue;
        fnl -= 4;
        if (memcmp(info.fname + fnl, ".ini", 4) != 0) continue;
        count++;
    }

    f_closedir(&dir);
    return count;
}

void lumaTranslList(Iso6391* out, u8 max) {
    DIR dir;
    if (f_opendir(&dir, LANGS_DIR) != FR_OK) {
        f_closedir(&dir);
        strcpy(out[0], lumaTranslBuiltinI);
        return;
    }

    FILINFO info;
    bool putB = false;
    for (u8 i = 0; i < max; i++) {
        if (f_readdir(&dir, &info) != FR_OK || info.fname[0] == 0) {
            if (!putB) strncpy(out[i], lumaTranslBuiltinI, sizeof(Iso6391));
            break;
        }
        if (info.fname[0] > lumaTranslBuiltinI[0] && !putB) {
            strncpy(out[i++], lumaTranslBuiltinI, sizeof(Iso6391));
            putB = true;
            if (i >= max) break;
        }
        if (info.fname[0] == '.') continue;
        u8 fnl = strlen(info.fname);
        if (fnl != 6) continue;
        fnl -= 4;
        if (memcmp(info.fname + fnl, ".ini", 4) != 0) continue;
        strncpy(out[i], info.fname, sizeof(Iso6391)-1);
        out[i][2] = 0;
    }
}