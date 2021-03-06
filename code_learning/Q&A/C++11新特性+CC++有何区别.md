# C++11 有哪些`新`特性？
C++11 最常用的新特性如下：
-  auto关键字：
   编译器可以根据初始值自动推导出类型。但是不能用于函数传参以及数组类型的推导

-  nullptr关键字：
   nullptr是一种特殊类型的字面值，它可以被转换成任意其它的指针类型；而NULL一般被宏定义为0，在遇到重载时可能会出现问题。

-  智能指针：
   C++11新增了std::shared_ptr、std::weak_ptr、unique_ptr类型的智能指针，用于解决内存管理的问题。
   弃用了auto_ptr

-  初始化列表：
   使用初始化列表来对类对象进行初始化 
   
   ```c++
   AstructFunction(int a,int b):param1(a),param2(b){};
   ```

-  右值引用：[最重要特性之一,包括移动语义+完美转发]
   基于右值引用可以实现移动语义和完美转发，消除两个对象交互时不必要的`对象拷贝`，节省运算存储资源，提高效率`比如push_back & emplace_back`.
   
   表现为 `右值引用&&`符号只能作用于右值(10、"sdf"等)且具有`对右值修改的权限`。
   
   移动语义 std::move(左值) // 将左值转化为右值,因为右值本身没有变量名，只有move之后才是右值 <br>
   完美转发 std::forward(10)// 按照原来的类型进行转发，原来的左值也成为右值。而将`右值转化为左值`这个根本`不需要多余的操作`。
   
   右值引用多用在函数形参中，既能够接受右值，又能够接受move转化过的左值，虽然一个引用也能用

```c++
int a = 1;     // a 是左值
int b = 2;     // b 是左值
int c = a + b; // + 需要右值，所以 a 和 b 被转换成右值
               // + 返回右值
```

-  atomic原子操作:
   
   目的是解决在并发程序中不加锁情况下,多线程对共享内存操作事发生错误的情况。在cuda编程中
有广泛使用。

   **自旋锁**:使用原子操作模拟互斥锁的行为就是自旋锁，自旋锁状态时程序员自己控制的
   
   
-  cbegin

新增STL容器array以及tuple


# c++ 与 c 的区别
c是`面向过程`的语言(面向`硬件编程`)，c++是`面向对象`的语言(面向`编译器`)

同时C++对C进行了`扩展`,同时c是c++的子集，c可以不做修改地拿到c++使用。


# 参考智能车竞赛：为什么在嵌入式中多用c？
c++中的很多`机制都会造成开销`，相对于`实时性要求高`的嵌入式来说`难以用到面型对象机制`的许多方法，所以不采用.

~问就是**兼容性好**。

- 具体体现在使用c写的底层好，兼容性强，并不会因为不同版本编译器而产生问题，这个是不用c++的原因所在，所以为什么c++是`面向编译器编程`的原因。
