#ifndef PROGRAM_H
#define PROGRAM_H

#include "common_lib.h"
#include "identifier.h"
#include "statement.h"
#include "../stmts/inc/addStmt.h"
#include "../stmts/inc/compStmt.h"
#include "../stmts/inc/declArrStmt.h"
#include "../stmts/inc/declIntStmt.h"
#include "../stmts/inc/endStmt.h"
#include "../stmts/inc/jEqStmt.h"
#include "../stmts/inc/jLessStmt.h"
#include "../stmts/inc/jMoreStmt.h"
#include "../stmts/inc/jumpStmt.h"
#include "../stmts/inc/movStmt.h"
#include "../stmts/inc/printStmt.h"
#include "../stmts/inc/readStmt.h"
#include "../../control/inc/errorControl.h"

class Program
{

public:
    Program(QString programPath, OutputTabWidget* consoleTab, OutputTabWidget* errorTab);
    ~Program();
    ResultState save();
    ResultState compile();
    ResultState run();

private:
    ErrorControl* errorControl;

    QString pgmName;
    QString pgmPath;
    qint16  numStmt;
    qint16  numLabel;
    qint16  numJumpStmt;
    Identifier* ids[MAX_VALUE_16];
    Statement*  statements[MAX_VALUE_16];
    Statement*  jumpStmts[MAX_VALUE_16];

    bool hasEnd;

    // helper functions
    ResultState addStmt(QString stmt, qint16 lineNum);
    StatementId getStmtId(QString ins);
    bool isEndStmt(Statement* stmt);
    bool isJumpStmt(Statement* stmt);
};

#endif

