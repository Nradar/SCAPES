#include "../inc/jEqStmt.h"

JEqStmt::JEqStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) : Statement(pgmName, stmt, idsLib, lnNum){}

JEqStmt::~JEqStmt()
{
    delete (op1.getIdentifier());
}

ResultState JEqStmt::compile()
{
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 2){ // syntax checking
        if(args.size() == 1){
            return NO_OPERAND_ONE_ERROR;
        }
        else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    JsonHandler jsonHdlr(this->programName);
    QString instruction = args[0];
    QString operand1 = args[1];

    QMap<QString, std::shared_ptr<Identifier>>::iterator foundLabel = ids.find(operand1);
    // Label not found
    if(foundLabel == ids.end()){
        return LABEL_NOT_FOUND_ERROR;
    }
    if (dynamic_cast<Label*>(foundLabel->get()))
        op1.setIdentifier(foundLabel.value().get());
    else
        return DIFF_TYPE_ERROR;

    // add to JSON
    QJsonObject op1Obj = JsonHandler::getJsonObj(OP_1, operand1);
    QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    return NO_ERROR;
}

ReturnValue* JEqStmt::run()
{
    Label* aLabel = dynamic_cast<Label*>(op1.getIdentifier());
    int lineNum = aLabel->getLineNum();

    return new ReturnValue(NO_ERROR, lineNum);
}
