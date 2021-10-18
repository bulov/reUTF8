/*
 *      Редактор RED.
 *
 *      $Header: A.locl.h,v 4.20 90/05/22 23:21:33 alex Exp $
 *      $Log:	A.locl.h,v $
 * Revision 4.20  90/05/22  23:21:33  alex
 * First rev. red 4.2
 * 
 * Revision 4.10  90/02/05  19:52:14  alex
 * Base revision 4.1
 * 
 * Revision 4.2  88/04/07  12:05:35  alex
 * Исправлен приоритет с -10 на -2.
 * 
 * Revision 4.1  88/03/31  22:00:08  alex
 * Версия 4.1 - обкатка на UTEC, СМ
 * 
 * Revision 3.1.2.2  87/07/03  22:01:21  alex
 * Graph_characters used in margin
 * 
 * Revision 3.1.2.1  87/06/19  17:14:18  alex
 * Base revision for new RED
 * 
 * Revision 3.1  87/06/19  17:13:32  alex
 * *** empty log message ***
 * 
 * Revision 1.1  87/06/19  16:17:41  alex
 * Initial revision
 * 
 * Revision 3.6  87/06/12  18:08:07  alex
 * Исправлены ошибки в режиме vilcase и мелочи для vt-200
 *
 * Revision 3.5  87/06/09  19:45:40  alex
 * Исправлена работа с tty ~ VT200 и 15-ИЭ-0013
 * 
 * Revision 3.4  87/06/05  23:48:56  alex
 * Добавлен roll для терминалов с sr/sf и отображение
 *  табуляций в режиме -t + всякая мелочь
 * 
 * Revision 3.3  86/10/14  23:00:05  alex
 * Об'единены описания ДЕМОС-2 и ДЕМОС-1700.
 * 
 * Revision 3.2  86/09/19  21:36:44  alex
 * Введена работа с job control.
 * 
 * Revision 3.1  86/09/19  19:48:14  alex
 * Версия для UTEC/2
 * 
 */

/*  Полиэкранный универсальный редактор RED
 *  Машинно и системно - зависимые определения
 */

/*******************************
 *  Описания для M-680xx       *
 *******************************
 */

#define DEBUG
#define SWORD (sizeof (int))

/*******************************
 *  Описания для ДЕМОС 2       *
 *******************************
 */
#define DEMOS
#include <sys/code.h>
/**********************
 * Длина границы окна *
 **********************/
#define LMARG 1

/* Установка флагов для полного набора символов */
#define REDFLG(x) (x&(~(ECHO|CRMOD|XTABS|RAW))|(CBREAK))
/* Установка флагов для урезанного набора символов */
#define REDFLGL(x) (x&(~(ECHO|CRMOD|XTABS|RAW))|(CBREAK|CYRILL|LCASE|SISO)) /* См. S.ttyio.c -#ifndef MNOS */
#define LCASEO
/* Проверка на тему 'LCASE?' */
#define LCFLG(x) ((x)&(LCASE))
/* Проверка на тему 'Только латинские символы ' */
#define LATFLG(x) (((x)&CYRILL)==0)
/* Проверка на режим 'могут исказиться прописные/строчные буквы в ф/к' */
#define KIOFLG(x) (((x)&(CYRILL|CSTYLE|LCASE))==(CYRILL|CS_TYPE0))
/* Проверка на режим - в русском режиме буквы переворачиваются */
#define KI40BIT(x) ((x&(CYRILL|CSTYLE|LCASE))==(CYRILL|CS_TYPE2)||lcasef)

/*
 * Имя структуры для TIOCSETA
 */
#define SGTTYB sgttya
/* #define Y_SIGSTOP  /* Пока не сделана обработка stop-сигналов */
#define RED_CYRILL

/* Запрос идентификаторов пользователя и группы, установка приоритета */

#define GETUID (getuid())
#define GETGID (getgid())
#define NICE   nice(-2)

/*******************************
 *  Суффикс для переименования *
 *******************************
 */
#define SUFFBAK ".b"

#ifndef Ucode
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

#else Ucode

/*******************************
 *  Описания для кода U-код    *
 *******************************
 */

/* 1. Символы из набора русских букв, которые не отображаются вообще: S_NO1
      Символы из набора русских букв, которые не отображаются в lcase: S_NO2
      Прописные русские буквы                                          RLPRO
      Строчные русские буквы                                           RLSTRO
*/
#define S_NO1 0332 /* большой твердый знак */
#define S_NO2 0372 /* малый твердый знак   */
#define RLPRO(x) ((unsigned)(x) >=0300 && (unsigned)(x)<=0337)
#define RLSTRO(x) ((unsigned)(x) >=0340 && (unsigned)(x)<=0377)

/* 2. Преобразования:
 * STK7(s) - из текущей кодировки в КОИ-7
 * K7TS(s) - из КОИ-7 в прописную букву
 *           (строчная должна отличаться битом 040
 * STASCII(s) - из текущей кодировки в ASCII
 *
 * Все преобразования применяются только для символов >=0300
 */
extern char ck7tu[], cutk7[];
#define STK7(s) cutk7[((s)&037)]
#define K7TS(s) ck7tu[((s)&037)]
#define STASCII(s) ((STK7(s)&0137)|((s)&040))

/* Необходимые инициализации (флаг INIT_RE включен только в одном файле )
 */

#ifdef INIT_RE
char ck7tu[040] = {
/* 140   Ю     А     Б     Ц     Д     Е     Ф     Г  */
	0336, 0300, 0301, 0326, 0304, 0305, 0324, 0303,
/* 150   Х     И     Й     К     Л     М     Н     О  */
	0325, 0310, 0311, 0312, 0313, 0314, 0315, 0316,
/* 160   П     Я     Р     С     Т     У     Ж     В  */
	0317, 0337, 0320, 0321, 0322, 0323, 0306, 0302,
/* 170   Ь     У     З     Ш     Э     Щ     Ч     '  */
	0334, 0333, 0307, 0330, 0335, 0331, 0327, 0332};

char cutk7[040] = {
/* 300   А     Б     В     Г     Д     Е     Ж     З  */
	0141, 0142, 0167, 0147, 0144, 0145, 0166, 0172,
/* 310   И     Й     К     Л     М     Н     О     П  */
	0151, 0152, 0153, 0154, 0155, 0156, 0157, 0160,
/* 320   Р     С     Т     У     Ф     Х     Ц     Ч  */
	0162, 0163, 0164, 0165, 0146, 0150, 0143, 0176,
/* 330   Ш     Щ     '     Ы     Ь     Э     Ю     Я  */
	0173, 0175, 0177, 0171, 0170, 0174, 0140, 0161};
#endif

#endif
