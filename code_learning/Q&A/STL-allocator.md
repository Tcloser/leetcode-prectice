# 空间配置器起什么作用？

因为序列性容器与关联性容器在创建时都会先分配一定空间大小的内存，这段内存并没有存储内容，只是规定了`存储的格式`。
所以这就关联到了 `对象构造` `空间开辟` `对象析构` `空间释放`的问题.为了将对象构造与析构与空间开辟与释放
相分隔开，提出了allocator的概念。

```c++
allocate  生成一定大小的空间
deallocate 释放该空间
construct 在单个空间上进行构造
destroy   调用对象的析构函数
```
所以在创建一个容器如vector的时候，首先开辟存储同种类型的空间，当需要进行对象构造的时候才会在空间上初始化对象。


# 异常捕获

try catch throw

throw 可以在任意地方抛出想要的异常

```c++
try {
}
catch(...){
    throw();
}
```










