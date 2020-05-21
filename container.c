#include "ivcc.h"

// 現在着目しているトークン
Token *token;

// 入力プログラム
char *user_input;

// プログラムの抽象構文木
Node *code[100];

