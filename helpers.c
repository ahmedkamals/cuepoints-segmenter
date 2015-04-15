/**
 * @file
 * Helpers functions implementation.
 *
 * Copyright © 2015, Ahmed Kamal. (https://github.com/ahmedkamals)
 *
 * This file is part of Ahmed Kamal's segmenter configurations.
 * ® Redistributions of files must retain the above copyright notice.
 *
 * @copyright     Ahmed Kamal (https://github.com/ahmedkamals)
 * @link          https://github.com/ahmedkamals/dev-environment
 * @package       AK
 * @subpackage    Segmenter
 * @version       1.0
 * @since         2015-01-25 Happy day :)
 * @license
 * @author        Ahmed Kamal <me.ahmed.kamal@gmail.com>
 * @modified      2015-01-25
 */

#include <stdio.h>
#include <string.h>

/**
 * Used to compare between two strings.
 *
 * @param string data
 * @param string searchData
 *
 * @return int
 */
int findString(void *data, void *searchData) {
  
    return strcmp((char*) data, (char*) searchData) ? 0 : 1;
}

/**
 * Replace all occurrences of the search string with the replacement string.
 *
 * @param char *search the value being searched for, otherwise known as the needle. An array may be used to designate multiple needles.
 * @param char *replace the replacement value that replaces found search values. An array may be used to designate multiple replacements.
 * @param char *subject The string or array being searched and replaced on, otherwise known as the haystack.
 * @return char *
 */
char *replaceString(char *search, char *replace, char *subject) {

    static char buffer[4096];
    char *p;

    if (!(p = strstr(subject, search))) // Is 'search' even in 'str'?
        return subject;

    strncpy(buffer, subject, p - subject); // Copy characters from 'str' start to 'search' st$
    buffer[p - subject] = '\0';

    sprintf(buffer + (p - subject), "%s%s", replace, p + strlen(search));

    return buffer;
}

// vim:sw=4:tw=4:ts=4:ai:expandtab
