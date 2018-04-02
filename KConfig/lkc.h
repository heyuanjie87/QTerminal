/*
 * Copyright (C) 2002 Roman Zippel <zippel@linux-m68k.org>
 * Released under the terms of the GNU GPL v2.0.
 */

#ifndef LKC_H
#define LKC_H

#include "expr.h"

static inline const char *gettext(const char *txt) { return txt; }
static inline void textdomain(const char *domainname) {}
static inline void bindtextdomain(const char *name, const char *dir) {}
static inline char *bind_textdomain_codeset(const char *dn, char *c) { return c; }

#ifdef __cplusplus
extern "C" {
#endif

#include "lkc_proto.h"

#define SRCTREE "srctree"

#ifndef PACKAGE
#define PACKAGE "linux"
#endif

#define LOCALEDIR "/usr/share/locale"

#define _(text) gettext(text)
#define N_(text) (text)

#ifndef CONFIG_
#define CONFIG_ "CONFIG_"
#endif
static inline const char *CONFIG_prefix(void)
{
	return getenv( "CONFIG_" ) ?: CONFIG_;
}
#undef CONFIG_
#define CONFIG_ CONFIG_prefix()

#define TF_COMMAND	0x0001
#define TF_PARAM	0x0002
#define TF_OPTION	0x0004

enum conf_def_mode {
	def_default,
	def_yes,
	def_mod,
	def_no,
	def_random
};

#define T_OPT_MODULES		1
#define T_OPT_DEFCONFIG_LIST	2
#define T_OPT_ENV		3
#define T_OPT_ALLNOCONFIG_Y	4

struct kconf_id {
	int name;
	int token;
	unsigned int flags;
	enum symbol_type stype;
};

#define YY_TYPEDEF_YY_SCANNER_T

typedef void* yyscan_t;

struct file* zconf_current_file(yyscan_t yyscanner);
void zconf_starthelp(yyscan_t yyscanner);
FILE *zconf_fopen(const char *name);
int zconf_initscan(const char *name, yyscan_t *yyscanner, struct msg_out *msgout);
bool zconf_nextfile(const char *name, yyscan_t yyscanner);
int zconf_lineno(yyscan_t yyscanner);
const char *zconf_curname(yyscan_t yyscanner);
void zconf_print_fileinfo(yyscan_t yyscanner, const char *fmt);

/* confdata.c */
const char *conf_get_configname(void);
const char *conf_get_autoconfig_name(void);
char *conf_get_default_confname(void);
void sym_add_change_count(kcmenu_t *kcm, int count);
bool conf_set_all_new_symbols(enum conf_def_mode mode);
void set_all_choice_values(struct symbol *csym);
int conf_write(const char *name, kcmenu_t *kcm);

/* confdata.c and expr.c */
static inline void xfwrite(const void *str, size_t len, size_t count, FILE *out)
{
	assert(len != 0);

	if (fwrite(str, len, count, out) != count)
		fprintf(stderr, "Error in writing or end of file.\n");
}

/* menu.c */
void _menu_init(kcmenu_t *kcm);
void menu_warn(struct menu *menu, const char *fmt, ...);
struct menu *menu_add_menu(kcmenu_t *kcm);
void menu_end_menu(kcmenu_t *kcm);
void menu_add_entry(struct symbol *sym, kcmenu_t *kcm);
void menu_end_entry(void);
void menu_add_dep(struct expr *dep, kcmenu_t *kcm);
void menu_add_visibility(struct expr *dep, kcmenu_t *kcm);
struct property *menu_add_prompt(enum prop_type type, char *prompt, struct expr *dep, kcmenu_t *kcm);
void menu_add_expr(enum prop_type type, struct expr *expr, struct expr *dep, kcmenu_t *kcm);
void menu_add_symbol(enum prop_type type, struct symbol *sym, struct expr *dep, kcmenu_t *kcm);
void menu_add_option(int token, char *arg, kcmenu_t *kcm);
void menu_finalize(struct menu *parent, kcmenu_t *kcm);
void menu_set_type(int type, kcmenu_t *kcm);

/* util.c */
struct file *file_lookup(const char *name, struct file **file_list);
int file_write_dep(const char *name, kcmenu_t *kcm);
void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);

struct gstr {
	size_t len;
	char  *s;
	/*
	* when max_width is not zero long lines in string s (if any) get
	* wrapped not to exceed the max_width value
	*/
	int max_width;
};
struct gstr str_new(void);
void str_free(struct gstr *gs);
void str_append(struct gstr *gs, const char *s);
void str_printf(struct gstr *gs, const char *fmt, ...);
const char *str_get(struct gstr *gs);

/* symbol.c */
void sym_init(kcmenu_t *kcm);
void sym_clear_all_valid(kcmenu_t *kcm);
struct symbol *sym_choice_default(struct symbol *sym);
const char *sym_get_string_default(struct symbol *sym);
struct symbol *sym_check_deps(struct symbol *sym);
struct property *prop_alloc(enum prop_type type, struct symbol *sym, kcmenu_t *kcm);
struct symbol *prop_get_symbol(struct property *prop);
struct property *sym_get_env_prop(struct symbol *sym);

static inline tristate sym_get_tristate_value(struct symbol *sym)
{
	return sym->curr.tri;
}


static inline struct symbol *sym_get_choice_value(struct symbol *sym)
{
	return (struct symbol *)sym->curr.val;
}

static inline bool sym_set_choice_value(struct symbol *ch, struct symbol *chval)
{
	return sym_set_tristate_value(chval, yes);
}

static inline bool sym_is_choice(struct symbol *sym)
{
	return sym->flags & SYMBOL_CHOICE ? true : false;
}

static inline bool sym_is_choice_value(struct symbol *sym)
{
	return sym->flags & SYMBOL_CHOICEVAL ? true : false;
}

static inline bool sym_is_optional(struct symbol *sym)
{
	return sym->flags & SYMBOL_OPTIONAL ? true : false;
}

static inline bool sym_has_value(struct symbol *sym)
{
	return sym->flags & SYMBOL_DEF_USER ? true : false;
}

#ifdef __cplusplus
}
#endif

#endif /* LKC_H */
