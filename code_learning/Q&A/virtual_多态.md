# 虚函数 以及 多态的实现

**多态是什么？**
wiki : `相同的信息`发送给`不同的对象`能够引发`不同的动作`.

**多态有哪几种？**
具体表现为四种：
`子类多态`(运行时多态 类向上转化后给父类指针 调用子类方法 **指针引用,否则就算是虚函数也只会调用父类方法**)、
`参数多态`(模板类的使用)、
`重载多态`、(重载运算符)
`强制多态`.(强制数据类型转化)

也可以分为`静态多态`与`动态多态`两部分

**虚函数是什么**
在某基类中声明为virtual，在一个或多个派生类中被重写的函数。目的是为了实现子类多态属性,
**因为派生类中重定义后的方法向上转化后调用只能表现出当前类的方法**。

**虚函数如何实现的？**

- 虚函数的实现与`虚函数表`及其中存储的`虚函数指针`有关
  **类的`存储地址中`除了定义的`函数成员`，还有一个成员是`虚函数表指针`**（占四个基本内存单元）
  【所以不论定义了多少虚函数，类中都只有一个虚函数表指针来对方法的使用进行索引。】
  
  这个`指针指向`一个`虚函数表的起始位置`，这个表会与类的定义同时出现，
  这个`表存放着`该类的`虚函数指针`，调用的时候可以找到该类的虚函数表指针，
  通过虚函数表指针找到虚函数表，通过虚函数表的偏移找到函数的入口地址，从而找到要使用的虚函数。

- 当实例化一个该类的子类对象的时候，（如果）该类的子类并没有定义虚函数，
  但是却从父类中`继承了虚函数`，那么在实例化该类子类对象的时候也会`产生一个虚函数表`，这个虚函数表是子类的虚函数表，
  `在没有重载的情况下`记录的子类的虚函数地址却是与父类的是一样的。
  所以通过子类对象的虚函数表指针找到自己的虚函数表，
  在自己的虚函数表找到的要执行的函数指针也是父类的相应函数入口的地址。

-（有关覆盖）如果我们在子类中重载了从父类继承来的虚函数，然而对于父类来说本身是没有被改变的.
  对于子类来说它的虚函数表与之前的虚函数表是一样的，但是如果此时子类中重写了（从父类那继承来的）
  相应虚函数，那么它的虚函数表当中关于这个函数的指针就会覆盖掉原有的指向父类函数的指针的值，
  换句话说就是指向了自己定义的相应函数，（父类指向子类？？）
  `这样如果用父类的指针指向子类的对象，就会通过子类对象当中的虚函数表指针找到子类的虚函数表，
  从而通过子类的虚函数表找到子类的相应虚函数地址，而此时的地址已经是该函数自己定义的虚函数入口地址，
  而不是父类的相应虚函数入口地址，所以执行的将会是子类当中的虚函数`。这就是多态的原理。若子函数中
  重载了虚函数那么就会调用之，若没定义则会调用父类的函数。

```c++

CMan m_man;

CChild m_child;

//这才是使用的精髓，如果不定义基类的指针去使用，没有太大的意义

CMan *p ;

p = &m_man ;

p->Eat(); //始终调用CMan的Eat成员函数，不会调用 CChild 的

p = &m_child; // 父类指向子类，如果子类没有实现该函数，则调用CMan的Eat函数

p->Eat(); //如果子类实现(覆盖)了该方法，则始终调用CChild的Eat函数

```
