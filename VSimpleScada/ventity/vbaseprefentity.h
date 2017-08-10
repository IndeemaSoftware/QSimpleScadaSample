#ifndef BASEPREFENTITY_H
#define BASEPREFENTITY_H

#include <QObject>
#include <QXmlStreamReader>

class VBasePrefEntity : public QObject
{
    Q_OBJECT
public:
    explicit VBasePrefEntity(QObject *parent = 0);

signals:

public slots:

    virtual void initFromXml(const QByteArray &xmlData) = 0;

    virtual void saveXmlToFile(const QString &filePath) = 0;

};

#endif // BASEPREFENTITY_H
