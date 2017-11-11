#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "tstack.h"
#include "pstack.h"
#include "MObject.h"
#include "MInt.h"
#include "MFloat.h"

using namespace std;

int myCalculator (string str, bool bInt) {
    
    // Create a stack in heap space
    Pstack * s4 = new Pstack();
    
    // For string splitting
    istringstream iss(str);
    string word; // each substring separated by space
    
    // Pointers for results of pop() and paramater for push()
    MObject * m_pop1 = NULL;
    MObject * m_pop2 = NULL;
    MObject * m_push = NULL;
    
    // Pointers to hold values of MObjects
    void *i1 = NULL;
    void *i2 = NULL;
    void *i3 = NULL;
    
    // Allocate space for i3 which will hold the operand or intermediate calculation result
    if (bInt) i3 = new int();
    else i3 = new float();
    
    // For string to number conversion
    void *lnum = NULL;
    char *cptr = NULL;
    
    
    while (iss >> word) {
        
        // Read in operator
        if (word == "+" || word == "-" || word == "/" || word == "*") {
            
            // pop out the top two MObjects
            m_pop1 = s4->pop();
            m_pop2 = s4->pop();
            
            if (m_pop1 == NULL || m_pop2 == NULL) {
                fprintf(stderr, "Invalid Expression.\n");
                
                // clear everything before return
                if (m_pop1 != NULL) {
                    delete m_pop1;
                    m_pop1 = NULL;
                }
                
                if (m_pop2 != NULL) {
                    delete m_pop1;
                    m_pop2 = NULL;
                }
                
                if (i3 != NULL) {
                    if (bInt) delete (int*)i3;
                    else delete (float*)i3;
                    i3 = NULL;
                }
                delete s4;
                
                return(1);
            }
            
            // get the values from the popped MObjects
            if (bInt) {
                i2 = (int *)(m_pop1->getValue()); // first value in stack is the second operand
                i1 = (int *)(m_pop2->getValue());
            }
            else {
                i2 = (float *)(m_pop1->getValue());
                i1 = (float *)(m_pop2->getValue());
            }
            
            // make value pointed by i3 equals to the result of the operation
            if (word == "+") {
                if (bInt) *(int*)i3 = *(int*)i1 + *(int*)i2;
                else *(float*)i3 = *(float*)i1 + *(float*)i2;
            } else if (word == "-") {
                if (bInt) *(int*)i3 = *(int*)i1 - *(int*)i2;
                else *(float*)i3 = *(float*)i1 - *(float*)i2;
            } else if (word == "/") {
                if (bInt) *(int*)i3 = *(int*)i1 / *(int*)i2;
                else *(float*)i3 = *(float*)i1 / *(float*)i2;
            } else { //(word == "*")
                if (bInt) *(int*)i3 = (*(int*)i1) * (*(int*)i2);
                else *(float*)i3 = (*(float*)i1) * (*(float*)i2);
            }
            
            // let i1, i2 point to NULL for safety
            i1 = NULL;
            i2 = NULL;
        }
        else { // Read in number
            // make value pointed by i3 equals to the number converted from input substring
            if (bInt) {
                long l = strtol((const char *)word.c_str(), &cptr, 10);
                *(int*)i3 = (int)l;
            }
            
            else {
                float f = strtof(word.c_str(), &cptr);
                *(float*)i3 = (float)f;
            }
            
            if (cptr && *cptr != '\0') {
                fprintf(stderr, "Invalid expression.\n");
                
                // clear everything before return
                if (m_pop1 != NULL) {
                    delete m_pop1;
                    m_pop1 = NULL;
                }
                
                if (m_pop2 != NULL) {
                    delete m_pop1;
                    m_pop2 = NULL;
                }
                
                if (i3 != NULL) {
                    if (bInt) delete (int*)i3;
                    else delete (float*)i3;
                    i3 = NULL;
                }
                delete s4;
                
                return(1);
            }
        }
        

        // create MObject by value of i3
        if (bInt)
            m_push = new MInt(*(int*)(i3));
        else
            m_push = new MFloat(*(float*)(i3));
        
        
        // push the MObject on to the stack
        s4->push(m_push);
    
        m_push = NULL; // for safefy
        
        // clear the popped MObjects
        if (m_pop1 != NULL) {
            delete m_pop1;
            m_pop1 = NULL;
        }
        
        if (m_pop2 != NULL) {
            delete m_pop1;
            m_pop2 = NULL;
        }
    
        
    } // end of while
    
    // clear the allocated space for i3
    if (i3 != NULL) {
        if (bInt) delete (int*)i3;
        else delete (float*)i3;
        i3 = NULL;
    }
    
    // pop the MObejct held by the top node which should be the only one left
    m_pop1 = s4->pop();
    
    if (s4->getSize() != 0) {
        fprintf(stderr, "Invalid Expression.\n");
        
        //clear everthing left before return
        if (m_pop1 != NULL) {
            delete m_pop1;
            m_pop1 = NULL;
        }
        
        delete s4;
        
        return(1);
    }
    
    
    // get result and print out
    if (bInt) {
        int result = *(int*)(m_pop1->getValue());
        cout << "result: " << result << endl;
    }
    
    else {
        float fresult = *(float*)(m_pop1->getValue());
        cout << "result: " << fresult << endl;
    }
    
    
    //cout << "stack size after final pop: " << s4->getSize() << endl;
    
    // delete the last popped MObject
    if (m_pop1 != NULL) {
        delete m_pop1;
        m_pop1 = NULL;
    }
   
    // delete stack
    delete s4;
    
    return 0;

}


int main() {
    
    /* ===== Part 1 Using Template ===== */
    
	Tstack<char> s1;
	Tstack<int> s2;

	cout << "===== Stack of char (s1) =====" << endl;
	s1.push('a');
	s1.push('b');
	s1.push('c');
	cout << "s1 before pop:" << endl;
	s1.print(cout);
	
    char c;
	int ret = s1.pop(c);
    if (ret == 0) {
        cout << "poped char: " << c << endl;
        cout << "s1 after pop:" << endl;
        s1.print(cout);
    }

	cout << "===== Stack of int (s2) =====" << endl;
	s2.push(1);
	s2.push(2);
	s2.push(3);
	cout << "s2 before pop:" << endl;
	s2.print(cout);
    
    
    int i;
    ret = s2.pop(i);
    if (ret == 0) {
        cout << "poped int: " << i << endl;
        cout << "s2 after pop:" << endl;
        s2.print(cout);
    }
    

	/* ===== Part 2 Using Polymorphism ===== */
    
	Pstack * s3 = new Pstack();

	//MObject * mo;
	MInt * mi1 = new MInt(1);
	MInt * mi2 = new MInt(2);
	MInt * mi3 = new MInt(3);
    
    cout << "===== Stack of MInt (s3) =====" << endl;
	s3->push((MObject *)mi1);
	s3->push((MObject *)mi2);
	s3->push((MObject *)mi3);
    
    // MInts are pointed by nodes in stack, set original pointers to NULL
    mi1 = NULL;
    mi2 = NULL;
    mi3 = NULL;
 
    cout << "s3 before pop:" << endl;
	s3->print(cout);
    
    MObject * mo = s3->pop();
    int value = *(int *)((MInt *)mo->getValue());
    cout << "poped value: " << value << endl;
    cout << "s3 after pop:" << endl;
    s3->print(cout);
    
    // Only mo points to the popped MObject, could be deleted
    delete mo;
    
    // delete stack pointer
    // stack desturctor, each node destructor, and each MInt:MObject destructor are called in chain
    delete s3;
    
    
    /* ===== Part 3 Calculator ===== */
    
    
    /* Using generic calulator function */
    
    
    cout << "===== Integer Calculator =====" << endl;
    string str = "123 34 + 23 - 2  *";
    cout << "Calculate: " << str << endl;
    myCalculator(str, true);

    cout << "===== Float Calculator =====" << endl;
	string fstr = "12.34 5.45 + 12.12 *";
    cout << "Calculate: " << fstr << endl;
	myCalculator(fstr, false);
   
    
    while (true) {
        string in_str1;
        cout << "Do you want to do interger calculation (i) or float calculation (f) or quit (q)? ";
        cin.clear();
        getline(cin, in_str1);
        while (!(in_str1 == "i" || in_str1 == "f" || in_str1 == "q")) {
            cout << "Only i (interger calculation) or f (float calculation) or q (quit) are allowed! ";
            cin.clear();
            getline(cin, in_str1);
        }
        if (in_str1 == "q") return 0;
        
        string in_str2;
        cout << "Enter the post fix expression: ";
        cin.clear();
        //cin.ignore();
        getline(cin, in_str2);
        if (in_str1 == "i") myCalculator(in_str2, true);
        else myCalculator(in_str2, false);

    }
    
    return 0;

}



