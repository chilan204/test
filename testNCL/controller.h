#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

struct sinhvien {
    QString name;
    QString lastname;

    sinhvien(){};
    sinhvien(QString addname, QString addlastname){
        name = addname;
        lastname = addlastname;
    };
};

class controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name     READ name   WRITE setName   NOTIFY nameChanged)

public:
    explicit controller(QObject *parent = 0);

    void readDatafromJson();

    QString name();
    void setName(QString name);

    Q_INVOKABLE void setNamefromUI(int index, QString lastname);
    Q_INVOKABLE int getLength();
    Q_INVOKABLE QVariantMap getData(int index) const;
    Q_INVOKABLE void addSV(QString name, QString lastname);

    void addSVjson();

signals:
    void nameChanged();

private:
    QList <sinhvien> m_listSV;
    QJsonArray m_sinhvienArray;
    QString m_name;
};

#endif // CONTROLLER_H
