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
    void CursorNewLine();
    void CursorUp(int n = 1);
    void CursorDown(int n = 1);
    void CursorLeft(int n = 1);
    void CursorRight(int n = 1);
    void CursorHome(int row = 0, int column = 0);

public:
    QColor GetColor(int c);

    void DisplayReset();
    void DisplayForeground(QColor &color);
    void DisplayBackground(QColor &color);

public:
    void EraseEndOfLine();
    void EraseStartOfLine();
    void EraseEntireLine();
    void EraseDown();
    void EraseUp();
    void EraseScreen();

public:
    void SelectRight(int n = 1);
};

#endif // QTERMSCREEN_H
