#include <stdio.h>
#include "ivcc.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }

    // トークナイズしてパースする
    // 結果は code に保存される
    user_input = argv[1];
    tokenize(user_input);
    program();

    // アセンブリの前半部分を出力
    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");

    // プロローグ
    // 変数26個分の領域を確保する
    printf("        push rbp\n");
    printf("        mov rbp, rsp\n");
    printf("        sub rsp, 208\n");

    // 先頭の式から順にコード生成
    for (int i = 0; code[i]; i++) {
        // 抽象構文木を下りながらコード生成
        gen(code[i]);

        // 式の評価結果としてスタックに一つの値が残っている
        // はずなので、すたくが溢れないようにポップしておく
        printf("        pop rax\n");
    }

    // エピローグ
    // 最後の式の結果が RAX に残っているのでそれが返り値になる
    printf("        mov rsp, rbp\n");
    printf("        pop rbp\n");
    printf("        ret\n");

    return 0;
}

