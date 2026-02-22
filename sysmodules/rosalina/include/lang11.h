/**
 * @file lang11.h
 * @brief Luma3DS UI runtime translation (Rosalina side)
 * 
 * @author Felix Homebrew
 */
#pragma once

#define MAX_STRLEN 0x200

typedef char Iso6391[3];

typedef enum {
    SID_MENU_ROOT_TITLE,
    SID_MENU_ROOT_ENTRY_SCREENSHOT,
    SID_MENU_ROOT_ENTRY_SCREENFILTERS,
    SID_MENU_ROOT_ENTRY_CHEATS,
    SID_MENU_ROOT_ENTRY_PLUGINLDR, SID_MENU_ROOT_ENTRY_PLUGINLDR_YES, SID_MENU_ROOT_ENTRY_PLUGINLDR_NO,
    SID_MENU_ROOT_ENTRY_NEW3DS
} Lang11_StringId;

/**
 * Inits UI strings
 */
void Lang11_Init();

/**
 * Get current language
 * @param out Address where output current language to
 */
void Lang11_Language(Iso6391* out);

/**
 * @return Translated string
 */
const char* Lang11_Get(Lang11_StringId sid);