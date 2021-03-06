#ifndef ERRORCONTROL_H
#define ERRORCONTROL_H

#include "../../interface/inc/outputtabwidget.h"
#include "../../entity/inc/common_lib.h"
#include "../../interface/inc/inputwindow.h"

class MainWindow;

class ErrorControl
{
public:
    ErrorControl(OutputTabWidget* consoleTab, OutputTabWidget* errorTab);
    ~ErrorControl();

    void printToConsole(QString message);
    void printErrorMsg(ResultState result);
    void printErrorMsg(QString errorMsg);
    void printErrorMsgAtLine(ResultState result, int lineNum);
    int  getUserInput(QString variableName);

private:
    QString convertErrorMsg(ResultState result);
    OutputTabWidget* consoleTab;
    OutputTabWidget* errorTab;
};
#endif // ERRORCONTROL_H
