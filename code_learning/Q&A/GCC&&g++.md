# 两者什么区别?
首先说明：gcc 和 GCC 是两个不同的东西

GCC:GNU Compiler Collection(GUN 编译器集合)，它可以编译C、C++、JAV、Fortran、Pascal、Object-C、Ada等语言。

gcc是GCC中的GUN C Compiler（C 编译器）

g++是GCC中的GUN C++ Compiler（C++编译器）


## 另外
一个有趣的事实就是，就本质而言，gcc和g++并不是编译器，也不是编译器的集合，它们只是一种驱动器，根据参数中要编译的文件的类型，调用对应的GUN编译器而已，比如，用gcc编译一个c文件的话，会有以下几个步骤：
所以，更准确的说法是：

gcc调用了C compiler，而g++调用了C++ compiler


## gcc和g++的主要区别
1. 对于 \*.c和*.cpp文件，gcc分别当做c和cpp文件编译（c和cpp的语法强度是不一样的）
2. 对于 \*.c和*.cpp文件，g++则统一当做cpp文件编译
3. 使用g++编译文件时，`g++会自动链接标准库STL`，而gcc不会自动链接STL
4. gcc在编译C文件时，可使用的预定义宏是比较少的
5. gcc在编译cpp文件时/g++在编译c文件和cpp文件时（这时候gcc和g++调用的都是cpp文件的编译器），会加入一些额外的宏




# 编译过程 cpp->i->s->o   .iso文件

1. 预编译  将所有的`文件包含` `宏定义`与`条件编译`等带`#`的进行替换。 .i 文件
```
g++ -E hello.cpp -o hello.i
```
2. 汇编  将预编译文件转化成汇编代码 包含语法词法的分析以及优化操作
```
g++ -S hello.i  -o  hello.s
```
3. 编译  编成二进制文件
```
g++ -c hello.s -o hello.o
```
4. 链接 可执行文件  就是将标识名字替换为函数的地址，反汇编可以看到
```
g++    hello.o  -o  hello
```