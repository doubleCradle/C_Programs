### Linked List implementation in C

This program first adds a head node with element '1' & a null pointer, then proceeds to add 9 more nodes with elements 1 to 9, each pointer pointing to the previous node starting from element '1'.

``` c
struct node{
	int element;
	struct node* ptr;
}node;
```
#### Features

##### 1. Backward traversal with option to start from an element to the head.

```c
void traverse_backwards(int element)
```
If `-1` is passed as a parameter, then it will output traversal from the last element to the head, otherwise, if an element for eg. `3` is passed, the output traversal will start from `3` to `Head`.

##### 2. Outputs the memory location with their respective elements.

##### 3. Outputs the size of the node in bytes.

##### 4. Allocated memory will be cleared before the program exits.


#### Compiling 
``` bash
gcc linkedList.c -o linkedList
```
#### Execution

``` bash
./linkedList
```

#### Learnings
```
1. Pointers
2. Memory Allocation & type casting
```
