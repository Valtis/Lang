#pragma once

#define COMMENT_TOKEN ";"
#define WHITE_SPACE_TOKENS " \n\t\r"

#define REGISTER_START_TOKEN 'r'
#define PRINT_TEXT_TOKEN '@'
#define NIL_TOKEN "nil"
#define END_TOKEN "end"


#define INTEGER_ADDITION "i_add"
#define INTEGER_SUBSTRACTION "i_sub"
#define INTEGER_MULTIPLICATION "i_mul"
#define INTEGER_DIVISION "i_div"
#define INTEGER_RANDOMIZE "i_rand"

#define INTEGER_COMPARE "i_cmp"
#define INTEGER_MOVE "i_mov"

#define JUMP "jump"
#define JUMP_IF_EQUAL "jeq"
#define JUMP_IF_GREATER "jgre"
#define JUMP_IF_LESSER "jle"
#define JUMP_NOT_EQUAL "jneq"

#define CALLSUB "callsub"
#define RET "ret"

#define PRINT "print"