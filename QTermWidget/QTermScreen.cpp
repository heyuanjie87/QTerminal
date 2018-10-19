#include "QTermScreen.h"

#include <QTextCursor>
#include <QTextBlock>

QTermScreen::QTermScreen(QWidget *parent):
    QPlainTextEdit(parent)
{
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::white);
    setPalette(p);
    setLineWrapMode(NoWrap);

    bcolor = p.color(QPalette::Base);
    fcolor = p.color(QPalette::Text);
}

void QTermScreen::CursorStartOfLine()
{
    QTextCursor tc = textCursor();

    tc.movePosition(QTextCursor::StartOfBlock);
    setTextCursor(tc);
}

void QTermScreen::CursorNewLine(int n)
{
    QTextCursor tc = textCursor();

    do
    {
        tc.movePosition(QTextCursor::EndOfBlock);

        if (tc.atEnd())
        {
            tc.insertBlock();
        }
        else
        {
            tc.movePosition(QTextCursor::NextBlock);
        }

        n --;
    }while (n > 0);

    setTextCursor(tc);

    DisplayColor(bcolor, fcolor);
}

void QTermScreen::SelectRight(int n)
{
    QTextCursor tc = textCursor();
    int endpos, pos;
    QTextCursor tcend = textCursor();

    tcend.movePosition(QTextCursor::EndOfBlock);
    endpos = tcend.position();
    pos = tc.position();
    if (pos + n > endpos)
    {
        n = endpos - pos;
    }
    if (n > 0)
    {
        tc.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, n);
        setTextCursor(tc);
    }
}

void QTermScreen::CursorUp(int n)
{
    QTextCursor tc = textCursor();

    tc.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, n);
    setTextCursor(tc);
}

void QTermScreen::CursorDown(int n)
{
    QTextCursor tc = textCursor();

    tc.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, n);
    setTextCursor(tc);
}

void QTermScreen::CursorLeft(int n)
{
    QTextCursor tc = textCursor();

    tc.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, n);
    setTextCursor(tc);
}

void QTermScreen::CursorRight(int n)
{
    QTextCursor tc = textCursor();

    tc.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, n);
    setTextCursor(tc);
}

void QTermScreen::CursorPosition(int row, int column)
{
    QTextCursor tc;
    int lines;

    moveCursor(QTextCursor::End);
    tc = cursorForPosition(QPoint(0, 0));
    lines = tc.document()->blockCount();

    for (int i = 1; i < row; i ++)
    {
        if (lines == 0)
        {
            tc.movePosition(QTextCursor::EndOfBlock);
            tc.insertBlock();
        }
        else
        {
            tc.movePosition(QTextCursor::NextBlock);
            lines --;
        }
    }

    for (int i = 1; i < column; i ++)
    {
        tc.movePosition(QTextCursor::Right);
    }

    setTextCursor(tc);
}

void QTermScreen::CursorHorizontal(int pos)
{
    QTextCursor tc = textCursor();
    int cp;

    tc.movePosition(QTextCursor::End);
    cp = tc.positionInBlock();
    if (pos > cp)
    {
        QString space(pos - cp - 1, ' ');

        setTextCursor(tc);
        insertPlainText(space);
    }
    else
    {
        tc.movePosition(QTextCursor::Start);
        tc.setPosition(pos);
        setTextCursor(tc);
    }
}

void QTermScreen::DisplayForeground(QColor &color)
{
    QTextCharFormat fmt;
    QTextCursor cursor = textCursor();

    fmt = cursor.charFormat();
    fmt.setForeground(color);

    cursor.setCharFormat(fmt);
    setTextCursor(cursor);

    fcolor = color;
}

void QTermScreen::DisplayBackground(QColor &color)
{
    QTextCharFormat fmt;
    QTextCursor cursor = textCursor();

    fmt = cursor.charFormat();
    fmt.setBackground(color);

    cursor.setCharFormat(fmt);
    setTextCursor(cursor);

    bcolor = color;
}

void QTermScreen::DisplayColor(QColor &b, QColor &f)
{
    QTextCharFormat fmt;

    fmt.setBackground(b);
    fmt.setForeground(f);
    QTextCursor cursor = textCursor();
    cursor.mergeCharFormat(fmt);
    setTextCursor(cursor);
}

QColor QTermScreen::GetColor(int col)
{
    QColor color[8] =
    {
        "black", "red", "green", "yellow",
        "deepskyblue", "magenta", "cyan", "white"
    };

    if (col >= 0 && col <= 7)
    {
        return color[col];
    }
    else
    {
        return color[0];
    }
}

void QTermScreen::DisplayReset()
{
    QColor color;

    color = GetColor(0);
    DisplayBackground(color);
    color = GetColor(7);
    DisplayForeground(color);
}

void QTermScreen::EraseEndOfLine()
{
    QTextCursor tc = textCursor();
    tc.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    tc.removeSelectedText();
    setTextCursor(tc);
}

void QTermScreen::EraseStartOfLine()
{
    QTextCursor tc = textCursor();
    tc.movePosition(QTextCursor::StartOfBlock, QTextCursor::KeepAnchor);
    tc.removeSelectedText();
    setTextCursor(tc);
}

void QTermScreen::EraseEntireLine()
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::LineUnderCursor);
    tc.removeSelectedText();
}

void QTermScreen::EraseDown()
{
    int bntop, bnbot;

    QTextCursor tctop = cursorForPosition(QPoint(0, 0));
    QTextCursor tcbot = cursorForPosition(QPoint(0, rect().bottom()));

    bntop = tctop.blockNumber();
    bnbot = tcbot.blockNumber();

    EraseEndOfLine();
    CursorDown(bnbot - bntop);
    for (; bntop < bnbot; bntop ++)
    {
        EraseEndOfLine();
        CursorUp();
    } 
}

void QTermScreen::EraseUp()
{
    QTextCursor tc = textCursor();
    QTextCursor tcup = cursorForPosition(QPoint(0, 0));

    tc.setPosition(tcup.position(), QTextCursor::KeepAnchor);
    tc.removeSelectedText();
}

void QTermScreen::EraseScreen()
{
    EraseDown();
    EraseUp();
}

QByteArray QTermScreen::GetLine(int n)
{
    QString str;
    QByteArray buf;
    int num;

    num = document()->lineCount();
    if (n<0)
        n = textCursor().blockNumber();

    if (n > num - 1)
        return buf;

    str = document()->findBlockByLineNumber(n).text();
    buf = str.toStdString().c_str();

    return buf;
}

