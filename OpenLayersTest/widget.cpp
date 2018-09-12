#include "widget.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QButtonGroup>
#include <QWebFrame>
#include <QWebView>
#include <QLabel>
#include <QMouseEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_pWebView = new QWebView;
    m_pWebView->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    QFileInfo file("./js/openlayer.html");
    m_pWebView->setUrl(QUrl::fromLocalFile(file.absoluteFilePath()));

    //右边布局
    QVBoxLayout *l_pVBoxLayout = new QVBoxLayout;
    l_pVBoxLayout->addWidget(CreateLayerSelect());
    l_pVBoxLayout->addStretch();

    QHBoxLayout *l_pHBoxLayout = new QHBoxLayout;
    l_pHBoxLayout->addWidget(m_pWebView);
    l_pHBoxLayout->addLayout(l_pVBoxLayout);

    m_pStatusLabel = new QLabel;
    QVBoxLayout *l_pMainLayout = new QVBoxLayout;
    l_pMainLayout->addLayout(l_pHBoxLayout);
    l_pMainLayout->addWidget(m_pStatusLabel);
    setLayout(l_pMainLayout);

    setMouseTracking(true);
}

Widget::~Widget()
{

}

QGroupBox *Widget::CreateLayerSelect()
{
    QGroupBox *l_pGroupBox = new QGroupBox("图层选择");
    l_pGroupBox->setFixedWidth(200);
    QVBoxLayout *l_pVBoxLayout = new QVBoxLayout;
    m_pLayerBtnGroup = new QButtonGroup;
    m_pLayerBtnGroup->setExclusive(false);
    connect(m_pLayerBtnGroup, SIGNAL(buttonClicked(int)), this, SLOT(SlotLayerSelect(int)));

    QStringList list;
    list<<"地形"<<"地名";
    for (int i = 0; i < list.size(); ++i)
    {
        QCheckBox *checkBox = new QCheckBox(list.at(i));
        checkBox->setChecked(true);
        l_pVBoxLayout->addWidget(checkBox);
        m_pLayerBtnGroup->addButton(checkBox, i);
    }

    l_pGroupBox->setLayout(l_pVBoxLayout);
    return l_pGroupBox;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    double lon = event->pos().x();
    double lat = event->pos().y();
    QString text;
    text.sprintf("Lon = %.4f, Lat = %.4f", lon, lat);
    m_pStatusLabel->setText(text);
}

void Widget::UpdateStatusLabel()
{
    double lon;
    double lat;
    QString text;
    text.sprintf("Lon = %.4f, Lat = %.4f", lon, lat);
    m_pStatusLabel->setText(text);
}

void Widget::SlotLayerSelect(int id)
{
    bool checked = m_pLayerBtnGroup->button(id)->isChecked();
    if (id == 0)
    {
        m_pWebView->page()->mainFrame()->evaluateJavaScript(QString("checkTerrain(%1)").arg(checked));
    }
    else if (id == 1)
    {
        m_pWebView->page()->mainFrame()->evaluateJavaScript(QString("checkOverlay(%1)").arg(checked));
    }
}
