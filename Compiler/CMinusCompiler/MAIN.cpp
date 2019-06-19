/****************************************************/
/* File: main.c                                     */
/* Main program for TINY compiler                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
//set NO_SCAN to TRUE to get a simple test program
#define NO_SCAN false
/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE false
/* set NO_ANALYZE to TRUE to get a parser-only compiler
can choose only one parser*/
#define NO_ANALYZE true
/* set NO_CODE to TRUE to get a compiler that does not
 * generate code
 */
#define NO_CODE true

#if !NO_SCAN
#include"CMinusScanner.h"
#if !NO_PARSE
#include "CMinusParser.h"
#if !NO_ANALYZE
#include "analyze.h"
#if !NO_CODE
#include "cgen.h"
#endif
#endif
#endif
#endif




fstream source;/* source code file name */
fstream tokens;//token output file name
ostream &listing=cout;
/* allocate and set tracing flags */
bool EchoSource = true;
bool TraceScan = true;
bool TraceParse = true;
bool TraceAnalyze = false;
bool TraceCode = false;
bool Error = false;

int main(){ 
	shared_ptr<TreeNode> syntaxTree;
	source.open("source.txt",ios::in);
	tokens.open("tokens.txt", ios::out);
	if (!source) {
		cerr << "Source file open fail!" << endl;
		cin.get();
		return -1;
	}
	if (!tokens) {
		cerr << "Tokens file open fail!" << endl;
		cin.get();
		return -1;
	}
	cout << endl<<"TINY COMPILATION: source.txt" << endl;
#if !NO_SCAN
	CMinusScanner::scan(source);
	CMinusScanner::print(tokens);
#if !NO_PARSE
	syntaxTree = CMinusParser::parse();
	if (TraceParse) {
		listing << endl << "Syntax tree: " << endl;
		printTree(syntaxTree, listing);
		listing << endl;
	}
#if !NO_ANALYZE
  if (! Error)
  { if (TraceAnalyze) fprintf(listing,"\nBuilding Symbol Table...\n");
    buildSymtab(syntaxTree);
    if (TraceAnalyze) fprintf(listing,"\nChecking Types...\n");
    typeCheck(syntaxTree);
    if (TraceAnalyze) fprintf(listing,"\nType Checking Finished\n");
  }
#if !NO_CODE
  if (! Error)
  { char * codefile;
    int fnlen = strcspn(pgm,".");
    codefile = (char *) calloc(fnlen+4, sizeof(char));
    strncpy(codefile,pgm,fnlen);
    strcat(codefile,".tm");
    code = fopen(codefile,"w");
    if (code == NULL)
    { printf("Unable to open %s\n",codefile);
      exit(1);
    }
    codeGen(syntaxTree,codefile);
    fclose(code);
  }
#endif
#endif
#endif
#endif
	source.close();
	tokens.close();

	system("pause");
	return 0;
}

