# new and malloc 区别

- new 执行过程
```c++
//包含两部分： operator new 分配空间与Obj::Obj()拷贝赋值
//第一级空间配置器由malloc free remalloc实现
Obj *ob = new Obj;
//包含两部分： Obj::~Obj()  与 operator delete
//第二级由free list 调配小额区块来实现
delete ob;
```

**两者有什么区别？**

new/delete不是库函数，而是关键字，
虽然其功能完全覆盖了malloc/free，但因为C函数中只能用malloc进行动态分配内存所以仍然保留。
new能够自动在堆中申请一块空间进行存放并调用构造函数，也是需要手动delete才行。

### 1. 申请的内存所在位置
malloc操作符从`堆`上为对象动态分配内存空间，使用free释放已分配的对应内存。
new函数从`自由存储区`上动态分配内存,new与delete相对应，如果没有手动释放那么将在程序结束时自动释放。

### 2.构造部分：(包括三个方面)

##### 是否调用构造函数/析构函数  (`最关键的部分`)
使用new操作符来分配对象内存时会经历三个步骤：<br>
第一步：调用operator new 函数（对于数组是operator new[]）分配一块足够大的，原始的，未命名的内存空间以便存储特定类型的对象。
第二步：编译器运行相应的`构造函数`以构造对象，并为其传入初值。
第三部：对象构造完成后，返回一个`指向该对象的指针`。

使用delete操作符来释放对象内存时会经历两个步骤：<br>
第一步：调用对象的析构函数。
第二步：编译器调用operator delete(或operator delete[])函数释放内存空间。
总之来说，new/delete会调用对象的构造函数/析构函数以完成对象的构造/析构。而malloc则不会。

##### new与malloc是否可以相互调用
operator new /operator delete的实现可以基于malloc，而malloc的实现不可以去调用new。

##### 是否可以被重载
opeartor new /operator delete可以被重载。标准库是定义了operator new函数和operator delete函数的8个重载版本：

而malloc/free并不允许重载。

### 3.返回值部分：

##### 类型安全性
new操作符内存分配成功时，返回的是对象类型的指针，类型严格与对象匹配，无须进行类型转换，故new是符合类型安全性的操作符。
而malloc内存分配成功则是返回void * ，需要通过强制类型转换将void*指针转换成我们需要的类型。

##### 内存分配失败时的返回值
new内存分配失败时，会抛出bac_alloc异常，它不会返回NULL；malloc分配内存失败时返回NULL，成功返回void*。

### 4.是否需要指定内存大小
使用new操作符申请内存分配时无须指定内存块的大小，编译器会根据类型信息自行计算，而malloc则需要显式地指出所需内存的尺寸。

### 5.对数组的处理
C++提供了new[]与delete[]来专门处理数组类型:

`A * ptr = new A[10];`//分配10个A对象 ,使用new[]分配的内存必须使用delete[]进行释放：

`delete [] ptr;`
new对数组的支持体现在它会分别调用构造函数函数初始化每一个数组元素，释放对象时为每个对象调用析构函数。注意delete[]要与new[]配套使用，不然会找出数组对象部分释放的现象，造成内存泄漏。

至于malloc，它并知道你在这块内存上要放的数组还是啥别的东西，反正它就给你一块原始的内存，在给你个内存的地址就完事。所以如果要动态分配一个数组的内存，还需要我们手动自定数组的大小：


### 6. 能够直观地重新分配内存
使用malloc分配的内存后，如果在使用过程中发现内存不足，可以使用realloc函数进行内存重新分配实现内存的扩充。
realloc先判断当前的指针所指内存是否有足够的连续空间，如果有，原地扩大可分配的内存地址，并且返回原来的地址指针；
如果空间不够，先按照新指定的大小分配空间，将原有数据从头到尾拷贝到新分配的内存区域，而后释放原来的内存区域。

new没有这样直观的配套设施来扩充内存。

[出处参考]( https://www.cnblogs.com/ywliao/articles/8116622.html)



