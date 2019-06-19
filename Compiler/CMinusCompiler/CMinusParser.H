/****************************************************/
/* File: parse.h                                    */
/* The parser interface for the TINY compiler       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _PARSE_H_
#define _PARSE_H_

#include"GLOBALS.H"
#include"CMinusScanner.H"
#include"UTIL.H"

class CMinusParser:public CMinusScanner {
	static list<Token>::const_iterator curTokenPos;//holsd current token position
	static Token curToken; /* holds current token */

	//auxiliary function
	static Token getToken();
	/* function prototypes for recursive calls */
	static shared_ptr<TreeNode> program();
	static shared_ptr<TreeNode> declaration_list();
	static shared_ptr<TreeNode> declaration();
	static shared_ptr<TreeNode> var_declaration();
	static shared_ptr<TreeNode> fun_declaration();
	static shared_ptr<TreeNode> params();		
	static shared_ptr<TreeNode> compound_stmt();
	static shared_ptr<TreeNode> local_declarations();
	static shared_ptr<TreeNode> read_stmt();		
	static shared_ptr<TreeNode> write_stmt();		
	static shared_ptr<TreeNode> expression_stmt();
	static shared_ptr<TreeNode> subcompound_stmt();
	static shared_ptr<TreeNode> if_stmt();
	static shared_ptr<TreeNode> while_stmt();
	static shared_ptr<TreeNode> return_stmt();
	static shared_ptr<TreeNode> expression();
	static shared_ptr<TreeNode> simple_expression();
	static shared_ptr<TreeNode> additive_expression();
	static shared_ptr<TreeNode> term();
	static shared_ptr<TreeNode> factor();
	static shared_ptr<TreeNode> var();
	static shared_ptr<TreeNode> call();
	static shared_ptr<TreeNode> args();

	static void match(TokenType expected);
protected://for further compile

public:
	/* Function parse returns the newly
	* constructed syntax tree
	*/
	static shared_ptr<TreeNode> parse(void);
	static void syntaxError(const string&,ostream&);
};
#endif
