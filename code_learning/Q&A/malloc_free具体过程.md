### free(void* pointer)是怎么执行的？  5-22

`找到该pointer前面地址处分配的空间大小，释放内存空间，然后将pointer置为null`

想知道free如何工作那肯定需要知道malloc如何工作，正所谓怎么来的就怎么回去。
使用malloc分配内存时候根据参数`指定的大小`，分配一块`内`存，然后返回这块内存的起始位置给调用者，这就是调用者拿到的所谓的指针,但是这个指针是void类型

这个指针并不是真正的起始位置，`真正的指针在malloc返回指针 p 的前面`，内存分配器在 p 的前面用`两个字节的空间来存放分配的内存大小信息`。

### malloc 创建指定大小空间的步骤与注意事项：

malloc()函数返回的是`void类型的指针`，调用时需要`强制转换`为自己需要的类型
malloc()返回的指针`需要妥善保存`，不能丢失；否则在释放时指针`丢失首地址`，导致所分配空间无法释放
(解决方案有两种，一是如上程序，申请后用一个新指针保存首地址；而是将分配后的地址不要移动，时始终指向所分配内存的首地址)

在使用完空间后一定要`调用free()函数释放所分配的空间`，不然会造成内存泄漏

实际中对malloc执行后要`判断是否申请成功`,存在申请失败的情况。
————————————————
### realloc 内存追加扩充：

使用realloc()增加空间不一定会成功，当追加的空间较大时，后续没有足够的空间时，则重新开辟空间【开辟完将内容拷贝进去，再将原来内容释放掉】
若再次开辟失败，则会出现内存泄露（原空间没有被释放）和数据丢失（原先指针不再指向原空间，而在失败时被赋为NULL）

解决办法：
将新开辟的空间指向一个新地址。当成功时将原地址指向新地址，防止数据丢失和内存泄露
注意_Size参数为扩增后的总空间，而不是追加的空间