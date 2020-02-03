//
//  main.c
//  JSONiter
//
//  Created by Seyyed Parsa Neshaei on 2/3/20.
//  Copyright © 2020 Seyyed Parsa Neshaei. All rights reserved.
//

#include <stdio.h>
#include "jsoniter.h"

void eachElementCompletion(int index, char* source) {
    printf("Index: %d\nMember: %s\n", index, source);
}

int main(int argc, const char * argv[]) {
//    char source[1000] = "{\"x\":\"y\",\"z\":{\"a\":\"b\",\"c\":\"d\"}}";
//    char source[1000] = "[{\"a\":\"b\"},{\"c\":\"d\"},{\"e\":\"f\"}]";
//    char destination[1000] = {};
////    getObjectValueOfKey(source, "z", destination);
////    getStringValueOfKey(destination, "b", destination);
////    int i = getStringValueOfArray(source, -1, destination);
//    getObjectValueOfArray(source, 0, destination);
//    printf("%s\n", destination);
    
    printf("TESTING JSONiter - The best JSON Parser\n\n");
    
    char source[1000] = "{\"type\":\"List\",\"content\":[{\"sender\":\"user1\",\"content\":\"Hello!!\"},{\"sender\":\"user2\",\"content\":\"How are you?\"}]}", destination[1000] = {}, destination2[1000] = {};
    
    printf("Source: %s\n\n", source);
    
    getStringValueOfKey(source, "type", destination);
    printf("The type of JSON (should be List) == %s\n", destination);
    
    getArrayValueOfKey(source, "content", destination);
    
    getObjectValueOfArray(destination, 0, destination2);
    getStringValueOfKey(destination2, "sender", destination2);
    printf("0 index's sender (should be user1) == %s\n", destination2);
    
    getObjectValueOfArray(destination, 1, destination2);
    getStringValueOfKey(destination2, "content", destination2);
    printf("1 index's content (should be How are you?) == %s\n", destination2);
    
    printf("\nNow testing an empty array. Should print -1 now: ");
    char newSource[1000] = "{\"mykey\":[]}";
    getArrayValueOfKey(newSource, "mykey", destination);
    int nn = getStringValueOfArray(destination, 0, destination);
    printf("%d\n\n", nn);
    
    printf("Now introducing LoopOver, a new feature of JSONiter!\n");
    
    char newSource2[1000] = "[\"y\",\"o\",\"s\",\"a\"]";
    loopOverArrayForStrings(newSource2, eachElementCompletion);
    
    return 0;
}
