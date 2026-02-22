/**
 * @file lang11.c
 * @brief Luma3DS UI runtime translation (Rosalina side)
 * 
 * @author Felix Homebrew
 */
#include "lang11.h"

#include <3ds.h>
#include <stdlib.h>
#include <string.h>

#include "ifile.h"
#include "ini.h"

#define LANGS_DIR "langs"
#define STRCOUNT (sizeof(sidTable)/sizeof(sidTable[0]))

#define MAX_INIBUF 0x7FFF

static const char* sidTable[] = {
    "ROSALINA_MENU_ROOT_TITLE",
    "ROSALINA_MENU_ROOT_ENTRY_SCREENSHOT",
    "ROSALINA_MENU_ROOT_ENTRY_SCREENFILTERS",
    "ROSALINA_MENU_ROOT_ENTRY_CHEATS",
    "ROSALINA_MENU_ROOT_ENTRY_PLUGINLDR",
    "ROSALINA_MENU_ROOT_ENTRY_PLUGINLDR_YES",
    "ROSALINA_MENU_ROOT_ENTRY_PLUGINLDR_NO",
    "ROSALINA_MENU_ROOT_ENTRY_NEW3DS"
};

static const Iso6391 strBuiltinI = "en";
static const char* strBuiltinV[STRCOUNT] = {
    "Rosalina menu",
    "Take screenshot",
    "Screen filters...",
    "Cheats...",
    "Plugin Loader: [%s]", "Enabled", "Disabled",
    "New 3DS menu..."
};

static Iso6391 curLang = {0};
static char curStrings[STRCOUNT][MAX_STRLEN];

int iniHandler(void* user, const char* section, const char* name, const char* value) {
    (void)user;

    if (strlen(section) >= 9) {
        if (strncmp(section, "ROSALINA_", 9)) return 0;
    } else return 0;

    //const char* subSection = section+9;

    for (u8 i = 0; i < STRCOUNT; i++) {
        const u32 sectLen = strlen(section);
        if (strncmp(section, sidTable[i], sectLen)) continue;
        const char* trsid = sidTable[i] + sectLen + 1;
        if (strcmp(name, trsid)) continue;
        memset(curStrings[i], 0, sizeof(curStrings[i]));
        strcpy(curStrings[i], value);
        return 1;
    }

    return 1;
}

void Lang11_Init() {
    s64 buf;
    Result res;

    svcGetSystemInfo(&buf, 0x10000, 0x10F);
    strncpy(curLang, (const char*)&buf, sizeof(Iso6391));
    if (!strcmp(curLang, strBuiltinI)) {
        return;
    }
    
    svcGetSystemInfo(&buf, 0x10000, 0x203);
    bool sdMode = (bool)buf;

    char path[] = "/luma/" LANGS_DIR "/??.ini";
    sprintf(path, "/luma/" LANGS_DIR "/%.2s.ini", curLang);

    FS_ArchiveID arcId = sdMode ? ARCHIVE_SDMC : ARCHIVE_NAND_RW;
    IFile file;
    res = IFile_Open(&file, arcId, fsMakePath(PATH_EMPTY, ""), fsMakePath(PATH_ASCII, path), FS_OPEN_READ);
    if (R_FAILED(res)) {
        strcpy(curLang, strBuiltinI);
        return;
    }

    u64 fsize;
    res = IFile_GetSize(&file, &fsize);
    if (R_FAILED(res) || fsize > MAX_INIBUF) {
        IFile_Close(&file);
        strcpy(curLang, "e1");
        return;
    }

    /*char* iniBuf = (char*)calloc(fsize, sizeof(char));
    if (!iniBuf) {
        IFile_Close(&file);
        strcpy(curLang, "eb");
        return;
    }*/
   static char iniBuf[MAX_INIBUF];

    u64 read = 0;
    res = IFile_Read(&file, &read, iniBuf, fsize);
    IFile_Close(&file);
    //free(iniBuf);
    //strcpy(curLang, "hf");
    //return;
    if (R_FAILED(res) || read != fsize) {
        IFile_Close(&file);
        strcpy(curLang, "e2");
        return;
    }

    for (u8 i = 0; i < STRCOUNT; i++) {
        memset(curStrings[i], 0, sizeof(curStrings[i]));
        strcpy(curStrings[i], "<UNKNOWN>");
    }

    ini_parse_string(iniBuf, iniHandler, NULL);
}

void Lang11_Language(Iso6391* out) {
    strcpy((char*)out, curLang);
}

const char* Lang11_Get(Lang11_StringId sid) {
    if (!strcmp(curLang, strBuiltinI)) {
        return strBuiltinV[sid];
    }
    return curStrings[sid];
}