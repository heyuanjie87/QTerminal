#include <qglobal.h>

#include <QMainWindow>
#include <QList>
#include <qtextbrowser.h>
#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QStatusBar>

#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qtoolbar.h>
#include <qlayout.h>
#include <qsplitter.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qmenubar.h>
#include <qmessagebox.h>
#include <qregexp.h>
#include <qevent.h>

#include "qconf.h"
#include "lkc.h"

#include "QKconfig.h"

#include "images.c"

#define _(x) (x)

#define gettext(x) (x)

static inline QString qgettext(const char* str)
{
    return QString::fromLocal8Bit(gettext(str));
}

static inline QString qgettext(const QString& str)
{
    return QString::fromLocal8Bit(gettext(str.toLatin1()));
}

/*
 * set the new data
 * TODO check the value
 */
void ConfigItem::okRename(int col)
{
}

/*
 * update the displayed of a menu entry
 */
void ConfigItem::updateMenu(void)
{
    ConfigList* list;
    struct symbol* sym;
    struct property *prop;
    QString prompt;
    int type;
    tristate expr;

    list = listView();
    if (goParent) {
        setPixmap(promptColIdx, list->menuBackPix);
        prompt = "..";
        goto set_prompt;
    }

    sym = menu->sym;
    prop = menu->prompt;
    prompt = _(menu_get_prompt(menu));

    if (prop) switch (prop->type) {
    case P_MENU:
        if (list->mode == singleMode || list->mode == symbolMode) {
            /* a menuconfig entry is displayed differently
             * depending whether it's at the view root or a child.
             */
            if (sym && list->rootEntry == menu)
                break;
            setPixmap(promptColIdx, list->menuPix);
        } else {
            if (sym)
                break;
            setPixmap(promptColIdx, QIcon());
        }
        goto set_prompt;
    case P_COMMENT:
        setPixmap(promptColIdx, QIcon());
        goto set_prompt;
    default:
        ;
    }
    if (!sym)
        goto set_prompt;

    setText(nameColIdx, QString::fromLocal8Bit(sym->name));

    type = sym_get_type(sym);
    switch (type) {
    case S_BOOLEAN:
    case S_TRISTATE:
        char ch;

        if (!sym_is_changable(sym) && list->optMode == normalOpt) {
            setPixmap(promptColIdx, QIcon());
            setText(noColIdx, QString::null);
            setText(modColIdx, QString::null);
            setText(yesColIdx, QString::null);
            break;
        }
        expr = sym_get_tristate_value(sym);
        switch (expr) {
        case yes:
            if (sym_is_choice_value(sym) && type == S_BOOLEAN)
                setPixmap(promptColIdx, list->choiceYesPix);
            else
                setPixmap(promptColIdx, list->symbolYesPix);
            setText(yesColIdx, "Y");
            ch = 'Y';
            break;
        case mod:
            setPixmap(promptColIdx, list->symbolModPix);
            setText(modColIdx, "M");
            ch = 'M';
            break;
        default:
            if (sym_is_choice_value(sym) && type == S_BOOLEAN)
                setPixmap(promptColIdx, list->choiceNoPix);
            else
                setPixmap(promptColIdx, list->symbolNoPix);
            setText(noColIdx, "N");
            ch = 'N';
            break;
        }
        if (expr != no)
            setText(noColIdx, sym_tristate_within_range(sym, no) ? "_" : 0);
        if (expr != mod)
            setText(modColIdx, sym_tristate_within_range(sym, mod) ? "_" : 0);
        if (expr != yes)
            setText(yesColIdx, sym_tristate_within_range(sym, yes) ? "_" : 0);

        setText(dataColIdx, QChar(ch));
        break;
    case S_INT:
    case S_HEX:
    case S_STRING:
        const char* data;

        data = sym_get_string_value(sym);

        setText(dataColIdx, data);
        if (type == S_STRING)
            prompt = QString("%1: %2").arg(prompt).arg(data);
        else
            prompt = QString("(%2) %1").arg(prompt).arg(data);
        break;
    }
    if (!sym_has_value(sym) && visible)
        prompt += _(" (NEW)");
set_prompt:
    setText(promptColIdx, prompt);
}

void ConfigItem::testUpdateMenu(bool v)
{
    ConfigItem* i;

    visible = v;
    if (!menu)
        return;

    sym_calc_value(menu->sym);
    if (menu->flags & MENU_CHANGED) {
        /* the menu entry changed, so update all list items */
        menu->flags &= ~MENU_CHANGED;
        for (i = (ConfigItem*)menu->data; i; i = i->nextItem)
            i->updateMenu();
    } else if (listView()->updateAll)
        updateMenu();
}


/*
 * construct a menu entry
 */
void ConfigItem::init(void)
{
    if (menu) {
        ConfigList* list = listView();
        nextItem = (ConfigItem*)menu->data;
        menu->data = this;

        if (list->mode != fullMode)
            setExpanded(true);
        sym_calc_value(menu->sym);
    }
    updateMenu();
}

/*
 * destruct a menu entry
 */
ConfigItem::~ConfigItem(void)
{
    if (menu) {
        ConfigItem** ip = (ConfigItem**)&menu->data;
        for (; *ip; ip = &(*ip)->nextItem) {
            if (*ip == this) {
                *ip = nextItem;
                break;
            }
        }
    }
}

ConfigLineEdit::ConfigLineEdit(ConfigView* parent)
    : Parent(parent)
{
    connect(this, SIGNAL(editingFinished()), SLOT(hide()));
}

void ConfigLineEdit::show(ConfigItem* i)
{
    item = i;
    if (sym_get_string_value(item->menu->sym))
        setText(QString::fromLocal8Bit(sym_get_string_value(item->menu->sym)));
    else
        setText(QString::null);
    Parent::show();
    setFocus();
}

void ConfigLineEdit::keyPressEvent(QKeyEvent* e)
{
    switch (e->key()) {
    case Qt::Key_Escape:
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        sym_set_string_value(item->menu->sym, text().toLatin1());
        parent()->updateList(item);
        break;
    default:
        Parent::keyPressEvent(e);
        return;
    }
    e->accept();
    parent()->list->setFocus();
    hide();
}

ConfigList::ConfigList(ConfigView* p, const char *name)
    : Parent(p),
      updateAll(false),
      symbolYesPix(xpm_symbol_yes), symbolModPix(xpm_symbol_mod), symbolNoPix(xpm_symbol_no),
      choiceYesPix(xpm_choice_yes), choiceNoPix(xpm_choice_no),
      menuPix(xpm_menu), menuInvPix(xpm_menu_inv), menuBackPix(xpm_menuback), voidPix(xpm_void),
      mode(singleMode), optMode(normalOpt),
      rootEntry(0), headerPopup(0)
{
    int i;

    setObjectName(name);
    setSortingEnabled(false);
    setRootIsDecorated(true);

    setVerticalScrollMode(ScrollPerPixel);
    setHorizontalScrollMode(ScrollPerPixel);

    setHeaderLabels(QStringList() << _("Option") << _("Name") << "N" << "M" << "Y" << _("Value"));

    connect(this, SIGNAL(itemSelectionChanged(void)),
        SLOT(updateSelection(void)));

    if (name) {

        optMode = (enum optionMode)normalOpt;
    }

    addColumn(promptColIdx);

    reinit();
}

bool ConfigList::menuSkip(struct menu *menu)
{
    if (optMode == normalOpt && menu_is_visible(menu))
        return false;
    if (optMode == promptOpt && menu_has_prompt(menu))
        return false;
    if (optMode == allOpt)
        return false;
    return true;
}

void ConfigList::reinit(void)
{
    removeColumn(yesColIdx);
    removeColumn(modColIdx);
    removeColumn(noColIdx);

    updateListAll();
}

ConfigItem* ConfigList::findConfigItem(struct menu *menu)
{
    ConfigItem* item = (ConfigItem*)menu->data;

    for (; item; item = item->nextItem) {
        if (this == item->listView())
            break;
    }

    return item;
}

void ConfigList::updateSelection(void)
{
    struct menu *menu;
    enum prop_type type;

    if (selectedItems().count() == 0)
        return;

    ConfigItem* item = (ConfigItem*)selectedItems().first();
    if (!item)
        return;

    menu = item->menu;
    emit menuChanged(menu);
    if (!menu)
        return;
    type = menu->prompt ? menu->prompt->type : P_UNKNOWN;
    if (mode == menuMode && type == P_MENU)
        emit menuSelected(menu);
}

void ConfigList::updateList(ConfigItem* item)
{
    ConfigItem* last = 0;

    if (!rootEntry)
    {
        if (mode != listMode)
            goto update;
        QTreeWidgetItemIterator it(this);
        ConfigItem* item;

        while (*it) {
            item = (ConfigItem*)(*it);
            if (!item->menu)
                continue;
            item->testUpdateMenu(menu_is_visible(item->menu));

            ++it;
        }
        return;
    }

    if (rootEntry != rootMen && (mode == singleMode ||
        (mode == symbolMode && rootEntry->parent != rootMen))) {
        item = (ConfigItem *)topLevelItem(0);
        if (!item)
            item = new ConfigItem(this, 0, true);
        last = item;
    }
    if ((mode == singleMode || (mode == symbolMode && !(rootEntry->flags & MENU_ROOT))) &&
        rootEntry->sym && rootEntry->prompt) {
        item = last ? last->nextSibling() : firstChild();
        if (!item)
            item = new ConfigItem(this, last, rootEntry, true);
        else
            item->testUpdateMenu(true);

        updateMenuList(item, rootEntry);
        update();
        resizeColumnToContents(0);
        return;
    }

update:
    updateMenuList(this, rootEntry);
    update();
    resizeColumnToContents(0);
}

void ConfigList::setValue(ConfigItem* item, tristate val)
{
    struct symbol* sym;
    int type;
    tristate oldval;

    sym = item->menu ? item->menu->sym : 0;
    if (!sym)
        return;

    type = sym_get_type(sym);
    switch (type) {
    case S_BOOLEAN:
    case S_TRISTATE:
        oldval = sym_get_tristate_value(sym);

        if (!sym_set_tristate_value(sym, val))
            return;
        if (oldval == no && item->menu->list)
            item->setExpanded(true);
        parent()->updateList(item);
        break;
    }
}

void ConfigList::changeValue(ConfigItem* item)
{
    struct symbol* sym;
    struct menu* menu;
    int type, oldexpr, newexpr;

    menu = item->menu;
    if (!menu)
        return;
    sym = menu->sym;
    if (!sym) {
        if (item->menu->list)
            item->setExpanded(!item->isExpanded());
        return;
    }

    type = sym_get_type(sym);
    switch (type) {
    case S_BOOLEAN:
    case S_TRISTATE:
        oldexpr = sym_get_tristate_value(sym);
        newexpr = sym_toggle_tristate_value(sym);
        if (item->menu->list) {
            if (oldexpr == newexpr)
                item->setExpanded(!item->isExpanded());
            else if (oldexpr == no)
                item->setExpanded(true);
        }
        if (oldexpr != newexpr)
            parent()->updateList(item);
        break;
    case S_INT:
    case S_HEX:
    case S_STRING:
        parent()->lineEdit->show(item);
        break;
    }
}

void ConfigList::setRootMenu(struct menu *menu)
{
    enum prop_type type;

    if (rootEntry == menu)
        return;
    type = menu && menu->prompt ? menu->prompt->type : P_UNKNOWN;
    if (type != P_MENU)
        return;
    updateMenuList(this, 0);
    rootEntry = menu;
    updateListAll();
    if (currentItem()) {
        currentItem()->setSelected(hasFocus());
        scrollToItem(currentItem());
    }
}

void ConfigList::setParentMenu(struct menu *rm)
{
    ConfigItem* item;
    struct menu *oldroot;

    oldroot = rootEntry;
    if (rootEntry == rm)
        return;

    setRootMenu(rm);

    QTreeWidgetItemIterator it(this);
    while (*it) {
        item = (ConfigItem *)(*it);
        if (item->menu == oldroot) {
            setCurrentItem(item);
            scrollToItem(item);
            break;
        }

        ++it;
    }
}

/*
 * update all the children of a menu entry
 *   removes/adds the entries from the parent widget as necessary
 *
 * parent: either the menu list widget or a menu entry widget
 * menu: entry to be updated
 */
void ConfigList::updateMenuList(ConfigItem *parent, struct menu* menu)
{
    struct menu* child;
    ConfigItem* item;
    ConfigItem* last;
    bool visible;
    enum prop_type type;

    if (!menu) {
        while (parent->childCount() > 0)
        {
            delete parent->takeChild(0);
        }

        return;
    }

    last = parent->firstChild();
    if (last && !last->goParent)
        last = 0;
    for (child = menu->list; child; child = child->next) {
        item = last ? last->nextSibling() : parent->firstChild();
        type = child->prompt ? child->prompt->type : P_UNKNOWN;

        switch (mode) {
        case menuMode:
            if (!(child->flags & MENU_ROOT))
                goto hide;
            break;
        case symbolMode:
            if (child->flags & MENU_ROOT)
                goto hide;
            break;
        default:
            break;
        }

        visible = menu_is_visible(child);
        if (!menuSkip(child)) {
            if (!child->sym && !child->list && !child->prompt)
                continue;
            if (!item || item->menu != child)
                item = new ConfigItem(parent, last, child, visible);
            else
                item->testUpdateMenu(visible);

            if (mode == fullMode || mode == menuMode || type != P_MENU)
                updateMenuList(item, child);
            else
                updateMenuList(item, 0);
            last = item;
            continue;
        }
    hide:
        if (item && item->menu == child) {
            last = parent->firstChild();
            if (last == item)
                last = 0;
            else while (last->nextSibling() != item)
                last = last->nextSibling();
            delete item;
        }
    }
}

void ConfigList::updateMenuList(ConfigList *parent, struct menu* menu)
{
    struct menu* child;
    ConfigItem* item;
    ConfigItem* last;
    bool visible;
    enum prop_type type;

    if (!menu) {
        while (parent->topLevelItemCount() > 0)
        {
            delete parent->takeTopLevelItem(0);
        }

        return;
    }

    last = (ConfigItem*)parent->topLevelItem(0);
    if (last && !last->goParent)
        last = 0;
    for (child = menu->list; child; child = child->next) {
        item = last ? last->nextSibling() : (ConfigItem*)parent->topLevelItem(0);
        type = child->prompt ? child->prompt->type : P_UNKNOWN;

        switch (mode) {
        case menuMode:
            if (!(child->flags & MENU_ROOT))
                goto hide;
            break;
        case symbolMode:
            if (child->flags & MENU_ROOT)
                goto hide;
            break;
        default:
            break;
        }

        visible = menu_is_visible(child);
        if (!menuSkip(child)) {
            if (!child->sym && !child->list && !child->prompt)
                continue;
            if (!item || item->menu != child)
                item = new ConfigItem(parent, last, child, visible);
            else
                item->testUpdateMenu(visible);

            if (mode == fullMode || mode == menuMode || type != P_MENU)
                updateMenuList(item, child);
            else
                updateMenuList(item, 0);
            last = item;
            continue;
        }
    hide:
        if (item && item->menu == child) {
            last = (ConfigItem*)parent->topLevelItem(0);
            if (last == item)
                last = 0;
            else while (last->nextSibling() != item)
                last = last->nextSibling();
            delete item;
        }
    }
}

void ConfigList::keyPressEvent(QKeyEvent* ev)
{
    QTreeWidgetItem* i = currentItem();
    ConfigItem* item;
    struct menu *menu;
    enum prop_type type;

    if (ev->key() == Qt::Key_Escape && mode != fullMode && mode != listMode) {
        emit parentSelected();
        ev->accept();
        return;
    }

    if (!i) {
        Parent::keyPressEvent(ev);
        return;
    }
    item = (ConfigItem*)i;

    switch (ev->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        if (item->goParent) {
            emit parentSelected();
            break;
        }
        menu = item->menu;
        if (!menu)
            break;
        type = menu->prompt ? menu->prompt->type : P_UNKNOWN;
        if (type == P_MENU && rootEntry != menu &&
            mode != fullMode && mode != menuMode) {
            emit menuSelected(menu);
            break;
        }
    case Qt::Key_Space:
        changeValue(item);
        break;
    case Qt::Key_N:
        setValue(item, no);
        break;
    case Qt::Key_M:
        setValue(item, mod);
        break;
    case Qt::Key_Y:
        setValue(item, yes);
        break;
    default:
        Parent::keyPressEvent(ev);
        return;
    }
    ev->accept();
}

void ConfigList::mouseReleaseEvent(QMouseEvent* e)
{
    QPoint p = e->pos();
    ConfigItem* item = (ConfigItem*)itemAt(p);
    struct menu *menu;
    enum prop_type ptype;
    QIcon icon;
    int idx, x;

    if (!item)
        goto skip;

    menu = item->menu;
    x = header()->offset() + p.x();
    idx = header()->logicalIndexAt(x);
    switch (idx) {
    case promptColIdx:
        icon = item->pixmap(promptColIdx);
        if (!icon.isNull()) {
            int off = header()->sectionPosition(0) + visualRect(indexAt(p)).x() + 4; // 4 is Hardcoded image offset. There might be a way to do it properly.
            if (x >= off && x < off + icon.availableSizes().first().width()) {
                if (item->goParent) {
                    emit parentSelected();
                    break;
                } else if (!menu)
                    break;
                ptype = menu->prompt ? menu->prompt->type : P_UNKNOWN;
                if (ptype == P_MENU && rootEntry != menu &&
                    mode != fullMode && mode != menuMode)
                    emit menuSelected(menu);
                else
                    changeValue(item);
            }
        }
        break;
    case noColIdx:
        setValue(item, no);
        break;
    case modColIdx:
        setValue(item, mod);
        break;
    case yesColIdx:
        setValue(item, yes);
        break;
    case dataColIdx:
        changeValue(item);
        break;
    }

skip:
    //printf("contentsMouseReleaseEvent: %d,%d\n", p.x(), p.y());
    Parent::mouseReleaseEvent(e);
}

void ConfigList::mouseDoubleClickEvent(QMouseEvent* e)
{
    QPoint p = e->pos(); // TODO: Check if this works(was contentsToViewport).
    ConfigItem* item = (ConfigItem*)itemAt(p);
    struct menu *menu;
    enum prop_type ptype;

    if (!item)
        goto skip;
    if (item->goParent) {
        emit parentSelected();
        goto skip;
    }
    menu = item->menu;
    if (!menu)
        goto skip;
    ptype = menu->prompt ? menu->prompt->type : P_UNKNOWN;
    if (ptype == P_MENU && (mode == singleMode || mode == symbolMode))
        emit menuSelected(menu);
    else if (menu->sym)
        changeValue(item);

skip:
    //printf("contentsMouseDoubleClickEvent: %d,%d\n", p.x(), p.y());
    Parent::mouseDoubleClickEvent(e);
}

void ConfigList::focusInEvent(QFocusEvent *e)
{
    struct menu *menu = NULL;

    Parent::focusInEvent(e);

    ConfigItem* item = (ConfigItem *)currentItem();
    if (item) {
        item->setSelected(true);
        menu = item->menu;
    }
    emit gotFocus(menu);
}

ConfigView::ConfigView(QWidget* parent, const char *name)
    : Parent(parent)
{
    setObjectName(name);
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    list = new ConfigList(this);
    verticalLayout->addWidget(list);
    lineEdit = new ConfigLineEdit(this);
    lineEdit->hide();
    verticalLayout->addWidget(lineEdit);
}

ConfigView::~ConfigView(void)
{

}

void ConfigList::setAllOpen(bool open)
{
    QTreeWidgetItemIterator it(this);

    while (*it) {
        (*it)->setExpanded(open);

        ++it;
    }
}

void ConfigView::updateList(ConfigItem* item)
{
    list->updateList(item);
}

void ConfigView::updateListAll(void)
{
    list->updateListAll();
}

ConfigInfoView::ConfigInfoView(QWidget* parent, const char *name)
    : Parent(parent),
      sym(0), _menu(0),
      _showDebug(false)
{
    QVBoxLayout *vlayout = new QVBoxLayout(this);

    vlayout->setContentsMargins(0, 0, 0, 0);

    helpWin = new QTextBrowser(this);
    vlayout->addWidget(helpWin);
    msgWin = new QTextEdit(this);
    vlayout->addWidget(msgWin);
    msgWin->hide();
}

void ConfigInfoView::setShowDebug(bool b)
{
    if (_showDebug != b) {
        _showDebug = b;
        if (_menu)
            menuInfo();
        else if (sym)
            symbolInfo();
        emit showDebugChanged(b);
    }
}

void ConfigInfoView::setInfo(struct menu *m)
{
    if (_menu == m)
        return;
    _menu = m;
    sym = NULL;
    if (!_menu)
        helpWin->clear();
    else
        menuInfo();
}

void ConfigInfoView::symbolInfo(void)
{
    QString str;

    str += "<big>Symbol: <b>";
    str += print_filter(sym->name);
    str += "</b></big><br><br>value: ";
    str += print_filter(sym_get_string_value(sym));
    str += "<br>visibility: ";
    str += sym->visible == yes ? "y" : sym->visible == mod ? "m" : "n";
    str += "<br>";
    str += debug_info(sym);

    helpWin->setText(str);
}

void ConfigInfoView::menuInfo(void)
{
    struct symbol* sym;
    QString head, debug, help;

    sym = _menu->sym;
    if (sym) {
        if (_menu->prompt) {
            head += "<big><b>";
            head += print_filter(_(_menu->prompt->text));
            head += "</b></big>";
            if (sym->name) {
                head += " (";
                if (showDebug())
                    head += QString().sprintf("<a href=\"s%p\">", sym);
                head += print_filter(sym->name);
                if (showDebug())
                    head += "</a>";
                head += ")";
            }
        } else if (sym->name) {
            head += "<big><b>";
            if (showDebug())
                head += QString().sprintf("<a href=\"s%p\">", sym);
            head += print_filter(sym->name);
            if (showDebug())
                head += "</a>";
            head += "</b></big>";
        }
        head += "<br><br>";

        if (showDebug())
            debug = debug_info(sym);

        struct gstr help_gstr = str_new();
        menu_get_ext_help(_menu, &help_gstr, rootMen);
        help = print_filter(str_get(&help_gstr));
        str_free(&help_gstr);
    } else if (_menu->prompt) {
        head += "<big><b>";
        head += print_filter(_(_menu->prompt->text));
        head += "</b></big><br><br>";
        if (showDebug()) {
            if (_menu->prompt->visible.expr) {
                debug += "&nbsp;&nbsp;dep: ";
                expr_print(_menu->prompt->visible.expr, expr_print_help, &debug, E_NONE);
                debug += "<br><br>";
            }
        }
    }
    if (showDebug())
        debug += QString().sprintf("defined at %s:%d<br><br>", _menu->file->name, _menu->lineno);

    helpWin->setText(head + debug + help);
}

QString ConfigInfoView::debug_info(struct symbol *sym)
{
    QString debug;

    debug += "type: ";
    debug += print_filter(sym_type_name(sym->type));
    if (sym_is_choice(sym))
        debug += " (choice)";
    debug += "<br>";
    if (sym->rev_dep.expr) {
        debug += "reverse dep: ";
        expr_print(sym->rev_dep.expr, expr_print_help, &debug, E_NONE);
        debug += "<br>";
    }
    for (struct property *prop = sym->prop; prop; prop = prop->next) {
        switch (prop->type) {
        case P_PROMPT:
        case P_MENU:
            debug += QString().sprintf("prompt: <a href=\"m%p\">", prop->menu);
            debug += print_filter(_(prop->text));
            debug += "</a><br>";
            break;
        case P_DEFAULT:
        case P_SELECT:
        case P_RANGE:
        case P_ENV:
            debug += prop_get_type_name(prop->type);
            debug += ": ";
            expr_print(prop->expr, expr_print_help, &debug, E_NONE);
            debug += "<br>";
            break;
        case P_CHOICE:
            if (sym_is_choice(sym)) {
                debug += "choice: ";
                expr_print(prop->expr, expr_print_help, &debug, E_NONE);
                debug += "<br>";
            }
            break;
        default:
            debug += "unknown property: ";
            debug += prop_get_type_name(prop->type);
            debug += "<br>";
        }
        if (prop->visible.expr) {
            debug += "&nbsp;&nbsp;&nbsp;&nbsp;dep: ";
            expr_print(prop->visible.expr, expr_print_help, &debug, E_NONE);
            debug += "<br>";
        }
    }
    debug += "<br>";

    return debug;
}

QString ConfigInfoView::print_filter(const QString &str)
{
    QRegExp re("[<>&\"\\n]");
    QString res = str;
    for (int i = 0; (i = res.indexOf(re, i)) >= 0;) {
        switch (res[i].toLatin1()) {
        case '<':
            res.replace(i, 1, "&lt;");
            i += 4;
            break;
        case '>':
            res.replace(i, 1, "&gt;");
            i += 4;
            break;
        case '&':
            res.replace(i, 1, "&amp;");
            i += 5;
            break;
        case '"':
            res.replace(i, 1, "&quot;");
            i += 6;
            break;
        case '\n':
            res.replace(i, 1, "<br>");
            i += 4;
            break;
        }
    }
    return res;
}

void ConfigInfoView::expr_print_help(void *data, struct symbol *sym, const char *str)
{
    QString* text = reinterpret_cast<QString*>(data);
    QString str2 = print_filter(str);

    if (sym && sym->name && !(sym->flags & SYMBOL_CONST)) {
        *text += QString().sprintf("<a href=\"s%p\">", sym);
        *text += str2;
        *text += "</a>";
    } else
        *text += str2;
}

void ConfigInfoView::addMsg(QString str, int type)
{
    msgWin->append(str);
}

/*
 * Construct the complete config widget
 */
ConfigMainWindow::ConfigMainWindow(void)
{
    QMenuBar* menu;
    bool ok = true;

    resize(700, 600);

    initToolBt();

    split1 = new QSplitter(Qt::Horizontal, this);
    setCentralWidget(split1);

    menuView = new ConfigView(split1, "menu");
    menuList = menuView->list;

    split2 = new QSplitter(Qt::Vertical, split1);

    // create config tree
    configView = new ConfigView(split2, "config");
    configList = configView->list;

    helpText = new ConfigInfoView(split2, "help");

    setTabOrder(configList, helpText);
    configList->setFocus();
#if 0
    menu = menuBar();
    toolBar = new QToolBar("Tools", this);
    addToolBar(toolBar);

    backAction = new QAction(QPixmap(xpm_back), _("Back"), this);
      connect(backAction, SIGNAL(triggered(bool)), SLOT(goBack()));
      backAction->setEnabled(false);
    QAction *quitAction = new QAction(_("&Quit"), this);
    quitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
      connect(quitAction, SIGNAL(triggered(bool)), SLOT(close()));
    QAction *loadAction = new QAction(QPixmap(xpm_load), _("&Load"), this);
    loadAction->setShortcut(Qt::CTRL + Qt::Key_L);
      connect(loadAction, SIGNAL(triggered(bool)), SLOT(loadConfig()));
    saveAction = new QAction(QPixmap(xpm_save), _("&Save"), this);
    saveAction->setShortcut(Qt::CTRL + Qt::Key_S);
      connect(saveAction, SIGNAL(triggered(bool)), SLOT(saveConfig()));

    // Set saveAction's initial state
    conf_changed();
    QAction *saveAsAction = new QAction(_("Save &As..."), this);
      connect(saveAsAction, SIGNAL(triggered(bool)), SLOT(saveConfigAs()));

    // init tool bar
    toolBar->addAction(backAction);
    toolBar->addSeparator();
    toolBar->addAction(loadAction);
    toolBar->addAction(saveAction);
    toolBar->addSeparator();

    // create config menu
    QMenu* config = menu->addMenu(_("&File"));
    config->addAction(loadAction);
    config->addAction(saveAction);
    config->addAction(saveAsAction);
    config->addSeparator();
    config->addAction(quitAction);
#endif
    connect(configList, SIGNAL(menuChanged(struct menu *)),
        helpText, SLOT(setInfo(struct menu *)));
    connect(configList, SIGNAL(menuSelected(struct menu *)),
        SLOT(changeMenu(struct menu *)));
    connect(configList, SIGNAL(parentSelected()),
        SLOT(goBack()));
    connect(menuList, SIGNAL(menuChanged(struct menu *)),
        helpText, SLOT(setInfo(struct menu *)));
    connect(menuList, SIGNAL(menuSelected(struct menu *)),
        SLOT(changeMenu(struct menu *)));

    connect(configList, SIGNAL(gotFocus(struct menu *)),
        helpText, SLOT(setInfo(struct menu *)));
    connect(menuList, SIGNAL(gotFocus(struct menu *)),
        helpText, SLOT(setInfo(struct menu *)));
    connect(menuList, SIGNAL(gotFocus(struct menu *)),
        SLOT(listFocusChanged(void)));
    connect(helpText, SIGNAL(menuSelected(struct menu *)),
        SLOT(setMenuLink(struct menu *)));

    worker = new QKconfig;

    connect(worker, SIGNAL(parseDone(int)), this, SLOT(parseDone(int)));
    connect(worker, SIGNAL(msgOut(QString)), this, SLOT(msgRecv(QString)));
}

void ConfigMainWindow::initToolBt(void)
{
    btLoad = new QPushButton(this);
    btSave = new QPushButton(this);

    btLoad->setText("Load");
    btSave->setText("Save");

    connect(btLoad, SIGNAL(clicked()),
            this, SLOT(loadConfig()));
    connect(btSave, SIGNAL(clicked()),
            this, SLOT(saveConfig()));

    statusBar()->addWidget(btLoad);
    statusBar()->addWidget(btSave);
}

void ConfigMainWindow::loadConfig(void)
{
    QString s = QFileDialog::getOpenFileName(this, "", conf_get_configname());
    if (s.isNull())
        return;

    worker->parseReq(s);
}

void ConfigMainWindow::parseDone(int err)
{
    if (err == 0)
    {
        rootMen = &worker->getMenu()->root;
        showSplitView();
        conf_changed();
    }
}

void ConfigMainWindow::parse(QString &name)
{
    emit worker->parseReq(name);
}

bool ConfigMainWindow::saveConfig(void)
{
    if (!worker->writeConfig("jjj"))
    {
        QMessageBox::information(this, "qconf", _("Unable to save configuration!"));
        return false;
    }

    return true;
}

void ConfigMainWindow::saveConfigAs(void)
{
    QString s = QFileDialog::getSaveFileName(this, "", conf_get_configname());
    if (s.isNull())
        return;
    saveConfig();
}

void ConfigMainWindow::changeMenu(struct menu *menu)
{
    configList->setRootMenu(menu);
//    if (configList->rootEntry->parent == rootMen)
//        backAction->setEnabled(false);
//    else
//        backAction->setEnabled(true);
}

void ConfigMainWindow::setMenuLink(struct menu *menu)
{
    struct menu *parent;
    ConfigList* list = NULL;
    ConfigItem* item;

    if (configList->menuSkip(menu))
        return;

    switch (configList->mode) {
    case singleMode:
        list = configList;
        parent = menu_get_parent_menu(menu, rootMen);
        if (!parent)
            return;
        list->setRootMenu(parent);
        break;
    case symbolMode:
        if (menu->flags & MENU_ROOT) {
            configList->setRootMenu(menu);
            configList->clearSelection();
            list = menuList;
        } else {
            list = configList;
            parent = menu_get_parent_menu(menu->parent, rootMen);
            if (!parent)
                return;
            item = menuList->findConfigItem(parent);
            if (item) {
                item->setSelected(true);
                menuList->scrollToItem(item);
            }
            list->setRootMenu(parent);
        }
        break;
    case fullMode:
        list = configList;
        break;
    default:
        break;
    }

    if (list) {
        item = list->findConfigItem(menu);
        if (item) {
            item->setSelected(true);
            list->scrollToItem(item);
            list->setFocus();
        }
    }
}

void ConfigMainWindow::listFocusChanged(void)
{
    if (menuList->mode == menuMode)
        configList->clearSelection();
}

void ConfigMainWindow::goBack(void)
{
    ConfigItem* item, *oldSelection;

    configList->setParentMenu(rootMen);
  //  if (configList->rootEntry == rootMen)
  //      backAction->setEnabled(false);

    if (menuList->selectedItems().count() == 0)
        return;

    item = (ConfigItem*)menuList->selectedItems().first();
    oldSelection = item;
    while (item) {
        if (item->menu == configList->rootEntry) {
            oldSelection->setSelected(false);
            item->setSelected(true);
            break;
        }
        item = (ConfigItem*)item->parent();
    }
}

void ConfigMainWindow::showSplitView(void)
{
    configList->rootMen = rootMen;
    configList->mode = symbolMode;
    if (configList->rootEntry == rootMen)
        configList->updateListAll();
    else
        configList->setRootMenu(rootMen);
    configList->setAllOpen(true);

    menuList->rootMen = rootMen;
    menuList->mode = menuMode;
    menuList->setRootMenu(rootMen);
    menuList->setAllOpen(true);
    menuView->show();
    menuList->setFocus();

    helpText->rootMen = rootMen;
}

/*
 * ask for saving configuration before quitting
 * TODO ask only when something changed
 */
void ConfigMainWindow::closeEvent(QCloseEvent* e)
{
    if (!worker->isChanged())
    {
        e->accept();
        return;
    }

    QMessageBox mb("qconf", _("Save configuration?"), QMessageBox::Warning,
            QMessageBox::Yes | QMessageBox::Default, QMessageBox::No, QMessageBox::Cancel | QMessageBox::Escape);
    mb.setButtonText(QMessageBox::Yes, _("&Save Changes"));
    mb.setButtonText(QMessageBox::No, _("&Discard Changes"));
    mb.setButtonText(QMessageBox::Cancel, _("Cancel Exit"));
    switch (mb.exec())
    {
    case QMessageBox::Yes:
        if (saveConfig())
            e->accept();
        else
            e->ignore();
        break;
    case QMessageBox::No:
        e->accept();
        break;
    case QMessageBox::Cancel:
        e->ignore();
        break;
    }
}

void ConfigMainWindow::conf_changed(void)
{
    //if (saveAction)
   //     saveAction->setEnabled(worker->isChanged());
}

void ConfigMainWindow::msgRecv(QString msg)
{
    helpText->addMsg(msg);
}

void ConfigMainWindow::setSettings(Session &ss)
{
    QString str;

    str = ss.param["file"];
    if (!str.isEmpty())
    {
        worker->putEnv(ss.param["env"]);
        parse(str);
    }
}
