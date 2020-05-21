#ifndef IVCC_HEADER
#define IVCC_HEADER

#include <stdbool.h>

// 入力プログラム
extern char *user_input;

// トークンの種類
typedef enum
{
    TK_RESERVED,    // 記号
    TK_IDENT,       // 識別子
    TK_NUM,         // 整数トークン
    TK_EOF,         // 入力の終わりを表すトークン
} TokenKind;

typedef struct Token Token;

// トークン型
struct Token
{
    TokenKind kind; // トークンの型
    Token *next;    // 次の入力トークン
    int val;        // kind が TK_NUMの場合、その数値
    char *str;      // トークン文字列
    int len;        // トークンの長さ
};

// 現在着目しているトークン
extern Token *token;

// エラーを報告するための関数
// printfと同じ引数をとる
void error_at(char *loc, char *fmt, ...);

// 次のトークンが期待している記号の時には、トークンを1つ読み進めて
// 真を返す。それ以外の場合には偽を返す。
bool consume(char *op);

// 次のトークンが期待している記号の時には、トークンを一つ読み進めて
// トークンを返す。それ以外の時には NULL を返す。
Token *consume_ident();

// 次のトークンが期待している記号の時には、トークンを1つ読み進める。
// それ以外の場合にはエラーを報告する
void expect(char *op);

// 次のトークンが数値の場合、トークンを1つ読み進めてその数値を返す。
// それ以外の場合にはエラーを報告する。
int expect_number();

// 終端を表すトークン
bool at_eof();

// 新しいトークンを作成して cur に繋げる
Token *new_token(TokenKind kind, Token *cur, char *str, int len);

// 入力文字列 p をトークナイズしてグローバル変数 token に格納する
void tokenize(char *p);


// 抽象構文木のノードの種類
typedef enum
{
    ND_ADD, // +
    ND_SUB, // -
    ND_MUL, // *
    ND_DIV, // /
    ND_ASSIGN, // =
    ND_LVAR, // ローカル変数
    ND_NUM, // 整数
    ND_LT,  // <
    ND_LE,  // <=
    ND_GT,  // >
    ND_GE,  // >=
    ND_EQ,  // ==
    ND_NE,  // !=
} NodeKind;

typedef struct Node Node;

// 抽象構文木のノードの型
struct Node
{
    NodeKind kind;  // ノードの型
    Node *lhs;      // 左辺
    Node *rhs;      // 右辺
    int val;        // kind が ND_NUM の場合のみ使う
    int offset;     // kind が ND_LVAR の場合のみ使う
};

// プログラムの抽象構文木
extern Node *code[100];

void program();     // program  = stmt*
Node *stmt();       // stmt     = expr ";"
Node *expr();       // expr     = assign
Node *assign();     // assign   = equality ("=" assign)?
Node *equality();   // equality = relational ("==" relational | "!=" relational)*
Node *relational(); // relational = add ("<" add | "<=" add | ">" add | ">=" add)*
Node *add();        // add      = mul ("+" mul | "-" mul)*
Node *mul();        // mul      = unary ("*" unary | "/" unary)*
Node *unary();      // unary    = ("+" | "-")? primary
Node *primary();    // primary  = num | ident | "(" expr ")"

Node *new_node(NodeKind kind, Node *lhs, Node *rhs);
Node *new_node_num(int val);
void gen(Node *node);

#endif

