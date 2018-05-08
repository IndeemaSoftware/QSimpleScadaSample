#include "qscadadeviceinfo.h"

void VDeviceInfo::init(VDeviceInfo *deviceInfo)
{
    setName(deviceInfo->name());
    setType(deviceInfo->type());
    setDomain(deviceInfo->domain());
    setHost(deviceInfo->host());
    setIp(deviceInfo->ip());
    setIpv6(deviceInfo->ipv6());
    setInterfaceIndex(deviceInfo->interfaceIndex());
    setPort(deviceInfo->port());
    setDeviceStatus(VStatusGray);
    setUnitCount(0);
}

QString VDeviceInfo::name() const
{
    return mName;
}

void VDeviceInfo::setName(const QString &name)
{
    mName = name;
}

QString VDeviceInfo::type() const
{
    return mType;
}

void VDeviceInfo::setType(const QString &type)
{
    mType = type;
}

QString VDeviceInfo::domain() const
{
    return mDomain;
}

void VDeviceInfo::setDomain(const QString &domain)
{
    mDomain = domain;
}

QString VDeviceInfo::host() const
{
    return mHost;
}

void VDeviceInfo::setHost(const QString &host)
{
    mHost = host;
}

QHostAddress VDeviceInfo::ip() const
{
    return mIp;
}

void VDeviceInfo::setIp(const QHostAddress &ip)
{
    mIp = ip;
}

QHostAddress VDeviceInfo::ipv6() const
{
    return mIpv6;
}

void VDeviceInfo::setIpv6(const QHostAddress &ipv6)
{
    mIpv6 = ipv6;
}

quint32 VDeviceInfo::interfaceIndex() const
{
    return mInterfaceIndex;
}

void VDeviceInfo::setInterfaceIndex(const quint32 &interfaceIndex)
{
    mInterfaceIndex = interfaceIndex;
}

quint16 VDeviceInfo::port() const
{
    return mPort;
}

void VDeviceInfo::setPort(const quint16 &port)
{
    mPort = port;
}

bool VDeviceInfo::operator ==(const VDeviceInfo &other)
{
    return mName == other.mName && mType == other.mType && mHost == other.mHost &&
            mInterfaceIndex == other.mInterfaceIndex && mIp == other.mIp && mIpv6 == other.mIpv6 && mDomain == other.mDomain &&
            mHost == other.mHost && mDeviceStatus == other.mDeviceStatus && mUnitCount == other.mUnitCount;
}

VStatus VDeviceInfo::deviceStatus() const
{
    return mDeviceStatus;
}

void VDeviceInfo::setDeviceStatus(const VStatus &deviceStatus)
{
    mDeviceStatus = deviceStatus;
}

int VDeviceInfo::unitCount() const
{
    return mUnitCount;
}

void VDeviceInfo::setUnitCount(int unitCount)
{
    mUnitCount = unitCount;
}

bool VDeviceInfo::operator<(const VDeviceInfo &deviceInfo)
{
    QString lName = name().remove(" ");
    QString rName = deviceInfo.name().remove(" ");
    bool rValue = lName.compare(rName, Qt::CaseInsensitive) < 0 ? true : false;

    return rValue;
}
