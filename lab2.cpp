#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

#ifdef __cplusplus
extern "C" {
  
  #endif
  double calc(const char * str, int * status);
  #ifdef __cplusplus
  
  }


#endif
class Operation_stack {
  int size;
  char operations[25];  
  
  public:
    Operation_stack(){
      size = 0;
      for (int i = 0; i < 25; ++i)
      {
        operations[i] = 0;
      }
   }
     int get_size(){
      return size;
     }
     void Push_stack(char operation) {
     operations[size++] = operation; 
    } 

     char Pop_stack() {
      size--;
      return operations[size];
    }  

   int Priority(char operation) {
    int k,l;
    if (operation == '*' || operation == '/' ) k = 2;
    if (operation == '-' || operation == '+' ) k = 1;
    if (operation == '^' )  k = 3;
    
    if (operations[size-1] == '*' || operations[size-1] == '/' ) l = 2;
    if (operations[size-1] == '-' || operations[size-1] == '+' ) l = 1;
    if (operations[size-1] == '^' )  l = 3;
  
    
    if (l<k) return 1;
    else return 0;
   } 
   
   int skobki () {

    if (operations[size-1]=='(') return 1;
    return 0;


   }

   void print() {

      for (int i = 0; i < size; ++i)
      {
       cout << i      <<  operations[i] << " " ;
      }
      cout << endl;
   }

};


class Expression{

  char * stroka;
  int size;
  double num[50];;
  char simbol[50];  
  
  public:
  Expression(const char * str) {
    size=0;
    stroka = new char[strlen(str)];
    strcpy(stroka,str);
    for (int i = 0; i < 50; i++){
      num[i] = 0;
      simbol[i] = 0;
    }
  }
  
  int  infics() {

     char * psb;
     psb = stroka;
     
     for (int i = 0; i < strlen(stroka); i++) {
      
      if ((stroka[i] <= '9') && (stroka[i] >= '0')){
        
        simbol[size] = 1;
        num[size++] = atof(stroka+i);
        psb = strpbrk (stroka+i, "+-*/^()");
        if (psb == NULL) break;
        else { 
          i=psb-stroka-1;
        }

      }
      else {
        simbol[size++] = stroka[i];
        if (stroka[i] != '+' && stroka[i] != '-' && stroka[i] != '*' && stroka[i] != '/' && stroka[i] != '(' && stroka[i] != ')' && stroka[i] != '^' ) return 1;
      }
     }
     return 0;
    }  

 
  void show() {

    for (int i = 0; i < size; ++i)
    {
      if (simbol[i] == 1){
        cout <<num[i] << " ";
      }
        else {
          cout << simbol[i] << " ";
        }
      
    }
    cout<<endl;

  }
  
  int postfics() {
     
      Operation_stack operation_stack;
      int j=0;
      for (int i = 0; i < size; i++) {
        
      if (simbol[i] == 1){
          simbol[j] = 1;
          num[j++]=num[i];
          continue;
      }

      if (operation_stack.get_size() == 0) { 
        operation_stack.Push_stack(simbol[i]); 
        continue; 
      } 
      if (simbol[i] == '(') { operation_stack.Push_stack(simbol[i]) ; continue; }
      
      if (simbol[i] == ')') {
        
        while (1) {
           if (operation_stack.get_size()==0) { return 1;}
           if (operation_stack.skobki()==1) { 
            operation_stack.Pop_stack();
            break;
          }
           simbol[j++] = operation_stack.Pop_stack();  
        } 

        continue;
      }
      if (operation_stack.skobki()==1) { 
        operation_stack.Push_stack(simbol[i]);
        continue;
      }
      if (operation_stack.Priority(simbol[i]) == 1 ) { 
          operation_stack.Push_stack(simbol[i]) ;
          continue;
          }
       else {

       simbol[j++] = operation_stack.Pop_stack();
       i--;
      }  
      }

    while(1) {
      
      if (operation_stack.get_size()==0) break;
      if (operation_stack.skobki()==1) return 1;
      simbol[j++]=operation_stack.Pop_stack();
    }
    size = j;
    return 0;
    }  
    
    double calculation(int* &stat) {
      *stat=0;
      for (int i = 2; i < size; ++i)
      {
      
        if (simbol[i] == 1) continue;
        if (simbol[i]== '+')  num[i] = num[i-1] + num[i-2];
        if (simbol[i]== '-')  num[i] = num[i-2] - num[i-1];
        if (simbol[i]== '*')  num[i] = num[i-1] * num[i-2];
        if (simbol[i]== '/')  num[i] = num[i-2] / num[i-1];
        if (simbol[i]== '^')  num[i] = pow(num[i-2], num[i-1]);
        simbol[i] = 1;
        for (i; i <size ; ++i)
        {
          
          num[i-2]=num[i];
          simbol[i-2]=simbol[i];
        }
        size = size - 2;
        i=1; 
      }
      return  num[0];
    }
};

double calc(const char * str, int * status) {

  Expression expression(str);
  if (expression.infics()==1){
    cout << "Error";
     *status=1;
     return 0.0;
  };
  if (expression.postfics() == 1) {
    cout << "Error" << endl;
    *status = 1;
    return 0.0;
  };      
  return expression.calculation(status);
   
 }
 
 
int main() {
  
  int * status;
  status = new int;
  double result = calc("2^2++(4*4+2)", status);
  cout << "result: " << result << endl;
  cout << *status << endl;
  return 0;

} 