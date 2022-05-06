/**
 * You can modify this file.
 */

#include <stdio.h>
#include "matcher.h"

#define TRUE 1
#define FALSE 0

/**
 * Your helper functions can go below this line
 */


//returns TRUE (1) if char c is a dot operator; otherwise returns FALSE (0)
int is_dot_operator(char c) {
  if (c == '.') {
    return TRUE;
  } else {
    return FALSE;
  }
}

//returns TRUE (1) if char c is a plus sign; otherwise returns FALSE (0)
int is_plus_sign_operator(char c) {
  if (c == '+') {
    return TRUE;
  } else {
    return FALSE;
  }
}

//returns TRUE (1) if char c is a question mark; otherwise returns FALSE (0)
int is_question_mark_operator(char c) {
  if (c == '?') {
    return TRUE;
  } else {
    return FALSE;
  }
}

//returns true(1) if char c is a backslash; otherwise returns false (0)
int is_backslash_operator(char c) {
  if (c == '\\') {
    return TRUE;
  } else {
    return FALSE;
  }
}

//returns number of times c occurs consecutively from the start of partial_line
int plus_sign_increment(char *partial_line, char c) {
  int increment = 0;
  while (*(partial_line + increment) == c) {
    increment++;
  }
  return increment;
}

//returns number of times c occurs c occurs at the start of partial_line
int question_mark_increment(char *partial_line, char c) {
  //if c occurs at the start of partial_line, returns 1
  if (*partial_line == c) {
    return 1;
  //if c doesnt occur at the start of partial_line, returns 0
  } else {
    return 0;
  }
}

/**
 * Your helper functions can go above this line
 */


/**
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
//recursive function: returns TRUE (1) if the given pattern occurs at the beginning of partial_line; otherwise returns FALSE (0)
int matches_leading(char *partial_line, char *pattern) {  
  int i = 1;
  //if all of pattern has been checked against partial_line, without any return false (meaning the entire pattern occurs at the beginning partial_line) then returns TRUE (1)
  if (*pattern == '\0') { 
    return TRUE;
  }
  //else checks if the current element pointed to in pattern is a backslash; returns TRUE (1) if it is
  else if (is_backslash_operator(*pattern) == TRUE) {
      //then checks if the element after the backslash in pattern is equal to *partial_line 
      if (*(pattern + 1) == *partial_line) {
        //if so, then recursively calls function again, skipping past the character that is "escaped" by the blackslash operator in partial_line and pattern 
        return matches_leading(partial_line+1, pattern+2);
      }
  }
  //checks if 1 element ahead of *pattern is a question mark operator; returns TRUE (1) if it is
  else if (is_question_mark_operator(*(pattern + 1)) == TRUE) {
      //question_mark_increment returns number of times the character preceding the question mark operator occurs (so either 0 or 1)
      i = question_mark_increment(partial_line, *pattern);
      //recursively calls function again, this time skipping past the number of pattern characters in partial_line, and skipping past the character and question mark operator in pattern
      return matches_leading(partial_line+i, pattern+2);
  }
  //checks if 1 element ahead of *pattern is a plus sign operator; returns TRUE (1) if it is
  else if (*pattern == *partial_line && is_plus_sign_operator(*(pattern + 1)) == TRUE) {
    //plus_sign_increment returns the number of times the character preceding plus sign operator occurs
    i = plus_sign_increment(partial_line, *pattern);
    //recursively calls function again, this time skipping past the number of repeating characters in partial_line, and skipping past the character and plus sign operator in pattern 
    return matches_leading(partial_line+i, pattern+2);
  } 
  //checks if current element pointed to in pattern is a dot operator (.); returns TRUE (1) if it is
  else if (is_dot_operator(*pattern) == TRUE) {
    //if there is nothing else to compare dot operator to (reached end of partial_line), then return FALSE (0)
    if (*partial_line == '\0') {
      return FALSE;
    //else consider dot operator as able to match to anything/equal, hence recursively call function again
    } else {
      return matches_leading(partial_line+1, pattern+1);
    }
  }
  //checks if current element pointed to in pattern and beginning of partial_line match; returns TRUE (1) if they do
  else if (*pattern == *partial_line) { 
    //recursively call function again, this time checking if the next elements match
    return matches_leading(partial_line+1, pattern+1);
  }
  
  //if all of the above cases do not pass, returns FALSE (0)
  return FALSE;

}

/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */
//TEST CASE EXAMPLE: line = "abcd"; pattern = "bc";
int rgrep_matches(char *line, char *pattern) {
  //match_found checks if pattern matches current line segment
  int match_found = FALSE;
  //loops through line while calling matches_leading to check if the pattern occurs at the start of every element in line
  while (*line != '\0') {
    //calls function matches_leading(), which will return either TRUE (1) or FALSE (0)
    match_found = matches_leading(line, pattern);
    //if match_found is TRUE, pattern occurs at the start of the line
    if (match_found == TRUE) {
      //rgre_matches() returns TRUE
      return TRUE;
    //else match_found returns FALSE, meaning the pattern is not found at where line currently points to; increments line to move on and check the next element
    }
    ++line;
  }
  //all of line has been looped through and pattern has not been found; rgrep_matches() returns FALSE (0)
  return FALSE;
}