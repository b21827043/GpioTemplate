#include "gpio.h"

Gpio::Gpio(QObject *parent) : QThread(parent)
{
    dataModel = DataModel::getInstance();
}

int Gpio::readGPIO(QString pinPath)
{
    QFile gpioFile(pinPath);
    if (!gpioFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open GPIO pin" << pinPath;
    }

    // Read the GPIO value
    char buttonValue;
    gpioFile.read(&buttonValue, 1);

    // Close the GPIO file
    gpioFile.close();
    QString strValue(buttonValue);
    int button = strValue.toInt();
    //  qDebug()<< "Button=" <<Button;
    return button;
}

void Gpio::run()
{
    bool upButtonPrevState = true;
    bool downButtonPrevState = true;
    bool leftButtonPrevState = true;
    bool rightButtonPrevState = true;
    bool okButtonPrevState = true;
    bool triggerButtonPrevState = true;

    while (1)
    {
        upButton = readGPIO(pathUpButton);
        downButton = readGPIO(pathDownButton);
        leftButton = readGPIO(pathLeftButton);
        rightButton = readGPIO(pathRightButton);
        okButton = readGPIO(pathOkButton);
        triggerButton = readGPIO(pathTriggerButton);

        if (upButton != upButtonPrevState && upButton == 0)
        {
            emit upPressed();
        }
        if (downButton != downButtonPrevState && downButton == 0)
        {
            emit downPressed();
        }
        if (leftButton != leftButtonPrevState && leftButton == 0)
        {
            emit leftPressed();
        }
        if (rightButton != rightButtonPrevState && rightButton == 0)
        {
            emit rightPressed();
        }
        if (okButton != okButtonPrevState && okButton == 0)
        {
            emit okPressed();
        }
        if (triggerButton != triggerButtonPrevState && triggerButton == 0)
        {
            emit triggerPressed();
        }

        upButtonPrevState = upButton;
        downButtonPrevState = downButton;
        leftButtonPrevState = leftButton;
        rightButtonPrevState = rightButton;
        okButtonPrevState = okButton;
        triggerButtonPrevState = triggerButton;

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

Gpio::~Gpio()
{
}
