#include <QString>
#include <QtTest>

class KIrcTestTest : public QObject
{
    Q_OBJECT

public:
    KIrcTestTest();

private Q_SLOTS:
    void testCase1();
};

KIrcTestTest::KIrcTestTest()
{
}

void KIrcTestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(KIrcTestTest)

#include "tst_kirctesttest.moc"
