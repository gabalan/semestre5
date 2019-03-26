#include <QString>
#include <QtTest>

class ddd : public QObject
{
    Q_OBJECT

public:
    ddd();

private Q_SLOTS:
    void testCase1();
};

ddd::ddd()
{
}

void ddd::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(ddd)

#include "tst_ddd.moc"
