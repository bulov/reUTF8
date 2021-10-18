/*
 *      Редактор RED. ИАЭ им. И.В. Курчатова, ОС ДЕМОС
 *
 *      $Header: S.locl.h,v 3.4 86/09/19 19:47:26 alex Exp $
 *      $Log:	S.locl.h,v $
 * Revision 3.4  86/09/19  19:47:26  alex
 * Версия для СМ-1700
 * 
 * Revision 3.3  86/08/04  21:01:17  alex
 * Bepqh dk LMNQ/DELNQ 2
 * 
 * Revision 3.2  86/07/24  00:20:57  alex
 * Об'единены версии текстов для ЕС и СМ
 * 
 * Revision 3.1  86/04/20  23:40:15  alex
 * Базовая версия для ЕС.
 *
 * Revision 3.1  86/04/20  23:40:15  alex
 * *** empty log message ***
 * 
 * Revision 1.2  86/04/13  21:55:51  alex
 *
 */

/*  Полиэкранный универсальный редактор RED
 *  Машинно и системно - зависимые определения
 */

/*******************************
 *  Описания для СМ-4          *
 *******************************
 */

#define SWORD (sizeof (int))

/*******************************
 *  Описания для ДЕМОС 1.2   *
 *******************************
 */
#define DEMOS

/**********************
 * Длина границы окна *
 **********************/
#define LMARG 1

/* Установка флагов для полного набора символов */
#define REDFLG(x) (x&(~(ECHO|CRMOD|INDCTL|XTABS|RAW))|(CBREAK))
/* Установка флагов для урезанного набора символов */
#define REDFLGL(x) (x&(~(ECHO|CRMOD|INDCTL|XTABS|RAW|LCASE))|(CBREAK|KIRILL|IKIRILL)) /* См. ned.t.c -#ifndef MNOS */
/* Проверка на тему 'LCASE?' */
#define LCFLG(x) ((x)&(LCASE))
/* Проверка на тему 'Только латинские символы ' */
#define LATFLG(x) (((x)&KIRILL)==0)
/* Проверка на режим 'могут исказиться прописные/строчные буквы в ф/к' */
#define KIOFLG(x) (((x)&(KIRILL|IKIRILL|LCASE))==(KIRILL))

/* Запрос идентификаторов пользователя и группы, установка приоритета */

#define GETUID (getuid())
#define GETGID (getgid())
#define NICE   nice(-10)

/*******************************
 *  Суффикс для переименования *
 *******************************
 */
#define SUFFBAK ".bak"

/*******************************
 *  Описания для кода KOI-8    *
 *******************************
 */

/* 1. Символы из набора русских букв, которые не отображаются вообще: S_NO1
 *    Символы из набора русских букв, которые не отображаются в lcase: S_NO2
 *    Прописные русские буквы                                          RLPRO
 *    Строчные русские буквы                                           RLSTRO
 */
#define S_NO1 0377 /* большой твердый знак */
#define S_NO2 0337 /* малый твердый знак   */
#define RLPRO(x) ((unsigned)(x) >=0340 && (unsigned)(x)<=0376)
#define RLSTRO(x) ((unsigned)(x) >=0300 && (unsigned)(x)<=0337)

/* 2. Преобразования:
 * STK7(s) - из текущей кодировки в КОИ-7
 * K7TS(s) - из КОИ-7 в прописную букву
 *           (строчная должна отличаться битом 040
 * STASCII(s) - из текущей кодировки в ASCII
 *
 * Все преобразования применяются только для символов >=0300
 */
#define STK7(s) ((s)&0177|040)
#define K7TS(s) ((s)|0200)
#define STASCII(s) ((s)&0177)

/* Необходимые инициализации (флаг INIT_RE включен только в одном файле )
 */

#ifdef INIT_RE
/* Для КОИ-8 ничего не нужно */
#endif

