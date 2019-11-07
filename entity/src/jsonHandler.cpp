#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

#include "../inc/jsonHandler.h"

JsonHandler::JsonHandler()
{
    m_currentFile = "";
    m_currentJsonObject = getJsonFromStr("{}");
    m_currentResultState = ResultState::NO_ERROR;
}

JsonHandler::JsonHandler(QString fileName)
{
    m_currentFile = fileName;
    m_currentJsonObject = getJsonFromStr("{}");
    m_currentResultState = ResultState::NO_ERROR;
}

void JsonHandler::setFileName(QString fileName)
{
    m_currentFile = fileName;
}

QJsonObject JsonHandler::getJsonFromStr(QString jsonString)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}

QJsonObject JsonHandler::findLabel(QString labelName)
{
    readData();
    if (m_currentResultState == ResultState::NO_ERROR) {
        if (m_currentJsonObject.contains("label") && m_currentJsonObject["label"].isArray()) {
            QJsonArray labelArray = m_currentJsonObject["label"].toArray();
            for (int labelIndex = 0; labelIndex < labelArray.size(); ++labelIndex) {
                QJsonObject labelObject = labelArray[labelIndex].toObject();
                if (labelObject["name"].toString() == labelName) {
                    return labelObject;
                }
            }
        }
    }
    return getJsonFromStr("{}");
}

QJsonObject JsonHandler::findVariable(QString variableName, TypeE type)
{
    readData();
    if (m_currentResultState == ResultState::NO_ERROR) {
        if (m_currentJsonObject.contains("variable") && m_currentJsonObject["variable"].isArray()) {
            QJsonArray variableArray = m_currentJsonObject["variable"].toArray();
            for (int variableIndex = 0; variableIndex < variableArray.size(); ++variableIndex) {
                QJsonObject variableObject = variableArray[variableIndex].toObject();
                if (variableObject["name"].toString() == variableName && variableObject["type"].toInt() == static_cast<int>(type)) {
                    return variableObject;
                }
            }
        }
    }
    return getJsonFromStr("{}");
}

ResultState JsonHandler::addElement(QString elementName, QJsonObject aQJsonObject)
{
    readData();
    if (m_currentResultState != ResultState::NO_ERROR) {
        return m_currentResultState;
    }
    QJsonArray variableArray;
    if (m_currentJsonObject.contains(elementName)){ //&& m_currentJsonObject[elementName].isArray()) {
        variableArray = m_currentJsonObject[elementName].toArray();
    }
    variableArray.push_back(aQJsonObject);
    m_currentJsonObject[elementName] = variableArray;
    writeData();
    return m_currentResultState;
}

ResultState JsonHandler::readData()
{
    QString source;
    QFile file;
    file.setFileName(m_currentFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_currentResultState = ResultState::FILE_OPEN_ERROR;
        return m_currentResultState;
    }
    source = file.readAll();
    file.close();
    QJsonDocument data = QJsonDocument::fromJson(source.toUtf8());
    m_currentJsonObject = data.object();
    return m_currentResultState;
}

ResultState JsonHandler::writeData()
{
    QString source;
    QFile file;
    file.setFileName(m_currentFile);
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        m_currentResultState = ResultState::FILE_OPEN_ERROR;
        return m_currentResultState;
    }
    QJsonDocument aQJsonDocument;
    aQJsonDocument.setObject(m_currentJsonObject);
    file.write(aQJsonDocument.toJson());
    file.close();
    return m_currentResultState;
}
