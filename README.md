Low Layer
=====

[![CircleCI](https://circleci.com/gh/Aofusa/ivcc.svg?style=svg)](https://circleci.com/gh/Aofusa/ivcc)


低レイヤーを歩く  


## 参考元  
https://www.sigbus.info/compilerbook  


## 始め方  

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


### メモ  

コンパイラの目標は アセンブリ を出力すること  
入力を受け取って 出力を作れば それは立派なコンパイラ  

```sh
# コンパイル
cc -o test1 test1.c
cc -o test2 test2.s

# 実行結果の取得
./test1
echo $?
```
