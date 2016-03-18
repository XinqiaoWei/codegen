#ifndef p_ast_hpp
#define p_ast_hpp

#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

extern  vector<  map< string, int> >var_stack;


//A parent class Value, classes like number, operaor, id, will be the kids
class Value{
public:
    virtual ~Value()
    {}
    
    //Virtual functions will be implemented in kid classes
    virtual int get_val_num(){ cout<<"Something goes wrong"<< endl; return 2;}
    virtual  string get_val(){ return "Something goes wrong";}
    virtual void to_MIPS(){ cout<<"Something goes wrong"<< endl;}
};

class FUNC{};
//Expression
class  Expression : public Value{
private:
     vector<Value*> entry;
    int bracket;
    bool single;
public:
     Expression():single(false){}
    
    void Add(Value* op1, Value* opr, Value* op2){
        entry.push_back(op1);
        entry.push_back(opr);
        entry.push_back(op2);
        single = false;
    }
    
    void Add(Value* op1){
        entry.push_back(op1);
        single = true;
    }
    
    void to_MIPS(){
        //Return the numerical results
        if(single){
            cout<<" # _tmp0 = a\n   lw $t2, 4($fp)"<<endl;
        }else{
            if(entry[1]->get_val() == "+"){
                cout<<" # _tmp0 = a + b\n   lw $t0, 4($fp)\n    lw $t1, 8($fp)\n    add $t2, $t0, $t1"<<endl;
            }else if(entry[1]->get_val() == "-"){
                cout<<" # _tmp0 = a - b\n   lw $t0, 4($fp)\n    lw $t1, 8($fp)\n    sub $t2, $t0, $t1"<<endl;
            }else if(entry[1]->get_val() == "*"){
                cout<<" # _tmp0 = a * b\n   lw $t0, 4($fp)\n    lw $t1, 8($fp)\n    mult $t0, $t1\n     mflo $t2"<<endl;
            }else{
                cout<<" # _tmp0 = a * b\n   lw $t0, 4($fp)\n    lw $t1, 8($fp)\n    div $t0, $t1\n     mflo $t2"<<endl;
            }
        }
    }

};


//NUMBER
class Number : public Value{
private:
    double value;
    
public:
    Number(double _value) : value(_value){}
    
    int get_val_num(){
        return value;
    }
    
};

//OPERATOR
class Optr : public Value{
private:
    string op;
public:
    Optr( string _value) : op(_value){}
    string get_val(){ return op;}
    
};

//ID_list
class Id_list : public Value{
private:
    vector< string> idlist;
    string type;
public:
    void Add( string id){
        idlist.push_back(id);
    }
    
    void Add_type( string tp){type = tp;}
    
    string get_id(int i){ return idlist[i];}
    
    int get_size(){ return idlist.size(); }
    
    string get_type(){return type;}
    
    
};



//Argument
class Argument {
private:
    static  vector< string> value;
    string current_value;
    static  vector< string> type;
    string current_type;

public:
    Argument(){}
    
    Argument( string _value){
        bool semicn = false;
        value.push_back(_value);
        current_value = _value;
        
    }
    
    void Add_type( string _type){
        type.push_back(_type);
        current_type = _type;
    }

};



//A parent class Function_body, classes like statement will be the kids
class Func_body{
public:
    virtual ~Func_body(){}
    
    //Virtual functions will be implemented in kid classes
    virtual  vector< string> get_val_list(){ vector< string> foo; return foo;}
    virtual  vector< string> get_type_list(){  vector< string> foo; return foo;}

    
};

//Variable
class Var : public Value, public Func_body{
private:
    static  vector< string> value;
     string current_value;
    static  vector< string> type;
     string current_type;
    bool semicn;
    bool defined;
public:
    
    Var(){}
    
    Var( string _value){
        semicn = false;
        value.push_back(_value);
        current_value = _value;
        
    }
    
    //Add the type for a variable
    void Add_type( string _type){
        type.push_back(_type);
        current_type = _type;
    }
    
    //For those variables which has either been divided before or caused undefined problems
    Var( string _value, bool df){
        semicn = false;
        defined = df;
        value.push_back(_value);
        current_value = _value;
        type.push_back("NotaType");
        
    }
    
    
    //Return the numerical results of variables
    int get_val_num(){
        typedef  vector<  map< string, int> >  vec_map;
        typedef  map< string, int> map_v;
        vec_map::const_iterator vit;
        for(vit=var_stack.begin(); vit!=var_stack.end(); ++vit){
            map_v::const_iterator it = vit->begin();
            if(current_value == it->first){
                return it->second;
            }
        }
        return 0;
    }
    
    void Add_semi(){semicn = true; }
    
    //Add a lists of variables of same data_type e.g: int a, b, c;
    void Add_id(Id_list* idlist){
        for(int i=0; i<idlist->get_size(); i++){
            value.push_back(idlist->get_id(i));
            type.push_back(idlist->get_type());
        }
    }
    
     vector< string> get_val_list() {return value;}
     vector< string> get_type_list() {return type;}
    
     string get_val(){
        return current_value;
    }
    
     string get_type(){
        return current_type;
    }
    
};

//STATEMENT
class Statement : public Func_body{
private:
    typedef  map< string, Value*> map_s;
     map< string, Value*> stment;
    Var* variable;
    Value* expression;
    bool declaration;
     map< string, int> variables_stack;   //variables in the stack, stored in forms of "a, 3", "b, 5"
    int index;       //Index used in the stack, indexes are in times of 4
public:
    Statement(): declaration(false){}
    
    void Add(Var* var, Value* expr){
         string temp = var->get_val();
        stment[temp] = expr;
        expression = expr;
        variable = var;
        cout<<"#"+temp+" = _tmp0\n  move $t3, $t2"<<endl;
    }
    
    void Add(Var* var){
        variable = var;
        declaration = true;
    }
};

//STATEMENT_list
class Statement_list : public Func_body {
private:
     vector<Statement*> st_list;
    
public:
    Statement_list(){}
    void Add(Statement* statement){
        st_list.push_back(statement);
    }
    
    void to_MIPS(){
        cout<<"     move $v0, $sp\n     move $sp, $fp\n    lw $ra, -4($fp)\n    lw $fp, 0($fp)\n    jr $ra"<<endl;
    }
    

};



//The toplevel class, the top level class
class Func_body_list : public Func_body{
private:
     vector<Func_body*> fc_list;
    Var* variable;
     string return_value;
    
public:
    
    void Add(Func_body* f){
        fc_list.push_back(f);
    }
    
    void set_return( string rt){return_value = rt;}
    
    
};

#endif

