#include "controller.h"

controller::controller(QObject *parent) : QObject(parent)
{
    readDatafromJson();
}

void controller::readDatafromJson()
{
    QFile file(":/Data/data.json");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Không thể mở tệp JSON";
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if (jsonDoc.isNull()) {
        qDebug() << "Không thể phân tích JSON";
    }

    QJsonObject jsonObject = jsonDoc.object();

    m_sinhvienArray = jsonObject["sinhvien"].toArray();

    foreach(const QJsonValue &value, m_sinhvienArray){
        sinhvien s;
        s.name = value.toObject()["Name"].toString();
        s.lastname = value.toObject()["lastName"].toString();
        m_listSV.append(s);
    }

    m_name = m_sinhvienArray[0].toObject()["Name"].toString();
}

QString controller::name()
{
    return m_name;
}

void controller::setName(QString name)
{
    if (m_name == name) return;
    m_name = name;
    emit nameChanged();
}

void controller::setNamefromUI(int index, QString name)
{
    setName(name);
    m_listSV[index].name = name;
    foreach(const sinhvien &value, m_listSV){
        qDebug() << value.name << " - " << value.lastname;
    }
}

int controller::getLength()
{
    return m_listSV.length();
}

QVariantMap controller::getData(int index) const {
    QVariantMap itemMap;
    if (index >= 0 && index < m_listSV.size()) {
        const sinhvien &item = m_listSV[index];
        itemMap["name"] = item.name;
        itemMap["lastname"] = item.lastname;
    }
    return itemMap;

}

void controller::addSV(QString name, QString lastname)
{
    m_listSV.append(sinhvien(name, lastname));
    qDebug() << m_listSV.length();
    addSVjson();
}

void controller::addSVjson()
{
        QJsonObject jsonObject;

        QJsonArray sinhvienArray;

        QJsonObject sinhvien;
        sinhvien["Name"] = "A";
        sinhvien["lastName"] = "Nguyễn";

        sinhvienArray.append(sinhvien);

        jsonObject["sinhvien"] = sinhvienArray;

        QJsonDocument jsonDoc(jsonObject);

        QFile file(":/Data/data.json");

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Không thể mở tệp JSON";
            return;
        }

        file.write(jsonDoc.toJson());

        file.close();
}
