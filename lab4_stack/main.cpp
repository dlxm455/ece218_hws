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

void myCalculator (string str, bool bInt) {
    Pstack * s4 = new Pstack();
    
    istringstream iss(str);
    string word;
    
    MObject * m_pop1;
    MObject * m_pop2;
    MObject * m_push;
    
    
    char *cptr;
    
    void *i1, *i2, *i3, *lnum;
    
    
    while (iss >> word) {
        
        if (word == "+" || word == "-" || word == "/" || word == "*") {
            m_pop1 = s4->pop();
            m_pop2 = s4->pop();
            if (m_pop1 == NULL || m_pop2 == NULL) {
                fprintf(stderr, "Not enough operands.\n");
                exit(1);
            }
            
            if (bInt) {
                i2 = (int *)(m_pop1->getValue());
                i1 = (int *)(m_pop2->getValue());
            }
            else {
                i2 = (float *)(m_pop1->getValue());
                i1 = (float *)(m_pop2->getValue());
            }
            
            
            delete m_pop1;
            m_pop1 = NULL;
            delete m_pop2;
            m_pop2 = NULL;
        }
        
        else {
            if (bInt)
                *(int*)lnum = strtol(word.c_str(), &cptr, 10);
            else
                *(float*)lnum = strtof(word.c_str(), &cptr);
            
            if (*cptr != '\0') {
                fprintf(stderr, "Invalid expression.\n");
                exit(1);
            }
        }
        
        if (word == "+") {
            if (bInt) *(int*)i3 = *(int*)i1 + *(int*)i2;
            else *(float*)i3 = *(float*)i1 + *(float*)i2;
        } else if (word == "-") {
            if (bInt) *(int*)i3 = *(int*)i1 - *(int*)i2;
            else *(float*)i3 = *(float*)i1 - *(float*)i2;
        } else if (word == "/") {
            if (bInt) *(int*)i3 = *(int*)i1 / *(int*)i2;
            else *(float*)i3 = *(float*)i1 / *(float*)i2;
        } else if (word == "*") {
            if (bInt) *(int*)i3 = (*(int*)i1) * (*(int*)i2);
            else *(float*)i3 = (*(float*)i1) * (*(float*)i2);
        } else {

            i3 = lnum;
        }
        
        if (bInt)
            m_push = new MInt(*(int*)(i3));
        else
            m_push = new MFloat(*(float*)(i3));
        
        s4->push(m_push);
        
        m_push = NULL;
    
        
    } // end of while
    
    m_pop1 = s4->pop();
    
    
    if (bInt) {
        int result = *(int*)(m_pop1->getValue());
        cout << "result: " << result << endl;
    }
    
    else {
        float fresult = *(float*)(m_pop1->getValue());
        cout << "result: " << fresult << endl;
    }
    
    
    cout << "stack size after final pop: " << s4->getSize() << endl;
    
    delete m_pop1;
    m_pop1 = NULL;
    
    delete s4;

}

int main() {
    
    /* ===== Part 1 Using Template ===== */
    /*
	Tstack<char> s1;
	Tstack<int> s2;

	cout << "===== Stack of char (s1) =====" << endl;
	s1.push('a');
	s1.push('b');
	s1.push('c');
	cout << "s1 before pop:" << endl;
	s1.print(cout);
	
	char c = s1.pop();
	cout << "poped char: " << c << endl;
	cout << "s1 after pop:" << endl;
	s1.print(cout);

	cout << "===== Stack of int (s2) =====" << endl;
	s2.push(1);
	s2.push(2);
	s2.push(3);
	cout << "s2 before pop:" << endl;
	s2.print(cout);

	int i = s2.pop();
	cout << "poped int: " << i << endl;
	cout << "s2 after pop:" << endl;
	s2.print(cout); 
    
    */

	/* ===== Part 2 Using Polymorphism ===== */
    
    
    /*
	Pstack * s3 = new Pstack();

	//MObject * mo;
	MInt * mi1 = new MInt(1);
	MInt * mi2 = new MInt(2);
	MInt * mi3 = new MInt(3);
    
    cout << "===== Stack of MInt (s3) =====" << endl;
	s3->push((MObject *)mi1);
	s3->push((MObject *)mi2);
	s3->push((MObject *)mi3);
 
    cout << "s3 before pop:" << endl;
	s3->print(cout);
    
    MObject * mo = s3->pop();
    int value = *(int *)((MInt *)mo->getValue());
    cout << "poped value: " << value << endl;
    cout << "s3 after pop:" << endl;
    s3->print(cout);
    
    delete s3;
    delete mo;
    
    */
    
    /* ===== Part 3 Integer Calculator ===== */
    /*

    Pstack * s4 = new Pstack();
    
    string str = "123 34 + 23 - 2  *";
    
    istringstream iss(str);
    string word;
    
    MObject * m_pop1;
    MObject * m_pop2;
    
    long lnum;
    char *cptr;
    int i1, i2, i3;
    
    MInt * mi_push;
    
    
    
    while (iss >> word) {
        
        if (word == "+" || word == "-" || word == "/" || word == "*") {
            m_pop1 = s4->pop();
            m_pop2 = s4->pop();
            if (m_pop1 == NULL || m_pop2 == NULL) {
                fprintf(stderr, "Not enough operands.\n");
                exit(1);
            }
            i2 = *(int *)(m_pop1->getValue());
            i1 = *(int *)(m_pop2->getValue());
            
            delete m_pop1;
            m_pop1 = NULL;
            delete m_pop2;
            m_pop2 = NULL;
        }
        
        else {
            lnum = strtol(word.c_str(), &cptr, 10);
            if (*cptr != '\0') {
                fprintf(stderr, "Invalid expression.\n");
                exit(1);
            }
        }
            
        if (word == "+") {
            i3 = i1 + i2;
        } else if (word == "-") {
            i3 = i1 - i2;
        } else if (word == "/") {
            i3 = i1 / i2;
        } else if (word == "*") {
            i3 = i1 * i2;
        } else {
            i3 = (int)lnum;
        }
        
        mi_push = new MInt(i3);;
        s4->push((MObject *) mi_push);
        
        mi_push = NULL;
        
    }
    
    m_pop1 = s4->pop();
    int result = *(int*)(m_pop1->getValue());
    cout << "result: " << result << endl;
    cout << "stack size after final pop: " << s4->getSize() << endl;
    
    delete m_pop1;
    m_pop1 = NULL;
    
    delete s4;
     */
    string str = "123 34 + 23 - 2  *";
    myCalculator(str, true);

}