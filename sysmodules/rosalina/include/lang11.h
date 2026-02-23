/**
 * @file lang11.h
 * @brief Luma3DS UI runtime translation (Rosalina side)
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