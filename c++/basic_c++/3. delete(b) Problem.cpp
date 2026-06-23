#include <iostream>
#include <pthread.h>

using namespace std;

class A {
    public:

    A(){
        cout<<"A ";
    }

    ~A(){
        cout<<" A des ";
    }
};

class B{
   
     A a;
    public:
   
    B(){
        cout<<"B ";
    }
    ~B(){
        cout<<" B des";
    }
};

int main() {

 //B a; // it'll b eautomatically deleted.

 B* b = new B();
 delete(b);
 b=NULL;
return 0;
}

/*
3. delete(b) Problem

You wrote:

B b;

delete(b);

This is WRONG.

Because:

B b;

is stack allocation.

Stack memory auto deleted.


Stack vs Heap
Stack	                Heap
Automatic memory	Dynamic memory
Fast	            Slower
Auto cleanup    	Manual cleanup
Local variables 	malloc/new


Stack Allocation
B b;

Stored in stack.

Destroyed automatically when scope ends.

Heap Allocation
B* b = new B();

Must manually delete:

delete b;
Correct Heap Example
B* b = new B();

delete b;
b = NULL;
Another Problem

You wrote:

free(b);

Wrong with new.

Rules:

Allocation	Deallocation
malloc()	free()
new	        delete

Never mix.

NULL Check Problem

You wrote:

delete(b);

if(b!=NULL){
    b = NULL;
    free(b);
}

After delete:

Pointer still dangling.

Correct:

delete b;
b = NULL;


malloc example: 
B* b = (B*)malloc(sizeof(B));
free(b);
b= NULL;
*/