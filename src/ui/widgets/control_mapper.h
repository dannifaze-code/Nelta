#ifndef CONTROL_MAPPER_H
#define CONTROL_MAPPER_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMap>

class ControlMapper : public QWidget {
    Q_OBJECT

public:
    ControlMapper(QWidget *parent = nullptr);

private:
    void createUI();
    void mapButton(int buttonId);

    QVBoxLayout *layout;
    QMap<int, QPushButton*> buttonMap;
};

#endif // CONTROL_MAPPER_H
