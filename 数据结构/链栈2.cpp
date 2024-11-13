#include <iostream>
using namespace std;

typedef struct Linkstack {
    int data;
    struct Linkstack* next;
} Linkstack, *Linkstacknode;

Linkstacknode initstack() {
    Linkstacknode top = new Linkstack; // 使用 new 而不是 malloc
    if (top == nullptr) {
        cout << "分配失败" << endl;
        exit(1);
    }
    top->next = nullptr;
    return top;
}

Linkstacknode pushstack(Linkstacknode top) {
    int num;
    cin >> num;
    while (num != -1) {
        Linkstacknode node = new Linkstack; // 使用 new 而不是 malloc
        if (node == nullptr) {
            cout << "分配失败" << endl;
            exit(1);
        }
        node->data = num;
        node->next = top->next;
        top->next = node;
        cin >> num;
    }
    return top;
}

Linkstacknode popstack(Linkstacknode top) {
    while (top->next != nullptr) {
        Linkstacknode temp = top->next;
        top->next = temp->next;
        cout << temp->data << " ";
        delete temp; // 使用 delete 而不是 free
    }
    return top;
}

int main() {
    Linkstacknode top = initstack();
    top = pushstack(top);
    top = popstack(top);
    delete top; // 释放初始化的栈顶元素
    return 0;
}
/*
这些是很好的问题。让我逐一解释：

1. **为什么使用 `new` 而不是 `malloc`**：
    - 在 C++ 中，`new` 和 `delete` 是标准的内存分配和释放方式，而 `malloc` 和 `free` 来自 C 语言。主要有以下几个原因推荐使用 `new`：
        - **构造函数和析构函数的调用**：`new` 自动调用对象的构造函数，而 `delete` 调用析构函数。这对于包含非平凡构造函数或析构函数的类非常重要。
        - **类型安全**：`new` 是类型安全的，它直接返回正确的类型指针，不需要类型转换，而 `malloc` 返回的是 `void*` 类型，需要显式转换。
        - **异常处理**：在内存分配失败时，`new` 抛出异常（`std::bad_alloc`），而 `malloc` 返回 `NULL`。这有助于更好地处理内存分配失败的情况。
        - **便捷性**：`new` 不需要显式指定分配的字节数，因为它根据类型自动确定。

2. **关于 `sizeof(Linkstack)` 和 `sizeof(Linkstacknode)` 的说明**：
    - 在您的原始代码中，您使用了 `malloc(sizeof(Linkstacknode))` 来分配内存。这里存在一个误解：
        - `Linkstacknode` 是一个指针类型，指向 `Linkstack` 结构。因此，`sizeof(Linkstacknode)` 实际上返回的是指针的大小，而不是 `Linkstack` 结构的大小。
        - 当您想要分配一个 `Linkstack` 结构的内存时，应该使用 `sizeof(Linkstack)`。这样做是为了确保分配足够的内存来存储 `Linkstack` 结构体的所有成员。
        - 使用 `malloc(sizeof(Linkstacknode))` 实际上分配的内存可能不足以容纳一个完整的 `Linkstack` 结构体，这可能导致未定义行为，比如内存越界访问。

简而言之，选择 `new` 与 C++ 的设计哲学更为一致，能更好地利用 C++ 的特性。而在分配内存时，确保分配足够的空间以容纳所需的数据结构是非常重要的。*/