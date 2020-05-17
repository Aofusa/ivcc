Low Layer
=====

[![CircleCI](https://circleci.com/gh/Aofusa/ivcc.svg?style=svg)](https://circleci.com/gh/Aofusa/ivcc)

低レイヤーを歩く  

参考元
-----

<https://www.sigbus.info/compilerbook>

始め方
-----

- docker を使う

```sh
# コンテナのビルドと中に入って作業
docker build -t local.dev/compilerbook . \
&& CONTAINER=$(docker run --rm -d -it --name compilerbook local.dev/compilerbook /bin/bash) \
&& docker cp . ${CONTAINER}:/app \
&& docker attach ${CONTAINER}

# make test の実行
CONTAINER=$(docker run --rm -d -it --name compilerbook local.dev/compilerbook /bin/bash) \
&& docker cp . ${CONTAINER}:/app \
&& docker exec -t ${CONTAINER} make test \
; docker stop ${CONTAINER}
```

メモ
-----

コンパイラの目標は アセンブリ を出力すること  
入力を受け取って 出力を作れば それは立派なコンパイラ  

- test1.c  

```c
int main() {
    return 42;
}
```

- test2.s  

```s
.intel_syntax noprefix
.global main
main:
        mov rax, 42
        ret
```

C や アセンブリのコンパイルと実行  

```sh
# コンパイル
cc -o test1 test1.c
cc -o test2 test2.s

# 実行結果の取得
./test1
echo $?
```

関数もグルーバル変数も本質的にはメモリ上に存在するデータ  
関数とデータの違いは、データは実行禁止メモリ領域に割り付けられること  

```sh
echo 'char main[] = "\x48\xc7\xc0\x2a\x00\x00\x00\xc3";' > foo.c

cc -c foo.c
objdump -D -M intel foo.o
# main の中に mov  rax, 0x2a; ret  が展開されている
```

実行新規領域の設定を変えてコンパイルする  

```sh
cc -static -Wl,--omagic -o foo foo.o

./foo
echo $?
# 42 (0x2a) が出力される
```
