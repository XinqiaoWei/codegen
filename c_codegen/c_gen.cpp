#include "ast.hpp"
#include "Parser.tab.h"
#include<iostream>
using namespace std;
Func_body_list *ast;

int main(){
	yyparse();
	retrun 0;
} 
