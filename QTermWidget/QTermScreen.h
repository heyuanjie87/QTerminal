#ifndef QTERMSCREEN_H
#define QTERMSCREEN_H

#include <QPlainTextEdit>

class QTermScreen : public QPlainTextEdit
{
    Q_OBJECT

public:
    QTermScreen(QWidget *parent = Q_NULLPTR);

public:
    void CursorStartOfLine();
    void CursorNewLine(int n = 1);
    void CursorUp(int n = 1);
    void CursorDown(int n = 1);
    void CursorLeft(int n = 1);
    void CursorRight(int n = 1);
    void CursorPosition(int row = 1, int column = 1);
    void CursorHorizontal(int pos);

public:
    QColor GetColor(int c);

    void DisplayReset();
    void DisplayForeground(QColor &color);
    void DisplayBackground(QColor &color);
    void DisplayColor(QColor &b, QColor &f);

public:
    void EraseEndOfLine();
    void EraseStartOfLine();
    void EraseEntireLine();
    void EraseDown();
    void EraseUp();
    void EraseScreen();

public:
    void SelectRight(int n = 1);
    QByteArray GetLine(int n = -1);

private:
    QColor bcolor;
    QColor fcolor;
};

#endif // QTERMSCREEN_H
