#ifndef STMT
#define STMT

#include "Lexer.h";
#include "Expr.h";
#include <vector>

using std::vector;

namespace Stmt {

class Stmt {                       
                            
};

class Class: public Stmt {       
    Class(Token name,                     
          Decl::Variable superclass,       
          vector<Stmt::Function> methods) {  
      this.name = name;                   
      this.superclass = superclass;       
      this.methods = methods;             
    }

    template<typename R> R accept(Visitor<R> visitor) {    
      return visitor.visitClassStmt(this);
    }                                     

    Token name;                     
    Expr.Variable superclass;       
    List<Stmt.Function> methods;    
  }   
}

  #endif