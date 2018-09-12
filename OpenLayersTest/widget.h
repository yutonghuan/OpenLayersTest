#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QGroupBox;
class QWebView;
class QButtonGroup;
class QLabel;

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

    QGroupBox *CreateLayerSelect();//图层选择

protected:
    void mouseMoveEvent(QMouseEvent *);

private:
    void UpdateStatusLabel();

private slots:
    void SlotLayerSelect(int id);

private:
    QWebView *m_pWebView;
    QButtonGroup *m_pLayerBtnGroup;
    QLabel *m_pStatusLabel;
};

#endif // WIDGET_H
