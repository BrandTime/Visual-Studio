/****************************************************/
/* File: parse.h                                    */
/* The parser interface for the TINY compiler       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _PARSE_H_
#define _PARSE_H_

#include"GLOBALS.H"
#include"SCAN.H"
#include"UTIL.H"

class Parser:public Scanner {
	static list<Token>::const_iterator curTokenPos;//holsd current token position
	static Token curToken; /* holds current token */

	//auxiliary function
	static Token getToken();
	/* function prototypes for recursive calls */
	static shared_ptr<TreeNode> stmt_sequence(void);
	static shared_ptr<TreeNode> statement(void);
	static shared_ptr<TreeNode> if_stmt(void);
	static shared_ptr<TreeNode> repeat_stmt(void);
	static shared_ptr<TreeNode> assign_stmt(void);
	static shared_ptr<TreeNode> read_stmt(void);
	static shared_ptr<TreeNode> write_stmt(void);
	static shared_ptr<TreeNode> exp(void);
	static shared_ptr<TreeNode> simple_exp(void);
	static shared_ptr<TreeNode> term(void);
	static shared_ptr<TreeNode> factor(void);
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
