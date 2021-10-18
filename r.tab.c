






{
int cmd_zz;
int cmd_cmd;
} cmd_names[] =
{
/* ВВод / Return */
ZZ(R,t),    CC+RN,              /* ReTurn       */
/* Команды движения курсора */
CC+RT,              /* CursorRight  */
ZZ(C,+),    CC+RT,              /* CursorRight  */
ZZ(C,u),    CC+UP,              /* CursorUp     */
				/* CursorBegin  */
				/* CursorEnd    */
/* Работа с табуляциями */
ZZ(T,-),    CC+BT,              /* TabLeft    */
ZZ(T,l),    CC+BT,              /* TabLeft    */
ZZ(T,r),    CC+TB,              /* TabRight   */
ZZ(T,+),    CC+TB,              /* TabRight   */
ZZ(T,s),    CCTABS,             /* TabSet     */
				/* TabClean   */
				/* TabInit    */
/* Работа по словам     */
				/* WordLeft   */
				/* WordRight  */
				/* WordSelect */
				/* WordGet    */
/* Команды движения по файлу */
ZZ(P,+),    CCPLPAGE,           /* Page+    */
ZZ(L,+),    CCPLLINE,           /* Line+    */
ZZ(P,r),    CCRPORT,            /* PageRight*/
ZZ(P,-),    CCMIPAGE,           /* Page-    */
ZZ(L,-),    CCMILINE,           /* Line-    */
ZZ(P,l),    CCLPORT,            /* PageLeft */
ZZ(G,o),    CCGOTO,             /* GOto     */
/* Команды поиска по шаблону */
ZZ(S,+),    CCPLSRCH,           /* Search+  */
ZZ(S,-),    CCMISRCH,           /* Search-  */
				/* SearchP  */
/* Команды редактирования строки */
ZZ(D,c),    CCDELCH,                    /* DelChar */
ZZ(B,s),    CCBACKSPACE,                /* BackSpace */
ZZ(I,m),    CCINSMODE,                  /* InsertMode*/
ZZ(Q,c),    CCCTRLQUOTE,/* QuoteChar */
/* Команды работы с окнами */
ZZ(W,c),    CCCHPORT,                   /* WindChange */
ZZ(W,m),    CCMAKEPORT,                 /* WindMake   */
/* Команды работы со строками и группами строк */
ZZ(L,i),    CCOPEN,                     /* LineInsert */
ZZ(L,d),    CCCLOSE,                    /* LineDelete */
					/* LineErase  */
ZZ(L,t),    CCTRUNCATE,                 /* LineTruncate */
					/* LineSplit  */
					/* LineJoin   */
ZZ(B,g),    CCPICK,                     /* BufGet     */
ZZ(B,p),    CCPUT,                      /* BufPut     */
					/* BufReplace  */
/* Команды работы с файлами */
ZZ(F,o),    CCSETFILE,                  /* FileOpen   */
ZZ(F,s),    CCSAVEFILE,                 /* FileSave   */
					/* FileChange */
/* Разные команды */
ZZ(E,c),    CCDOCMD,                    /* ExecCmd */
ZZ(E,n),    CCENTER,                    /* ENter   */
ZZ(Q,u),    CCQUIT,                     /* QUit    */
ZZ(R,s),    CCRESCREEN,                 /* ReScreen */
ZZ(H,e),    CCHELP,                     /* HElp     */
/* Работа с макро */
ZZ(M,c),    CCDEFMACRO,                 /* MacroCreate */
ZZ(M,s),    CCSAVEMACRO,                /* MacroSave   */
ZZ(M,r),    CCREADMACRO,                /* MacroRead   */
/* Конец таблицы */
0, 0 };

