#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace::std;

class Person {
public:
	Person() {}
	virtual void AboutMe() = 0; // makes this now a pure virtual method, and class Person is now abstract
	virtual ~Person() {}
};

class Student : public Person {
public:
	Student() {}
	void AboutMe() {
		printf("I am a Student\n");
	}
	~Student() {}
};

class Teacher : public Person {
public:
	Teacher() {}
	~Teacher() {}
	void AboutMe() {
		printf("I am a Teacher\n");
	}
};

    void reverseoneword(int b, int e, string &s) {

        if (s.empty())
            return;

        int begin = b;
        int end = e;
        char temp;

        while (begin <= end) {
            temp = s[begin];
            s[begin] = s[end];
            s[end] = temp;
            end--;
            begin++;
        }
        return;
    }

    void reverseWords(string &s) {

        if (s.empty())
            return;

        int len = s.length();

        int beginindex = 0;
        int endindex = 0;

        while (endindex < len){
            
            // skip initial ws
            while (s[endindex]== ' ') {
                endindex++;
            }
            if (s[endindex] == ' ')
                beginindex = endindex - 1;
            else
                beginindex = endindex;

            // find endindex
            while ((s[endindex] != ' ') && (endindex < len)) {
                endindex++;
            }
            reverseoneword(beginindex, endindex-1, s);
        }

        // once all words are reversed, reverse the entire word
        reverseoneword(0,s.length()-1,s);

        return;
    }

void main()
{

	Person *p1 = new Student();
	p1->AboutMe();

	delete p1;

    string s = "This is a test";
    cout << "Original String: " << s << endl;
    reverseWords(s);
    cout << "Reversed String: " << s << endl;

}