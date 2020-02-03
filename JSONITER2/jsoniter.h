//
//  jsoniter.h
//  JSONiter
//
//  Created by Seyyed Parsa Neshaei on 2/3/20.
//  Copyright © 2020 Seyyed Parsa Neshaei. All rights reserved.
//

/*

      ##  ######   #######  ##    ## #### ######## ######## ########
      ## ##    ## ##     ## ###   ##  ##     ##    ##       ##     ##
      ## ##       ##     ## ####  ##  ##     ##    ##       ##     ##
      ##  ######  ##     ## ## ## ##  ##     ##    ######   ########
##    ##       ## ##     ## ##  ####  ##     ##    ##       ##   ##
##    ## ##    ## ##     ## ##   ###  ##     ##    ##       ##    ##
 ######   ######   #######  ##    ## ####    ##    ######## ##     ##
 
*/

#ifndef jsoniter_h
#define jsoniter_h

#include <stdio.h>
#include <string.h>

int getStringValueOfKey(char *source, char *key, char *destination);
int getRawValueOfKey(char *source, char *key, char *destination);
int getObjectValueOfKey(char *source, char *key, char *destination);
int getArrayValueOfKey(char *source, char *key, char *destination);

int getStringValueOfArray(char *source, int index, char *destination);
int getRawValueOfArray(char *source, int index, char *destination);
void getObjectValueOfArray(char *source, int index, char *destination);
void getArrayValueOfArray(char *source, int index, char *destination);

#endif /* jsoniter_h */
