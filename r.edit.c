/*
 *      Редактор RED.
 * Функции по манипулированию содержимым файлов для RED
 *      $Header: r.edit.c,v 4.20 90/05/22 23:21:45 alex Exp $
 *      $Log:	r.edit.c,v $
 * Revision 4.20  90/05/22  23:21:45  alex
 * First rev. red 4.2
 * 
 * Revision 4.10  90/02/05  19:52:20  alex
 * Base revision 4.1
 * 
 * Revision 4.1  88/03/31  22:01:32  alex
 * Версия 4.1 - обкатка на UTEC, СМ
 * 
 * Revision 3.8  88/03/30  17:28:23  alex
 * Исправлена ошибка в readch. Введены функции для удаления/вставки
 * строк на экране через ChangeScroll/InsertLine-DeleteLine.
 * 
 * Revision 3.1.2.1  87/06/19  16:59:08  alex
 * Start revision for red/4
 * 
 * Revision 3.7  87/06/05  23:49:46  alex
 * Добавлен roll для терминалов с sr/sf и отображение
 *  табуляций в режиме -t + всякая мелочь
 * 
 * Revision 3.6  87/06/04  23:43:10  alex
 * Scroll on -sr- or -al/dl- added
 * 
 * Revision 3.6  87/04/01  19:15:20  alex
 * Revision for Utec: Cs, Ce, Ct, hR
 * 
 * Revision 3.5  86/10/14  23:00:35  alex
 * Исправлена ошибка в exinss (не там стояли скобки у масок).
 * 
 * Revision 3.4  86/09/19  19:50:59  alex
 * Версия для СМ-1700
 * 
 * Revision 3.3  86/08/04  20:50:56  alex
 * Bepqh dk LMNQ/DELNQ 2
 * 
 * Revision 3.2  86/07/24  00:23:08  alex
 * Об'единены версии текстов для ЕС и СМ
 * 
 * Revision 3.1.1.4  86/06/16  22:16:48  alex
 * Первая версия с повтором сеанса (пока грязная)
 * 
 * Revision 3.1.1.2  86/06/06  00:13:40  alex
 * Введена установка ключей
 * 
 * Revision 3.1.1.1  86/06/05  00:03:49  alex
 * Отлажено_на_модели
 * 
 * Revision 3.1  86/04/20  23:40:53  alex
 * Базовая версия для ЕС.
 * 
 * Revision 3.1  86/04/20  23:40:53  alex
 * *** empty log message ***
 * 
 * Revision 1.5  86/04/13  21:57:54  alex
 *
 */

#include "r.defs.h"
#ifdef RED_ALT
char   koi_alt[] = {
/*80*/ 0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
/*90*/ 0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xff,0xcc,0xcd,0xce,0xcf,
/*A0*/ 0xf9,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,
/*B0*/ 0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xd0,0xfa,0xfb,0xfc,0xfd,0xfe,0xcb,
/*C0*/ 0xee,0xa0,0xa1,0xe6,0xa4,0xa5,0xe4,0xa3,0xe5,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,
/*D0*/ 0xaf,0xef,0xe0,0xe1,0xe2,0xe3,0xa6,0xa2,0xec,0xeb,0xa7,0xe8,0xed,0xe9,0xe7,0xea,
/*E0*/ 0x9e,0x80,0x81,0x96,0x84,0x85,0x94,0x83,0x95,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,
/*F0*/ 0x8f,0x9f,0x90,0x91,0x92,0x93,0x86,0x82,0x9c,0x9b,0x87,0x98,0x9d,0x99,0x97,0x9a
};
char   alt_koi[] = {
/*80*/ 0xe1,0xe2,0xf7,0xe7,0xe4,0xe5,0xf6,0xfa,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,0xf0,
/*90*/ 0xf2,0xf3,0xf4,0xf5,0xe6,0xe8,0xe3,0xfe,0xfb,0xfd,0xff,0xf9,0xf8,0xfc,0xe0,0xf1,
/*A0*/ 0xc1,0xc2,0xd7,0xc7,0xc4,0xc5,0xd6,0xda,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,
/*B0*/ 0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
/*C0*/ 0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0xbf,0x9c,0x9d,0x9e,0x9f,
/*D0*/ 0xb9,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
/*E0*/ 0xd2,0xd3,0xd4,0xd5,0xc6,0xc8,0xc3,0xde,0xdb,0xdd,0xdf,0xd9,0xd8,0xdc,0xc0,0xd1,
/*F0*/ 0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xa0,0xba,0xbb,0xbc,0xbd,0xbe,0x9b
};
#endif RED_ALT

int charskh,charskl,charscol;   /* Положение символа ( для chars) */
#define NBYMAX 150      /* Макс. размер байтов для fsdbytes, +1 */
struct fsd *temp2fsd(),*delete(),*pick(),*blanklines(),*writemp(),*copyfsd();

/*
 * struct fsd *file2fsd(fname)
 * Создать цепочку описателей для файла fname
 */
struct fsd *file2fsd(fname)
int fname;
{
    charsin(fname,0,0);
    return temp2fsd(fname);
}

/* struct fsd *temp2fsd(chan)
 * - Разложить файл на fsd-цепь.
 * работает с текущего места в файле chan
 */
struct fsd *temp2fsd(chan)
int chan;
{
    register struct fsd *thisfsd, *lastfsd;
    struct fsd *firstfsd;
    register int nby;
    char *bpt; 
    int c;
    char fby[NBYMAX+1];
    int i,lct,nl,sh,sl,kh,kl;
    firstfsd = thisfsd = lastfsd = 0;
    /* основной цикл. c - очередной символ, но -1 означает
     * конец файла, а -2 - вход в цикл.
     */
    c = -2;
    sh = sl = 0;
#ifdef lint
    nby = 0; 
    nl = 0;
#endif
    FOREVER
        {
        if ( (c < 0) || (nby >= NBYMAX) || (nl == FSDMAXL))
        {
            if (c != -2)
            {
                lastfsd = thisfsd;
                thisfsd = (struct fsd *)salloc(nby + SFSD);
                if (firstfsd == 0) firstfsd = thisfsd;
                else lastfsd->fwdptr = thisfsd;
                thisfsd->backptr = lastfsd;
                thisfsd->fwdptr = (struct fsd *)0;
                thisfsd->fsdnlines = nl;
                nlines[chan] += nl;
                thisfsd->fsdfile = chan;
                thisfsd->seekhigh = sh;
                thisfsd->seeklow = sl;
                bpt = &(thisfsd->fsdbytes);
                for (i=0; i<nby; ++i) *(bpt++) = fby[i];
            }
            if (c == -1)
	    { /* Поместим блок конца и выйдем */
                thisfsd->fwdptr = lastfsd = (struct fsd *)salloc(SFSD);
                lastfsd->backptr = thisfsd;
                return (firstfsd);
            }
            sh = charskh;
            sl = charskl;
            nl = nby = lct = 0;
        }
        kh = charskh;
        kl = charskl;
        c = chars(0);
        lct = (charskl - kl) + 512 * (charskh - kh);
        if (c != -1 || lct) {
            if (lct > 127)
            {
                fby[nby++] = (lct / 128)|0200;
                lct = lct % 128;
            }
            fby[nby++] = lct;
            ++nl;
        }
    }
}

/*
 * Настройка программы чтения из файла
 */
#define ALIGBUF                 /* Читать по границе листа!! */
#define CHARBUFSZ 512           /* >= 512, если ALIGBUF */


int chkl,chkh;  /* position of next read from charsfi */
int charsfi,charsi,charsn;

/*
 * charsin(file,h,l) - настроить программу чтения символов "char" на
 * файл "fi" с позиции (h,l) = (блок, сдвиг).
 */
charsin(fi,h,l)
int fi,h,l;
{
    if (fi <= 0) {
        charsfi = fi;
        return;
    }
    if((charsfi != fi)||(chkh != h)||(l > chkl)||(l < chkl - charsn))
    {
        chkh = h;
        seek(fi,h,3);
#ifndef ALIGBUF
        seek(fi,l,1);
        chkl = l;
        charsi = charsn = 0;
#else ALIGBUF
        chkl = 0;
        charsi = l;
        charsn = 0;
#endif ALIGBUF
    }
    else charsi = charsn + l - chkl;
    ncline = 0;
    charsfi = fi;
    charskh = chkh;
    charskl = chkl + charsi - charsn;
    charskl=normhl(charskl, &charskh);
}

/*
 * int chars(flg)
 * Основная функция для чтения очередной строки из файла.
 * Управляется глобальными переменными chkх, chkl, и charsfi.
 * (сдвиг в файле и дескриптор).
 * Возвращает: последний символ либо -1 при конце файла.
 * Если flg = 1 - заполняется строка "cline".
 * Длина строки возвращается в ncline, с учетом символа конца.
 * Строка оканчивается символом LINE FEED или -1, если конец файла.
 * ============================================================
 * При вводе строка разворачивается из файловой в экранную форму.
 * При этом заменяются символы табуляции, неграфические символы,
 * а в режимах "lcase" или "lat" часть символов преобразуются в пару
 * символов.
 * Обратное преобразование (из экранной в файловую форму)
 * делается функцией "dechar".
 *
 * Если flg = 0 - строка не формируется, этот режим служит для
 * составления цепи дескрипторов.
 */
int chars(flg)
{       
    register char *c,*se;
    register int ko; 
    char *si, *so;
    static char charsbuf[CHARBUFSZ];
    if (charsfi <= 0)
    {
        if (lcline == 0) excline(1);
        ncline = 1;
        cline[0] = NEWLINE;
        return (NEWLINE);
    }
    so=cline;
    ko=(charsi>=charsn? 1 : 2 ) ;
    do
	{
        if (ko==1)
        { 
#ifndef ALIGBUF
            charsn=read(charsfi, charsbuf, CHARBUFSZ);
            charsi=0;
#else ALIGBUF
	    charsi -= charsn;
	    charsn=read(charsfi, charsbuf, CHARBUFSZ);
#endif ALIGBUF
            if(charsn<0) { 
                error(DIAG("Read Error","Oшибка чтения"));
                charsn=0;
            }
            chkl += charsn;
        }
        if (charsn<=charsi) { 
            ko=1; 
            break;
        }/* read buf empty */
        si=charsbuf+charsi; 
        se=charsbuf+charsn;
        if ( !flg)
        { 
            c=si;
            while ( *c++ !=NEWLINE && c != se);
            charsi=c-charsbuf;
            ko=(*(c-1)==NEWLINE ? 0 : 1 );
            continue;
        }
        while (!lcline||(ko=exinss(&si, se, &so, &ncline, lcline))==2)
        {
            ncline=so-cline; 
            excline(0); 
            so=cline+ncline;
        }
        charsi=si-charsbuf;
    } 
    while (ko);
    /* ko=0 - NEWLINE, 1 - end of file */
    chkl=normhl(chkl,&chkh);
    charskh  = chkh;
    charskl = chkl + charsi - charsn;
    charskl=normhl(charskl, &charskh);
    if (ko==1)
        charsfi = 0;
    /* Убрать хвостовые пробелы */
    if (flg)
    { 
        *so=' '; 
        c= so;
        while (*c==' ' && c--!=cline);
        *++c=NEWLINE;
        ncline=(c-cline)+1;
    }
    return( ko? -1 : NEWLINE);
}

#ifndef DEMOSES
static char *seit="\\\\\140'{(})|!~^";
#else +DEMOSES
/* Из зa oшибки в дpaйвepe cимвoлы 136 и 176 пepecтaвили !!!*/
static char *seit="\\\\\140'{(})|!^~";
static char *seit0="\\\\";
#endif +DEMOSES
extern int flgtabs;
extern int alltabs;
/*
 * exinss(&si,&se,&so,&no,&mo) -
 * Преобразование строки из внешней во внутреннюю форму.
 * *si - Текущий входной символ
 * *(se-1) - Последний ранее считанный входной символ
 * *so - текущее место в строке вывода
 *  no - текущая колонка на выводе, +1 (1, если пусто)
 *  mo - мaкc. нoмep кoлoнки в пoлyчeннoй cтpoкe
 *
 * Код ответа:
 *       0 - end of line
 *       1 - end of input string
 *       2 - the output line overflow
 */
exinss(si,se,so,no,mo)
char **si,*se,**so;
int *no,mo;
{
#ifndef DEMOSES
    register char *st, *sf; 
    register unsigned sy;
    int s,s1,n,i;
    char *sft;
    int ir=0;
    int no_head;  /* Не первые табуляции */
    sf= *si;
    st= *so;
    /*==== se +=1; ====*/
    n= *no;
    /* main loop */
    no_head = 0;
    while((sy= *sf&0377)!='\n' && sf!=se)
    {
#ifdef RED_ALT
   if ( Rcy_alt || Rcy_ALT ) {                            /* bvg */
       if ( sy >= 0x80 )                       /* bvg */
	   sy = alt_koi[sy - 0x80] & 0xFF;     /* bvg */
   }                                           /* bvg */
#endif RED_ALT
        if((n+2)>mo) {
            ir=2;
            break;
        }
	if ( sy != '\11' && sy != ' ' ) no_head = 1;
	if( (alltabs == 1 || no_head==0 ) && flgtabs && sy=='\11' )
        {
            i=(n&(~07))+8;
            if(i>mo) {
                ir=2;
                break;
            }
            for(; n<i; n++) *st++ =' ';
            goto next;
        }
        /* DEL */
        if(sy=='\177') {
            *st++ =esc0;
            *st++ ='#';
            n += 2;
            goto next;
        }
        /* CNTRL X */
        s1= (sy)&0340;
        if(s1==0)  {
            *st++ =esc0;
            *st++ =sy|0100;
            n += 2;
            goto next;
        }
        /* letters and sim. */
        if(s1!=040)
        {
            if(s1==0200||s1==0240||(sy==S_NO1)||(lcasef && sy==S_NO2))
	    if((sy==S_NO1)||(lcasef && sy==S_NO2))
            /* \377 */              {
                if (n+4>mo) {
                    ir=2;
                    break;
                }
                *st++ =esc0;
		*st++ =((sy>>6)&3) + '0';
		*st++ =((sy>>3)&7) + '0';
                *st++ =((sy) &7) + '0';
                n += 4;
                goto next;
            }
            /* russion letters */
            if (latf && ((sy&0300)==0300) )
            {
                *st++ = esc2;
                *st++ = (sy==0337?sy&0177:(sy&0177)^040);
                n += 2;
                goto next;
            }
            /* \A  A \( \) \! ... */
            if (lcasef)
            {
                *st=esc1;
                s= ((int)sy) & 0377;
                if (s>='A' && s<= 'Z')
                {
                    *++st = s;
                    st++;
                    n += 2;
                    goto next;
                }
                if (RLPRO(s))
                {
                    *++st = STK7(s);
                    st++;
                    n += 2;
                    goto next;
                }
                if (s>='a' && s<='z')
                {
                    *st++ = (s&0177) ^ 040;
                    n++;
                    goto next;
                }
                if (RLSTRO(s))
                {
                    *st++ = STK7(s);
                    n++;
                    goto next;
                }
                /* table twice chars */
                sft=sf;
                sf=seit;
                while ( *sf && *sf++!=sy) sf++;
                if( *sf) {
                    *++st = *sf;  
                    st++;
                    n += 2;
                    sf=sft;
                    goto next;
                }
                sf=sft;
            }
        }
        *st++ = sy;
        n++;
next:
        sf++;
    }
    ir= ( ir?  ir : ((sy=='\n')?(sf++,0):1) );
    *si=sf;
    *so=st;
    *no=n;
    *st=0;
    return(ir);
#else +DEMOSES
    register char *st, *sf; 
    register unsigned sy;
    int s,s1,n,i;
    char *sft;
    int ir=0;
    sf= *si;
    st= *so;
    /*==== se +=1; ====*/
    n= *no;
    /* main loop */
    while((sy= (*sf))!='\n' && sf!=se)
    {
        if((n+2)>mo) {
            ir=2;
            break;
        }
        if( sy=='\11' )
        {
            i=(n&(~07))+8;
            if(i>mo) {
                ir=2;
                break;
            }
            for(; n<i; n++) *st++ =' ';
            goto next;
        }
        /* DEL */
        if(sy=='\177') {
	    *st++ =esc1;
            *st++ ='#';
            n += 2;
            goto next;
        }
        /* letters and sim. */
	s1 = (sy)&0340;
        if(s1!=040)
        {
	    if(s1== 0 || s1==0200||s1==0240||(sy==S_NO1)||(lcasef && sy==S_NO2))
	    {
                if (n+4>mo) {
                    ir=2;
                    break;
                }
		*st++ =esc1;
		*st++ =((sy>>6)&3) + '0';
		*st++ =((sy>>3)&7) + '0';
		*st++ =((sy)&7) + '0';
                n += 4;
                goto next;
            }
            /* russion letters */
            if (latf && ((sy&0300)==0300) )
            {
                *st++ = esc2;
                *st++ = (sy==0337?sy&0177:(sy&0177)^040);
                n += 2;
                goto next;
            }
            /* \A  A \( \) \! ... */
            if (lcasef)
            {
                *st=esc1;
                s= ((int)sy) & 0377;
                if (s>='A' && s<= 'Z')
                {
                    *++st = s;
                    st++;
                    n += 2;
                    goto next;
                }
                if (RLPRO(s))
                {
		    *++st = s;
                    st++;
                    n += 2;
                    goto next;
                }
                if (s>='a' && s<='z')
                {
		    *st++ = s +('G'-'g') ;
                    n++;
                    goto next;
                }
                if (RLSTRO(s))
                {
		    *st++ = s +('Г'-'г') ;
                    n++;
                    goto next;
                }
                /* table twice chars */
                sft=sf;
		sf=speccase?seit:seit0;
                while ( *sf && *sf++!=sy) sf++;
                if( *sf) {
                    *++st = *sf;  
                    st++;
                    n += 2;
                    sf=sft;
                    goto next;
                }
                sf=sft;
            }
	   else if ( !(sy == ' ' || sy >= 'a' && sy <= 'z'
		      || sy >= 'A' && sy <='Z' || (sy&0300)==0300 ))
	    {
		    sft=sf;
		    sf= ( speccase? seit:seit0 );
		    *st = esc1;
		    while ( *sf && *sf++!=sy) sf++;
		    if( *sf) {
			*++st = *sf;
			st++;
			n += 2;
			sf=sft;
			goto next;
		    }
		    sf=sft;
	    }
        }
        *st++ = sy;
        n++;
next:
        sf++;
    }
    ir= ( ir?  ir : ((sy=='\n')?(sf++,0):1) );
    *si=sf;
    *so=st;
    *no=n;
    *st=0;
    return(ir);
#endif +DEMOSES
}


/*
 * dechars(line,n) -
 * Преобразование строки line из внутренней (экранной) формы
 * во внешнюю. Преобразование делается прямо в строке line.
 * n - длина строки. В строке должно быть не менее n+1 символов,
 * так как в конец полученной строки пишется NEWLINE.
 * Замена пробелов табуляциями управляется через flgtabs
 *      0 - нет, 1 - начальные табуляции, 2 - все пробелы.
 * Возвращает число символов в полученной строке.
 * Хвостовые пробелы исключаются.
 */
int dechars(line,n)
char *line;
int n;
{
    register char *fm,*to;  /* pointers for move */
    register unsigned cc;   /* current character */
    int lnb;       /* 1 + last non-blank col */
    int cn;                 /* col number */
    int i,j;
    char *to1;
    line[n] = NEWLINE;
    fm = to = line;
    cn = -1;
    lnb = 0;
    while ((cc = (*fm++&0377)) != NEWLINE)
    {
        cn++;
        if ( cc != ' ')
        {
            if(flgtabs==2 || flgtabs==1 && lnb==0)
                /* Пробелы заменяем табуляциями */
                while (8+(lnb&(~07)) <= cn)
                {
                    *to++ = (lnb&7)==7 ? ' ' : '\t';
                    lnb &= (~07);
                    lnb += 8;
                }
            while ( ++lnb <= cn ) *to++ = ' ';
            /* расшифровка символов */
#ifndef DEMOSES
            if (cc==esc0)
            {
                if( *fm >='@' || (unsigned)(*fm) > 0200 )
                {
                    *to++ = *fm++ & 037;
                    continue;
                }
                if ( *fm == '#') {
                    *to++ = '\177';
                    *fm++;
                    continue;
                }
                /* <esc>XXX */
                i=0;
                j=0;
                while (j++ <3 && (*fm >= '0' && *fm <= '7'))
                    i= (i<<3) + (*fm++ - '0');
                *to++ = i & 0377;
                continue;
            }
            else if (lcasef)
            {
                if (cc>='A' && cc<= 'Z')
                    cc=cc^040;
                else if (cc>=0140 && cc <= 0176 )
                    cc=K7TS(cc)^040;
                else if (cc==esc1 && (cc= *fm) !=NEWLINE )
                {
                    *fm++;
                    if (cc>=0140 && cc<=0176)
                        cc=K7TS(cc);
                    else if (cc<'A' || cc>'Z')
                    {
                        to1=to;
                        to=seit-1;
                        while (*++to && *++to != cc);
                        if (*to) cc= *--to;
                        to=to1;
                    }
                }
                *to++ =cc;
                continue;
            }
            else if (latf && cc==esc2 && *fm != NEWLINE )
            {
                cc= *fm++ ^ 0240;
                if (cc==0377) cc= 0337;
            }
            *to++ =cc;
        } /* while - continue - not skip */
    }
#else +DEMOSES
            /* расшифровка символов */
	    if (cc==esc1 && (*fm >= '0'&& *fm <='7'||*fm == '#') )
            {
                if ( *fm == '#') {
                    *to++ = '\177';
                    *fm++;
                    continue;
                }
                /* <esc>XXX */
                i=0;
                j=0;
                while (j++ <3 && (*fm >= '0' && *fm <= '7'))
                    i= (i<<3) + (*fm++ - '0');
                *to++ = i & 0377;
		continue;
            }
            else if (lcasef)
            {
                if (cc>='A' && cc<= 'Z')
                    cc=cc^040;
		else if (cc>=0340 && cc <= 0376 )
		    cc=cc^040;
                else if (cc==esc1 && (cc= *fm) !=NEWLINE )
                {
                    *fm++;
		    if ( cc >= 'a' && cc <= 'z' || RLSTRO(cc)) cc^=040;
		    else if (cc> ' ' && cc<'@' || cc>'Z' && cc<'a' || cc>'z'&& cc<'\177' )
                    {
                        to1=to;
                        to=seit-1;
                        while (*++to && *++to != cc);
                        if (*to) cc= *--to;
                        to=to1;
                    }
                }
                *to++ =cc;
                continue;
            }
	    else if ( cc == esc1 && (cc = *fm) != NEWLINE )
            {
                    *fm++;
		    if (cc> ' ' && cc<'@' || cc>'Z' && cc<'a' || cc>'z' && cc<'\177' )
                    {
                        to1=to;
			to=seit-1;
                        while (*++to && *++to != cc);
                        if (*to) cc= *--to;
                        to=to1;
                    }
            }
            else if (latf && cc==esc2 && *fm != NEWLINE )
            {
                cc= *fm++ ^ 0240;
                if (cc==0377) cc= 0337;
            }
            *to++ =cc;
        } /* while - continue - not skip */
    }
#endif +DEMOSES
    *to++ = NEWLINE;
#ifdef RED_ALT
   if ( Rcy_alt || Rcy_ALT ) {                      /* bvg */
       for(fm = line; fm < to ; fm++ ){             /* bvg */
	   if( (cc = (*fm & 0xff )) >= 0x80 )       /* bvg */
	      *fm = koi_alt[cc - 0x80] & 0xFF;      /* bvg */
       }                                            /* bvg */
   }                                                /* bvg */
#endif RED_ALT
    return (to - line);
}



/*
 * excline(n) -
 * расширить массив cline.
 * cline содержит текущую строку, причем
 * lcline - содержит максимальную длину массива cline;
 * ncline - длина текущей строки.
 */
excline(n)
int n;
{
    register int j;
    register char *tmp;
    j = lcline + icline;
    if (j < n) j = n;
    tmp = salloc(j+1);
    icline += icline >> 1;
    while (--lcline >= 0) tmp[lcline] = cline[lcline];
    lcline = j;
    if (cline != 0) free(cline);
    cline = tmp;
}

/*
 * putbks(col,n) -
 * вставить n пробелов в колонке col текущей строки
 */
putbks(col,n)
int col,n;
{
    register int i;
    if (n <= 0) return;
    if (col > ncline-1)
    {
        n += col - (ncline-1);
        col = ncline-1;
    }
    if (lcline <= (ncline += n)) excline(ncline);
    for (i = ncline - (n + 1); i >= col; i--) cline[i + n] = cline[i];
    for (i = col + n - 1; i >= col; i--) cline[i] = ' ';
}

static struct workspace *wkspline;
/*
 * wseek(wksp,lno) -
 * Установить файл и смещение для ввода строки nlo
 * из рабочего пространства wksp.
 * После этого chars(0) считает требуемую строку.
 * Код ответа = 1, если такой строки нет, 0 если ОК
 */
int wseek(wksp,lno)
struct workspace *wksp;
int lno;
{
    register char *cp;
    int h,i;
    register int j,l;
    /* Запоминаем координаты текущей строки */
    wkspline = wksp;
    clineno = lno;
    /* 1. Получим fsd, в котором "сидит" данная строка */
    if (wposit(wksp,lno)) return (1);
    /* Теперь вычислим смещение */
    h = wksp->curfsd->seekhigh;
    l = wksp->curfsd->seeklow;
    i = lno - wksp->curflno;
    cp = &(wksp->curfsd->fsdbytes);
    while (i-- != 0)
    {
        if ((j = *(cp++)) &0200)
        {
            l += 128*(j&0177);
            j = *(cp++);
        }
        l += j;
    }
    l=normhl(l, &h);
    charsin(wksp->curfsd->fsdfile,h,l);
    return (0);
}

/*
 * wposit(wksp,lno) -
 * Установить указатель curfsd структуры wksp на fsd,
 * к которому относится строка lno.
 */
wposit(wk,lno)
struct workspace *wk;
int lno;
{
    register struct workspace *wksp;
    wksp = wk;
    if (lno < 0) fatal("Wposit neg arg");
    while (lno >= (wksp->curflno + wksp->curfsd->fsdnlines))
    {
        if (wksp->curfsd->fsdfile == 0)
        {
            wksp->curlno = wksp->curflno;
            return (1);
        }
        wksp->curflno += wksp->curfsd->fsdnlines;
        wksp->curfsd = wksp->curfsd->fwdptr;
    }
    while (lno < wksp->curflno)
    {
        if ((wksp->curfsd = wksp->curfsd->backptr) == 0)
            fatal("Wposit 0 backptr");
        wksp->curflno -= wksp->curfsd->fsdnlines;
    }
    if (wksp->curflno < 0) fatal("WPOSIT LINE CT LOST");
    wksp->curlno = lno;
    return 0;
}

/*
 * switchfile(dir) -
 *  Переключиться на альтернативный файл.
 *  dir>0 - на следующий
 *  dir<0 - на предыдущий
 */
switchfile(dir)
{
    if ( dir >= 0 && *next_args && editfile(*next_args++,0,0,1,1) == 1 ) return;
    if (curwksp->next_wksp == curwksp)
    {
	helpview();
	return;
    }
    if ( dir >= 0 )
	      switchwksp(0);
    else
	      switchpwksp();
    out_lines(0,-1);
    poscursor(curwksp->ccol,curwksp->crow);
}

/*
 * switchwksp(make) -
 *  Переключить wksp на альтернативное.
 *  если make, то сделать новое wksp и вплести его в цепочку
 */
switchwksp(make)
{
    register struct workspace *tempwksp;
    curwksp->ccol = cursorcol;
    curwksp->crow = cursorline;
    if ( make && curwksp->next_wksp->wfile )
    {
	    tempwksp = (struct workspace *)salloc(SWKSP);
	    tempwksp->next_wksp = curwksp->next_wksp;
	    curwksp->next_wksp = tempwksp;
    }
    curwksp = curport->wksp = curwksp->next_wksp;
    curfile = curwksp->wfile;
}

/*
 * switchpwksp() -
 *  Переключить wksp на предыдущее wksp
 */
switchpwksp()
{
    register struct workspace *tempwksp;
    curwksp->ccol = cursorcol;
    curwksp->crow = cursorline;
    for(tempwksp = curwksp;
	tempwksp->next_wksp != curwksp;
	tempwksp = tempwksp->next_wksp
	);
    curwksp = curport->wksp = tempwksp;
    curfile = curwksp->wfile;
}

/*
 * openlines(from,number) -
 * Вставить со строки from number строк.
 */
openlines(from,number)
int from, number;
{
    if (from >= nlines[curfile]) return;
    nlines[curfile] += number;
    insert(curwksp,blanklines(number),from);
    redisplay((struct workspace *)NULL,curfile,from,from+number-1,number,from);
    poscursor(cursorcol,from - curwksp->ulhclno);
}

/*
 * openspaces(line,col,number, nl) -
 * Вставить пробелы, nubmer колонок, nl строк.
 */
openspaces(line,col,number, nl)
int line, col, number, nl;
{
    register int i,j;
    for (i=line;i<line+nl;i++)
    {
	getlineFlerov(i);
        putbks(col,number);
        fcline = 1;
	putline(1);
        if((j=i - curwksp->ulhclno)<= curport ->btext)
	    out_lines(j,j);
    }
    poscursor(col - curwksp->ulhccno, line - curwksp->ulhclno);
}

/*
 * splitline(line,col) -
 * Расщепить строку "line,col"
 */
splitline(line,col)
int line,col;
{
    register int nsave,colUTF8;
    register char csave;
    if (line >= nlines[curfile]) return;
    nlines[curfile]++;
    getlineFlerov(line);
    colUTF8 = tUTF8(col);
    if (col + colUTF8  >= ncline - 1) openlines(line+1,1);
    else
    {
	csave = cline[col+colUTF8];
	cline[col+colUTF8] = NEWLINE;
        nsave = ncline;
	ncline = col+colUTF8+1;
        fcline = 1;
	putline(1);
	cline[col+colUTF8] = csave;
	insert(curwksp,writemp(cline+col+colUTF8,nsave-col+colUTF8),line+1);
	redisplay((struct workspace *)NULL,curfile,line,line+1,1,line+1);
    }
    poscursor(col  - curwksp->ulhccno, line - curwksp->ulhclno);
    return;
}

/*
 * closelines(frum,number) -
 * Убрать строки из файла.
 * frum < 0 - не делать redisplay, from = -frum
 * (используется при "exec").
 */
closelines(frum,number)
int frum, number;
{
    register int n,from;
    register struct fsd *f;
    if ((from = frum) < 0) from = -from-1;
    if (from < nlines[curfile]) if ((nlines[curfile] -= number) <= from)
        nlines[curfile] = from + 1;
    f = delete(curwksp,from,from+number-1);
    if (frum >= 0) redisplay((struct workspace *)NULL,curfile,from,from+number-1,-number,from);
    insert(pickwksp,f,n = nlines[2]);
    redisplay((struct workspace *)NULL,2,n,n,number,-1);
    deletebuf->linenum = n;
    deletebuf->nrows = number;
    deletebuf->ncolumns = 0;
    nlines[2] += number;
    poscursor(cursorcol,from - curwksp->ulhclno);
    return;
}

/*
 * closespaces(line,col,number,nl) -
 * Убрать область из файла
 */
closespaces(line,col,number,nl)
int line, col, number, nl;
{
	pcspaces(line,col,number,nl,1);
}


/*
 * combineline(line,col) -
 * Слепить строку со следующей
 */
combineline(line,col)
int line,col;
{
    register char *temp;
    register int nsave,i,colUTF8;
    if (nlines[curfile] <= line-2) nlines[curfile]--;
    getlineFlerov(line+1);
    temp = salloc(ncline);
    for (i=0;i<ncline;i++) temp[i] = cline[i];
    nsave = ncline;
    getlineFlerov(line);
    colUTF8 = tUTF8(col);
    if (col+colUTF8+nsave > lcline) excline(col+colUTF8+nsave);
    for (i=ncline-1;i<col+colUTF8;i++) cline[i] = ' ';
    for (i=0;i<nsave;i++) cline[col+colUTF8+i] = temp[i];
    ncline = col+colUTF8 + nsave;
    fcline = 1;
    putline(1);
    free((char *)temp);
    delete(curwksp,line+1,line+1);
    redisplay((struct workspace *)NULL,curfile,line,line+1,-1,line+1);
    poscursor(col - curwksp->ulhccno, line - curwksp->ulhclno);
}

/*
 * picklines(from,number) -
 * взять строки из файла
 */
picklines(from,number)
int from, number;
{
    register int n;
    register struct fsd *f;
    f = pick(curwksp,from,from+number-1);
    redisplay((struct workspace *)NULL,curfile,from,from+number-1,0,-1); /* because of breakfsd */
    insert(pickwksp,f,n = nlines[2]);
    redisplay((struct workspace *)NULL,2,n,n,number,-1);
    pickbuf->linenum = n;
    pickbuf->nrows = number;
    pickbuf->ncolumns = 0;
    nlines[2] += number;
    poscursor(cursorcol,from - curwksp->ulhclno);
    return;
}

/*
 * pickspaces(line,col,number,nl) -
 * взять кусок из файла
 */
pickspaces(line,col,number,nl)
int line, col, number, nl;
{
	pcspaces(line,col,number,nl,0);
}

/*
 * pcspaces(line,col,number,nl,flg) -
 * Взять (flg=0) / убрать (flg = 1)
 * Общая функция
 */
pcspaces(line,col,number,nl,flg)
int line, col, number, nl, flg;
{
    register struct fsd *f1,*f2; 
    struct fsd *f0;
    char *linebuf, *bp;
    register int i;
    int j, n,line0,line1;
    int iUTF8, colUTF8, numberUTF8;
    putline(1);
    if (charsfi == tempfile) charsfi = 0;
    linebuf = salloc(2*number+1);    //UTF8 2* D0xx
    f0=f2=0; 
    line1 = (line0=line) + nl;
    while( nl = (line1 - line0))
    {
        if(nl > FSDMAXL) nl=FSDMAXL;
	f1 = (struct fsd *)salloc(SFSD+(2*number>127?nl*2:nl));  //UTF8 2* D0xx
        if(f2) {
            f2->fwdptr = f1; 
            f1->backptr = f2;
        } 
        else f0= f1;
        bp = &(f1->fsdbytes);
        f1->fsdnlines = nl;
        f1->fsdfile = tempfile;
        f1->seekhigh = tempfh;
        f1->seeklow = tempfl;
        for (j=line0;j<line0+nl;j++)
        {
	    getlineFlerov(j);
	    colUTF8 = tUTF8(col);
	    numberUTF8 = wUTF8(number,col);
	    if (col+number+colUTF8+numberUTF8 >= ncline)
            {
		if (col+number+colUTF8+numberUTF8 >= lcline) excline(col+number+colUTF8+numberUTF8+1);
		for (i=ncline-1;i<col+number+colUTF8+numberUTF8;i++) cline[i] = ' ';
		cline[col+number+colUTF8+numberUTF8] = NEWLINE;
		ncline = col + number+colUTF8+numberUTF8+ 1;
            }
	    if ( 0 != colUTF8 ) colUTF8 -= fUTF8(&cline[col+colUTF8-1])?1:0;
	    for (i=iUTF8=0;i<number+iUTF8;i++) { linebuf[i] = cline[col+colUTF8+i]; if ( fUTF8(&cline[col+colUTF8+i] )) iUTF8++ ; }
	    if ( UTF8_D0(linebuf[i-1]) ) i--;
	    linebuf[i] = NEWLINE;
            seek(tempfile,tempfh,3);
            seek(tempfile,tempfl,1);
            if (charsfi == tempfile) charsfi = 0;
	    write(tempfile,linebuf,n = dechars(linebuf,i));     //UTF8 n i
            if ( n > 127 ) *bp++ = (n/128)|0200;
            *bp++ = n%128;
            tempfl += n;
            tempfl=normhl(tempfl, &tempfh);
        }
        f2 = f1; 
        line0 = line0 + nl;
    }
    (f2->fwdptr = (struct fsd *)salloc(SFSD))->backptr = f2;
    nl = line1 - line;
    if (flg) for (j=line;j<line+nl;j++)
    {
	getlineFlerov(j);
        if (col+number >= ncline)
        {
            if (col+number >= lcline) excline(col+number+1);
            for (i=ncline-1;i<col+number;i++) cline[i] = ' ';
            cline[col+number] = NEWLINE;
            ncline = col + number + 1;
        }
	iUTF8   = wUTF8(number,col);
	for (i=col+number+tUTF8(col+number);i<ncline;i++)
	    cline[i-(number+iUTF8)] = cline[i];
	ncline -= number+iUTF8;
        fcline = 1;
	putline(1);
        if((i=j - curwksp->ulhclno) <= curport->btext)
	    out_lines(i,i);
    }
    insert(pickwksp,f0,n = nlines[2]);
    redisplay((struct workspace *)NULL,2,n,n,nl,-1);
    if (flg)
    {
        deletebuf->linenum = n;
        deletebuf->nrows = nl;
        deletebuf->ncolumns = number;
    }
    else
    {
        pickbuf->linenum = n;
        pickbuf->nrows = nl;
        pickbuf->ncolumns = number;
    }
    nlines[2] += nl;
    free(linebuf);
    poscursor(col - curwksp->ulhccno, line - curwksp->ulhclno);
}

/*
 * put(buf,line,col) -
 * Поместить на указанное место взятое "buf"
 * Если  buf->ncolumns == 0 , вставляются строки,
 * иначе прямоугольная область.
 */
put(buf,line,col)
struct savebuf *buf;
int line, col;
{
	if (buf->ncolumns == 0) plines(buf,line);
	else pspaces(buf,line,col);
}

/*
 * plines(buf,line) -
 * Поместить на указанное место строки из buf.
 * Должно быть buf->ncolumns == 0 .
 */
plines(buf,line)
struct savebuf *buf;
int line;
{
    int lbuf, cc, cl;
    struct fsd *w0, *w1;
    register struct fsd *f, *g;
    register int j;
    putline(1);
    cc = cursorcol;
    cl = cursorline;
    breakfsd(pickwksp, buf->linenum + buf->nrows,1);
    w1 = pickwksp->curfsd;
    breakfsd(pickwksp, buf->linenum,1);
    w0 = pickwksp->curfsd;
    f = g = copyfsd(w0,w1);
    lbuf = 0;
    while (g->fsdfile)
    {
        lbuf += g->fsdnlines;
        g = g->fwdptr;
    }
    insert(curwksp,f,line);
    redisplay((struct workspace *)NULL,curfile,line,line+lbuf,lbuf,line);
    poscursor(cc,cl);
    if ((nlines[curfile] += lbuf) <= (j=line+lbuf)) nlines[curfile] = j+1;
}

/*
 * pspaces(buf,line,col)    -
 * Поместить на указанное место взятое "buf"
 * Должно быть buf->ncolumns != 0 .
 */
pspaces(buf,line,col)
struct savebuf *buf;
int line, col;
{
    struct workspace *oldwksp;
    char *linebuf;
    int nc, i, j;
    int colUTF8,nclineUTF8;
    linebuf = salloc(nc=2*buf->ncolumns);     // UTF8 2* d0xx
    oldwksp = curwksp;
    for (i=0;i<buf->nrows;i++)
    {
        curwksp = pickwksp;
	getlineFlerov(buf->linenum + i);
//        if (ncline-1 < nc) for (j=ncline-1;j<nc;j++) cline[j] = ' ';
	if (ncline < nc) for (j=ncline;j<nc;j++) cline[j] = ' ';
	for (j=0; j<ncline-1 ;j++) linebuf[j] = cline[j];
//        for (j=0;j<nc;j++) linebuf[j] = cline[j];
        curwksp = oldwksp;
	nclineUTF8=ncline-1;
	getlineFlerov(line+i);
	colUTF8 = tUTF8(col);
	putbks(col+colUTF8,nclineUTF8);
//        putbks(col,nc);
//        for (j=0;j<nc;j++) cline[col+j] = linebuf[j];
	for (j=0;j<nclineUTF8 ;j++) cline[col+colUTF8+j] = linebuf[j];
        fcline = 1;
        putline(0);
        if ((j = line+i-curwksp->ulhclno) <= curport->btext)
	    out_lines(j,j);
    }
    free(linebuf);
    poscursor(col - curwksp->ulhccno, line - curwksp->ulhclno);
    return;
}

/* ========= Подпрограммы нижнего уровня ========
 *         = Для работы с описателями fsd =
 */
/*
 * insert(wksp,f,at) -
 * Вставить описатель f в файл, описываемый wksp,
 * перед строкой at.
 * Вызывающая программа должна вызвать redisplay с
 * соответствующими аргументами.
 * При вызове insert сбрасывается тек. строки и уст. в -1
 */
insert(wksp,f,at)
struct workspace *wksp;
struct fsd *f;
int at;
{
    register struct fsd *w0, *wf, *ff;
    putline(1);
    DEBUGCHECK;
    /* determine length of insert */
    ff = f;
    /* ln = 0;      */
    while (ff->fwdptr->fsdfile)
    {
        /*  ln += ff->fsdnlines;  */
        ff = ff->fwdptr;
    }
    /* ln += ff->fsdnlines; */
    breakfsd(wksp,at,1);
    wf = wksp->curfsd;
    w0 = wf->backptr;
    free((char *)ff->fwdptr);
    ff->fwdptr = wf;
    wf->backptr = ff;
    f->backptr = w0;
    wksp->curfsd = f;
    wksp->curlno = wksp->curflno = at;
    if (openwrite[wksp->wfile]) openwrite[wksp->wfile] = EDITED;
    catfsd(wksp);
    DEBUGCHECK;
}


/*
 * struct fsd *delete(wksp,from,to) -
 * Исключить указанные строки из wksp.
 * Возвращает указатель на fsd - цепь исключенных строк,
 * с добавленнык концевым блоком.
 * Требует redisplay.
 * При вызове delete сбрасывается тек. строки и уст. в -1
 */
struct fsd *delete(wksp,from,to)
struct workspace *wksp;
int from,to;
{
    struct fsd *w0;
    register struct fsd *wf,*f0,*ff;
    putline(1);
    breakfsd(wksp,to+1,1);
    DEBUGCHECK;
    wf = wksp->curfsd;
    breakfsd(wksp,from,1);
    f0 = wksp->curfsd;
    ff = wf->backptr;
    w0 = f0->backptr;
    wksp->curfsd = wf;
    wf->backptr = w0;
    f0->backptr = 0;
/* do both in one line */
    (ff->fwdptr = (struct fsd *)salloc(SFSD))->backptr = ff;
    /* w0->fwdptr ставится здесь */
    catfsd(wksp);
    openwrite[wksp->wfile]=  EDITED;
    DEBUGCHECK;
    return (f0);
}

/*
 * struct fsd *pick(wksp,from,to) -
 * Возвращает указатель на fsd - цепь указанных строк,
 * с добавленным концевым блоком.
 * Требует redisplay.
 */
struct fsd *pick(wksp,from,to)
struct workspace *wksp;
int from,to;
{
    struct fsd *wf;
    putline(1);
    breakfsd(wksp,to+1,1);
    wf = wksp->curfsd;
    breakfsd(wksp,from,1);
    return(copyfsd(wksp->curfsd,wf));
}


/*
 * struct fsd *breakfsd(w,n,reall) -
 * разломать fsd по строке n в пространстве
 * w. curlno = curflno при возврате, и curfsd указывает на первую
 * строку после разрыва (которая может быть строкой из конечного
 * блока). Исходный fsd остается, возможно, с неиспользуемым
 * остатком списка длин.
 * Если функция применяется к концу файла, текущая
 * позиция остается в конце файла, на конечном блоке.
 * Если указанная строка выходит за пределы файла, добавляются
 * описатели пустых строк (с каналом -1).
 * Если "reall=1" то блок перед разрывом переразмещается в памяти с
 * целью экономии места.
 * ВНИМАНИЕ: breakfsd может нарушить корректность указателей в  workspace.
 * Поэтому после всех операций нужно вызывать "redisplay".
 */
int breakfsd(w,n,reall)
struct workspace *w;
int n,reall;
{
    int nby,i,j,jj,k,offs,lfb0;
    register struct fsd *f,*ff;
    struct fsd *fn;
    register char *c;
    char *cc;
    DEBUGCHECK;
    if (wposit(w,n))
    {
        f = w->curfsd;
        ff = f->backptr;
        free((char *)f);
        fn = blanklines(n - w->curlno);
        w->curfsd = fn;
        fn->backptr = ff;
        if (ff) ff->fwdptr = fn; 
        else openfsds[w->wfile] = fn;
        wposit(w,n);
        return (1);
    }
    f = w->curfsd;
    cc = c = &f->fsdbytes;
    offs = 0;
    ff = f;
    nby = n - w->curflno;
    if (nby != 0)
    {
        /* get down to the nth line */
        for (i=0; i<nby; i++)
        {
            if ((j = *c++)&0200)
            {
                offs += 128*(j&0177);
                j = *c++;
            }
            offs += j;
        }
        /* now make a new fsd from the remainder of f */
        i = j = jj = f -> fsdnlines - nby; /* number of lines in new fsd */
        lfb0 = c - cc;
        cc = c;
        while (--i >= 0) if (*cc++&0200) {
            j++; 
            cc++; 
        }
        ff = (struct fsd *)salloc(SFSD + j);
        ff->fsdnlines = jj;
        ff->fsdfile = f->fsdfile;
        offs += f->seeklow;
        ff->seeklow = offs % 512;
        ff->seekhigh = f->seekhigh + offs/512;
        cc = &ff->fsdbytes;
        for (k=0; k<jj; k++) if ((*cc++ = *c++)&0200) *cc++ = *c++;
        if ((ff->fwdptr = f->fwdptr)) ff->fwdptr->backptr = ff;
        ff->backptr = f;
        f->fwdptr = ff;
        f->fsdnlines = nby;
        if (reall && (jj>4) && (f->backptr))
        {
            ff=(struct fsd *)salloc(SFSD+lfb0);
            *ff = *f; 
            c= &(ff->fsdbytes);  
            cc= &(f->fsdbytes);
            while (lfb0--) { 
                *c++ = *cc++; 
            }
            ff->backptr->fwdptr = ff->fwdptr->backptr = ff;
            free((char *)f); 
            f=ff; 
            ff=f->fwdptr;
        }
    }
    w->curfsd = ff;
    w->curflno = n;
    DEBUGCHECK;
    return (0);
}

/*
 * struct fsd *writemp(buf,n)
 * Дописать строку buf длиной n во врем. файл.
 * Возвращает описатель этой строки.
 */
struct fsd *writemp(buf,n)
char *buf;
int n;
{
    register struct fsd *f1,*f2;
    register char *p;
    if (charsfi == tempfile) charsfi = 0;
    if (tempfh)
    {
        seek(tempfile,tempfh,3);
        seek(tempfile,tempfl,1);
    }
    else seek(tempfile,tempfl,0);
    write(tempfile,buf,n = dechars(buf,n-1));
    /* now make fsd */
    f1 = (struct fsd *)salloc(2 + SFSD);
    f2 = (struct fsd *)salloc(SFSD);
    f2->backptr = f1;
    f1->fwdptr = f2;
    f1->fsdnlines = 1;
    f1->fsdfile = tempfile;
    f1->seekhigh = tempfh;
    f1->seeklow = tempfl;
    if (n<=127) f1->fsdbytes = n;
    else
    {
        p = &f1->fsdbytes;
	*p++ = (n / 128)|0200;
        *p = n % 128;
    }
    tempfl += n;
    tempfl=normhl(tempfl, &tempfh);
    return (f1);
}

/*
 * getlineFlerov(ln) -
 * Дай строку ln из текущего curwksp.
 * строка попадает в cline, длина - в ncline.
 * Атрибуты текущей строки запоминаются при вызове wseek
 */
getlineFlerov(ln)
int ln;
{
    if ( ncline > 1 ) clineexist = 1;
    if ( wkspline && wkspline->wfile == curwksp->wfile && clineno == ln )
	return(clineexist);
    if ( fcline ) putline(0);
    fcline = 0;
    clineexist = 1;
    if (wseek(curwksp, ln))
    {
        if (lcline == 0) excline(1);
        cline[0] = NEWLINE;
        ncline = 1;
	clineexist = 0;
    }
    else chars(1);
    return(clineexist);
}

/*
 * putline(nosave) -
 * Поместить строку из cline в curwksp, строка nl.
 * nosave > 0 - не сохранять строку
 */
putline(nosave)
int nosave;
{
    struct fsd *w0,*cl;
    register struct fsd *wf, *wg;
    register struct workspace *w;
    int i;
    int save_cline = 1;
    char flg;
    DEBUGCHECK;
    if (fcline == 0)
    {
	if ( nosave )
	    clineno = -1;
        return;
    }
    fcline = 0;
    w = wkspline;
#if 0
    ptl(w->wfile);
#endif
    if (nlines[w->wfile] <= clineno) nlines[w->wfile] = clineno + 1;
    cline[ncline-1] = NEWLINE;
    cl = writemp(cline,ncline);
    i = clineno;
    flg = breakfsd(w,i,1);
    wg = w->curfsd;
    w0 = wg->backptr;
    if (flg == 0)
    {
        breakfsd(w,i+1,0);
        wf = w->curfsd;
        free((char *)cl->fwdptr);
        cl->fwdptr = wf;
        wf->backptr = cl;
    }
    free((char *)wg);
    cl->backptr = w0;
    w->curfsd = cl;
    w->curlno = w->curflno = i;
    openwrite[w->wfile] = EDITED;
    /* К сожалению, dechars портит строку, так что придется сбросить буфер */
    clineno = -1;
    catfsd(w);
    redisplay(w,w->wfile,i,i,0,-1);
    if ( nosave ) clineno = -1;
    DEBUGCHECK;
}

/*
 * undoedit(f)
 * Отменить изменения текущей или последней измененной строки
 */
undoedit(f)
{
      int lno;
      struct workspace *wksp;
      if ( !fcline ) return(-1);
      lno = clineno;
      wksp = wkspline;
      fcline = 0; /* Сбросить признак изменения в строке */
      putline(1); /* И сбросить саму эту строку */
      redisplay(NULL, wksp->wfile,lno,lno,0,-1);
      return(0);
}

/*
 * struct fsd *copyfsd(f,end) -
 * Возвращает копию цепи fsd, от f до end, не включая end.
 * Если end = NULL - до конца файла.
 */
struct fsd *copyfsd(f,end)
struct fsd *f,*end;
{
    struct fsd *res,*ff,*rend;
    register int i;
    register char *c1,*c2;
    res = 0;
#ifdef lint
    rend = (struct fsd *)0; /* При первом заходе res = FALSE */
#endif
    while (f->fsdfile && f != end)
    {
        c1 = &f->fsdbytes;
        for (i = f->fsdnlines; i; i--) if (*c1++&0200) c1++;
        c2 = (char *)f; /* !!! Подсчет места !!!*/
        i = c1 - c2;
        ff = (struct fsd *)(c2 = salloc(i));
        c2 += i;
        while (i--) *--c2 = *--c1;
        if (res)
        {
            rend->fwdptr = ff;
            ff->backptr = rend;
            rend = ff;
        }
        else res = rend = ff;
        f = f->fwdptr;
    }
    if (res)
    {
        (rend->fwdptr = (struct fsd *)salloc(SFSD))->backptr = rend;
        rend = rend->fwdptr;
    }
    else res = rend = (struct fsd *)salloc(SFSD);
    if (f->fsdfile == 0) rend->seeklow = f->seeklow;
    return res;
}

/*
 * freefsd(f) -
 * Почистить цепочку fsd.
 */
freefsd(f)
struct fsd *f;
{
    register struct fsd *g;
    while (f) {
        g = f;
        f = f->fwdptr;
        free((char *)g);
    }
}

/*
 * blanklines(n) -
 * создай дескриптор n пустых строк
 */
struct fsd *blanklines(n)
int n;
{
    int i;
    register struct fsd *f,*g;
    register char *c;
    f = (struct fsd *)salloc(SFSD);
    while (n) {
        i = n > FSDMAXL ? FSDMAXL : n;
        g = (struct fsd *)salloc(SFSD + i);
        g->fwdptr = f;
        f->backptr = g;
        g->fsdnlines = i;
        g->fsdfile = -1;
        c = &g->fsdbytes;
        n -= i;
        while (i--) *c++ = 1;
        f = g;
    }
    return (f);
}

/*
 * catfsd(w)
 *  программа пытается слить несколько fsd - блоков в один
 *  для экономии памяти.
 *  делается попытка слить в один блок w->curfsd->backptr и
 *  w->curfsd, если они описывают смежную информацию.
 */
catfsd(w)
struct workspace *w;
{
    register struct fsd *f0, *f;
    struct fsd *f2;
    register char *c;
    char *cc;
    int i,j,l0=0 ,l1=0,lb0=0 ,lb1,dl,nl0,nl1,fd0,kod=0;
    /*      l0, l1 : число байтов в участке файла, описываемом f0,f;
     *      lb0,lb1: длина описателя длин в fsd
     *      nl0,nl1 : число строк в fsd */
    f=w->curfsd;
    if ((f0=f->backptr)==0) {
        openfsds[w->wfile]=f; 
        return(0);
    }
    f0->fwdptr = f;
    fd0=f0->fsdfile;
    nl0=f0->fsdnlines;
    while( fd0>0 && fd0==f->fsdfile && (nl0+(nl1=f->fsdnlines)< FSDMAXL))
    {
        i=f0->seekhigh;
        j=f->seekhigh;
        if (i>j || (j-i > 20 )) return(kod);
        dl=(j-i)*512 + f->seeklow - f0->seeklow;
        /*  подсчитываем длину блока, eсли она неизвестна */
        if (l0==0)
        {
            i=nl0;
            cc=c= &(f0->fsdbytes);
            while(i--)
            {
                if ((j= *c++)&0200) j= (j&0177)*128 + *c++;
                l0 += j;
            }
            lb0= c - cc;
        }
        if (dl != l0) return(kod);
#if 0
      ptff(openfsds[w->wfile]);
#endif
        /* сливаем два fsd  и пытаемся повторить */
        i=nl1;
	cc=c= &(f->fsdbytes);
	l1 = 0;
        while(i--)
        {
            if((j= *c++ ) &0200) j= (j&0177)*128 + *c++;
            l1 += j;
        }
        lb1 = c - cc;
        f2=f;
        f=(struct fsd *)salloc(SFSD + lb0 + lb1);
        *f = *f0;
        f->fwdptr = f2->fwdptr;
        w->curfsd=f;
        w->curflno -= nl0;
        nl0=f->fsdnlines = nl0 + nl1;
        c= &(f->fsdbytes);
        i=lb0;
        cc= &(f0->fsdbytes);
        while (i--) *c++ = *cc++;
        i=lb1;
        cc= &(f2->fsdbytes);
        while (i--) *c++ = *cc++;
        lb0 += lb1;
        l0 += l1;
        kod=1;
        free((char *)f2);
        free((char *)f0);
        f->fwdptr ->backptr =f;
        if( f0=f->backptr) f0->fwdptr = f;
        else openfsds[w->wfile]=f;
        f0=f;
        f=f0->fwdptr;
    }
#if 0
      ptff(openfsds[w->wfile]);
#endif
    return(kod);
}

/*
 * int normhl(ll, hh)
 * int ll,*hh;
 * Пересчитать номер блока и сдвиг (ll, hh) так,
 * чтобы ll указывал сдвиг в блоке hh.
 * hh пишется на место, ll возвращается
 */
int normhl(ll, hh)
int ll,*hh;
{
	register int l=ll,*h=hh;
	while(l<0) { 
		l += 512; 
		(*h)--; 
	}
	while(l>=512) { 
		l -= 512; 
		(*h)++; 
	}
	return(l);
}


/*
 * doreplace(line,m,jproc,pipef)
 * Заменить строки с "line" m строк, через фильтр jproc, канал pipef.
 */
doreplace(line,m,jproc,pipef)
int line,m,jproc,*pipef;
{       
    register struct fsd *e,*ee;
    register int l;
    int n;
    close(pipef[0]);
    putline(1);
    breakfsd(curwksp,line,0);
    if (m == 0) close(pipef[1]);
    else {
        m = fsdwrite(curwksp->curfsd,m,pipef[1]);
        if (m == -1) {
            error(DIAG("Can't write on pipe.","Ошибка записи в pipe."));
            kill(jproc,9);
        }       
    }
    while (wait(&n) != jproc);          /* wait for completion */
    if ((n & 0177400) == 0157400) {
        error(DIAG("Can't find program to execute.","Не найдена программа"));
        return; 
    }
    if ((n & 0177400) == 0177000 || (n & 0377) != 0) {
        error(DIAG("Abnormal termination of program.","Плохой код конца программы."));
        return; 
    }
    charsfi = -1;                   /* forget old position before fork */
    if (m) closelines(-1-line,m);
    charsin(tempfile,tempfh,tempfl);
    ee = e = temp2fsd(tempfile);
    tempfh = charskh;
    tempfl = charskl;
    if (e->fsdnlines) {
        l = 0;
        while (e->fsdfile) {
            l += e->fsdnlines;
            e = e->fwdptr;
        }
        insert(curwksp,ee,line);
        nlines[curfile] += l;
    }
    redisplay((struct workspace *)NULL,curfile,line,line+m,l-m,-1);
    poscursor(cursorcol,cursorline);
}

/*
 * execr(args) -
 * char **args
 * запустить команду с параметрами args
 */
execr(args)
char **args;
{
    execvp(*args,args);
    exit(0337); /* Код ответа согласован с doreplace */
}

#ifdef DEBUG
FILE *fd;
dumpfsd(file)
char *file;
{
    register int i;
    register struct workspace *w;
    static int first;
    int j;
    if ( !fd )
    {
	      if ( !file || !(fd=fopen(file,(first==0?"w":"a") )) )
		  fd = stdout;
	      first++;
    }
    fprintf(fd,"\n\n\n*** DUMP FSD *** *** ***\n");
    fprintf(fd,"cline=%s clineno=%d \n ncline=%d wkspline=%o fcline=%d\n",cline, clineno, ncline, wkspline, fcline);
    for (i = 0; i < MAXFILES; i++) if (openfsds[i])
    {
        fprintf(fd,"\n*** OPENFSDS[%d] - file %s\n",i,openfnames[i]);
	printfsd(openfsds[i],fd);
    }
    for (i = 0; i < nportlist; i++)
    {
        w = portlist[i]->wksp;
	fprintf(fd,"\nViewport #%d: wksp=%o FSD chain %d, current line %d at block %o,\n",
	    i,w,w->wfile,w->curlno,w->curfsd);
	fprintf(fd,"first line %d, ulhc (%d,%d)\n",w->curflno,w->ulhccno,
            w->ulhclno);
	for(j=0;j<=portlist[i]->btext;j++)
	{
		fprintf(fd,"cols[%d]=(%d,%d)%c",j,portlist[i]->firstcol[j],
		portlist[i]->lastcol[j],(j+1)%4?'\t':'\n');
	}
	fprintf(fd,"\n");
    }
    ptfree(fd);
    fflush(fd);
    /* if ( fd != stdout ) fclose(fd);        */
}

ptl(wf)
{
if ( !fd ) return;
fprintf(fd,"putline n=%d l=%d wfile=%d\n",clineno, ncline, wf);
return;
}

ptff(f) struct fsd *f;
{
	if ( !fd ) return;
	fprintf(fd,"Catfsd: f=\n");
	printfsd(f,fd);
}

/*  #ifndef WORK
 *  printfsd(f) -
 * Отладочная печать цепочек fsd
 */
printfsd(f,fd)
struct fsd *f;
    FILE *fd;
{
    register char *c;
    register int i,j;
    fprintf(fd,"\n**********");
    while (f) {
	fprintf(fd,"\nfsdnl=%d chan=%d hi=%d lo=%d at %o",
        f->fsdnlines,f->fsdfile,f->seekhigh,
        f->seeklow,f);
	if (f->fwdptr && f != f->fwdptr->backptr) fprintf(fd,"\n*** next block bad backpointer ***");
        c = &(f->fsdbytes);
        for (i=0; i<f->fsdnlines; i++) {
	    if ((i % 20) == 0) fprintf(fd,"\n");
	    j = *c++ & 0377;
	    if ( j > 128 ) j = 128*(j-128) + *c++;
	    fprintf(fd," %d",j);
        }
        f = f->fwdptr;
    }
}

/*
 * checkfsd() -
 * Проверка корректности цепочек fsd.
 */
checkfsd()
{
    register struct fsd *f;
    register int nl;
/*
    struct {
        int s0; 
        char *s1; 
    };
*/
    register char *g;
    char *gg;
    nl = 0;
    f = openfsds[curfile];
    while (f) {
        if (curwksp->curlno >=nl && curwksp->curlno <
            nl + f->fsdnlines && curwksp->curfsd != f &&
            curwksp->curfsd->backptr ) {
            fatal("CKFSD CURFSD LOST"); 
        }
        if (f->fwdptr && f->fwdptr->backptr != f) fatal("CKFSD BAD CHAIN");
	nl += f->fsdnlines;
        f = f->fwdptr;
    }
    allock();
}
#endif

