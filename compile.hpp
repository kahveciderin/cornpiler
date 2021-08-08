#pragma once

#include <cstdint>
#include <string>
#include <vector>

#define DEBUG

bool check_id_constraints(std::string id, char c);

#ifdef DEBUG
std::string DEBUG_TOKEN_TYPES[] = {"str", "identifier", "number", "bracket", "semi", "sep", "sym"};
#endif

enum token_type {
  string,
  identifier,
  number,
  bracket,
  semi,
  sep,
  sym
};

enum act_type {
  error,
  statement,
  statement_with_body,
  statement_with_two_bodies,
  varop,
  vardef,
  type,
  fundef,
  extdef,
  glbdef,
  call,
  varset,
  getvar,
  const_str,
  const_number,
  oper,
  expr,
  arrset,
  arrget,
  outtype
};

class token {
 public:
  token_type type;
  std::string value;
  token(token_type t, std::string v) { // god forgive me for writing a function inside a header file
    type = t;
    value = v;
  }
};

std::vector<token> tokenize_program(std::string program, int length);

class AST {
  act_type act;
};

class ast_body {
 public:
  std::vector<AST*> body;
};

namespace ast_types {

class statement : AST {
 public:
  std::string name;
  ast_body args;
};
class statement_with_body : statement {
 public:
  ast_body body;
};
class statement_with_two_bodies : statement_with_body {
 public:
  ast_body second_body;
};

class varop : AST {
 public:
  std::string name;
  std::string var;
};

class vardef : AST {
 public:
  std::string name;
  ast_body args;
  ast_body type;
};

class type : AST {
 public:
  std::string type;
};

class out_type : AST {
 public:
  std::string name;
  ast_body type;
};

class extdef : AST {
 public:
  std::string name;
  ast_body args;
  ast_body return_type;
};

class fundef : AST {
 public:
  std::string name;
  ast_body args;
  ast_body return_type;
  ast_body body;
};

class glbdef : vardef {
};

class call : AST {
 public:
  std::string name;
  ast_body args;
};

class varset : AST {
 public:
  std::string name;
  ast_body args;
};

class getvar : AST {
 public:
  std::string name;
};

class const_str : AST {
 public:
  std::string value;
};

class const_int : AST {
 public:
  int value;
};

class oper : AST {
 public:
  char op;
  AST args[2];
};

class expr : AST {
 public:
  AST arg;
};

class arrset : AST {
 public:
  ast_body args;
};

class arrget : AST {
 public:
  AST index;
  AST array;
};
}  // namespace ast_types