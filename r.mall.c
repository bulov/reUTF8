/*
 *      Редактор RED.
 *
 * r.mall.c - Запрос/освобождение памяти.
 *            Программа взята из стандартной библиотеки,
 *            Изменен только режим отладки
 *      $Header: r.mall.c,v 4.20 90/05/22 23:22:24 alex Exp $
 *      $Log:	r.mall.c,v $
 * Revision 4.20  90/05/22  23:22:24  alex
 * First rev. red 4.2
 * 
 * Revision 4.10  90/02/05  19:52:37  alex
 * Base revision 4.1
 * 
 * Revision 4.1  88/03/31  22:05:54  alex
 * Версия 4.1 - обкатка на UTEC, СМ
 * 
 * Revision 3.1.2.1  87/06/19  17:01:55  alex
 * Start revision for red/4
 * 
 * Revision 3.6  87/06/05  23:51:15  alex
 * Добавлен roll для терминалов с sr/sf и отображение
 *  табуляций в режиме -t + всякая мелочь
 * 
 * Revision 3.5  87/06/04  23:44:25  alex
 * Scroll on -sr- or -al/dl- added
 * 
 * Revision 3.4  86/09/19  19:58:11  alex
 * Версия для СМ-1700
 * 
 * Revision 3.3  86/08/04  20:54:15  alex
 * Bepqh dk LMNQ/DELNQ 2
 * 
 * Revision 3.2  86/07/24  19:07:20  alex
 * Об'единены версии текстов для ЕС и СМ
 * 
 * Revision 3.1.1.1  86/06/05  00:07:48  alex
 * Отлажено_на_модели
 * 
 * Revision 3.1  86/04/20  23:43:55  alex
 * Базовая версия для ЕС.
 * 
 * Revision 3.1  86/04/20  23:43:55  alex
 * *** empty log message ***
 * 
 */

#include "r.defs.h"

#define debug

#ifdef debug
#define ASSERT(p) if(!(p))botch("p");else
botch(s)
char *s;
{
	printf("assertion botched: %s\n",s);
	fatal("Mallock DESTROIED\n");
}
#else
#define ASSERT(p)
#endif

/*	avoid break bug */
#ifdef pdp11
#define GRANULE 64
#else
#define GRANULE 0
#endif
/*      Монитор памяти
 *      Круговая стратегия размещения
 *      Работает с кусками свободной памяти, связанными в монотонно
 *      возрастающий список.
  *      Перед каждым блоком записан указатель на следующий блок.
  *      Блоки выравнены на границу слова (тип ALIGN)
  *      Младший бит указателя используется как признак "занято"
  *      (1 - занято, 0 - свободно).
  *      Дырки отмечаются как занятые блоки.
  *      Последний блок (на который указывает alloct) пуст и указывает
  *      на первый распределенный блок
  *
  *      ALIGN, NALIGN, BLOCK, BUSY, INT
  *      INT - целый тип, соответствыющий слову - указателю.
 */
#define INT int
#define ALIGN int
#define NALIGN 1
#define WORD sizeof(union store)
#ifdef UTEC
#define BLOCK (1024*4)
#else
#ifdef pdp11
#define BLOCK 256      /* a multiple of WORD*/
#else
#define BLOCK 1024
#endif
#endif UTEC
#define BUSY 1
#undef NULL
#define NULL 0
#define testbusy(p) ((INT)(p)&BUSY)
#define setbusy(p) (union store *)((INT)(p)|BUSY)
#define clearbusy(p) (union store *)((INT)(p)&~BUSY)

union store { union store *ptr;
	      ALIGN dummy[NALIGN];
	      int calloc;	/*calloc clears an array of integers*/
};

static	union store allocs[2];	/*initial arena*/
static	union store *allocp;	/*search ptr*/
static	union store *alloct;	/*arena top*/
static	union store *allocx;	/*for benefit of realloc*/
char	*sbrk();
#ifdef debug
allock()
{
    register union store *p;
    int x;
    x = 0;
    for(p= &allocs[0]; clearbusy(p->ptr) > p; p=clearbusy(p->ptr)) {
        if(p==allocp)
            x++;
    }
    ASSERT(p==alloct);
    return(x==1|p==allocp);
}
#endif

#ifdef debug
static ptflag=0;
ptfree(fd)
FILE *fd;
{ 
    register union store *p,*q;
    register int i=0;
    if (ptflag++) return;
    fprintf(fd,"\n FREE LIST:\n");
    ASSERT(allocp>allocs && allocp <= alloct);
    for (p=allocs; ;)   {
        if ( !testbusy(p->ptr) )
        {
	    fprintf(fd," 0%o( %d)\t%c", p,
		((int)p->ptr - (int)p) - (WORD), (++i%4?' ':012));
        }
        q = p;
        p = clearbusy(p->ptr);
	if ( p > q ) ASSERT( p <= alloct );
        else if ( q != alloct || p != allocs ) { 
	    fprintf(fd,"Corrupt arena\n");
            return;
        }
	else {fprintf(fd,"\n"); return;}
    }
}
#endif

