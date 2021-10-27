#! Инит-файл с полными комментариями доступен в
#! файле /usr/local/lib/red/init.dfltsrc
#! Для установки с обрезанными комментариями запустить ком. файл
#! /usr/local/lib/red/comm_remove
#
set help "$DSTDIR/red/help.dflt"
set delims " "
set lboard 2
#
# Описание клавиатуры редактора - вариант, совместимый с RED
#
keytab replace
#
# Стандартная часть описания - имеется в
# самом редакторе и не заменяется по Replace
#
# Rt ^M
# Rt "^J"
# Cl ":kl:^[^L"
# Cr ":kr:^[^R"
# Cu ":ku:^[^U"
# Cd ":kd:^[^D"
# Ch ":kh:^[^H"
# Tl "^B"
# Tr "^I"
# Bs "^?"
# Qc "^A"
# Qu "^[^?"
# En "^[= "
# He "^\"
#
# Ввод команд через  ^С:
#
En ^C           # ENter
L+ ^T           # Line+
L- ^W           # Line-
Ud ^U           # UnDo
Fo ^D           # FileOpen
Bg ^F           # BufGet
Bp ^G           # BufPut
Ec ^P           # ExecCmd
Rs ^L           # ReScreen
S+ ^R           # Search+
S- ^E           # Search-
Fs ^V           # FileSave
Bs ^H           # BackSpace
# Новые команды
Mc ^X           # Начать макро
$0 ^Y           # Выполни макро
Wz ^Z           # Увеличить окно
Ud ^U           # Отменить изменения строки
$$ ^]           # Выполнить макро (+буква)
#
# *** Вариант клавиатуры в режиме совместимости с RED ***
#
#
# Использование именованных управляющих клавиш
#
Tl kB           # TabLeft
P+ kN           # Page+
P- kP           # Page-
Li :kA:k2       # LineInsert
Ld :kL:k3       # LineDelete
Ch k1           # Home для терминалов без Home
En :kE:fE:k1    # ENter - идет после Home, и поэтому приоритетнее
Dc :kD:k5       # DeleteChar
Im :kI:k4       # InsertMode
L+ :kF:k6       # Line+
L- :kR:k7       # Line-
#
# Использование новых команд - верхняя клавиатура
#
Sp :Kf:F4       # (FIND)/(F4)   Find
As :Ks:F5       # (SELECT)/(F5) Select
Cb F6          # На начало
Wl F7          # Слово назад
Wr F8          # Слово вперед
Ce F9          # На конец
$1 F0          # Вернись к редактированию
He Kh          # (HELP) Справка
$0 Kd          # (DO)   Выполни макро
#     Определяем движение на строку над клавишами листания на VT-200
L- Ki          # (INSERT HERE) Назад на строку
L+ Kr          # (REMOVE) Вперед на строку

# Вызов макро - SHIFTED KEYS

$a S1
$b S2
$c S3
$d S4
$e S5
$f S6
$g S7
$h S8
$i S9
$j S0

# Ввод через функциональную клавиатуру
# -0- - -9-

Wc        ":f0:^[=0" # Сменить окно
En        ":f1:^[=1" # Ввод аргумента
S+        ":f3:^[=3" # Поиск вперед
Go        ":f4:^[=4" # Перейти на
Im        ":f5:^[=5" # Режим вставки
Dc        ":f6:^[=6" # Удалить символ
P+        ":f7:^[=7"  # Лист вперед
Li        ":f8:^[=8"  # Вставить строку
Bg        ":f9:^[=9"  # Взять буфер
T-        ":f.:^[=."  # Таб. назад
Fo        ":f-:^[=-"  # Открыть файл

# Ввод через GOLD - -2-:

Pl        ":f2kl:^[kl"  # Окно влево
Pr        ":f2kr:^[kr"  # Окно вправо
#
Ec        ":f2f0:^[^[=0" # Выполни команду
En        ":f2f1:^[^[=1" # Ввод аргумента
S-        ":f2f3:^[^[=3" # Поиск назад
Wm        ":f2f4:^[^[=4" # Создать окно
Ts        ":f2f5:^[^[=5" # Уст. табуляции
Lt        ":f2f6:^[^[=6" # Обрезать
P-        ":f2f7:^[^[=7" # Лист назад
Ld        ":f2f8:^[^[=8" # Иск. строку
Bp        ":f2f9:^[^[=9" # Положи буфер
Qc        ":f2f.:^[^[=." # Спец. символ
Fs        ":f2f-:^[^[=-" # Спаси файл
.

macro 1
go $1
.
# Доописываем верхние клавиши
termcap vt200 vt220 wyse85 vt300 vt340 vt200w vt220w wyse85w vt340w vt300w
vt-340:Ks=\E[4~:Kf=\E[1~:Kh=\E[28~:Kd=\E[29~:Ki=\E[2~:Kr=\E[3~:\
      :F1=\E[31~:F2=\E[32~:F3=\E[33~:F4=\E[34~:F6=\E[17~:F7=\E[18~:F8=\E[19~:\
      :F9=\E[20~:F0=\E[21~:kh=\E[26~:fE=\EOM:\
      :tc=%t:
.
termcap wyse99 wyse99w
wyse99:F1=\E[?5i:F2=\E[?3i:F3=\E[2i:F4=\E[@:F5=\E[M:F6=\E[17~:\
      :S1=[5i:S2=[?1i:S3=[0i:S4=[L:S5=[K:S6=[31~:S7=[32~:\
      :S8=[33~:S9=[34~:S0=[35~:\
      :F7=\E[18~:F8=\E[19~:F9=\E[20~:F0=\E[21~:fE=\EOM:tc=%t:
.
# Xenix-286 old
termcap xenix
xenix:F1=\E[Y:F2=\E[Z:F3=\E[a:F4=\E[b:F5=\E[c:F6=\E[d:\
	:F7=\E[e:F8=\E[f:F9=\E[g:F0=\E[h:S1=\E[i:\
	:CY:\
	:Ct=$DSTDIR/red/QWERTY8:\
	:S1=\E[k:S2=\E[l:S3=\E[m:S4=\E[n:S5=\E[o:S6=\E[p:S7=\E[q:S8=\E[r:\
	:S9=\E[s:S0=\E[t:\
	:tc=%t:
.
# Xenix 386
termcap xenix8
xenix8:F1=\E[Y:F2=\E[Z:F3=\E[a:F4=\E[b:F5=\E[c:F6=\E[d:\
	:F7=\E[e:F8=\E[f:F9=\E[g:F0=\E[h:S1=\E[i:\
	:S1=\E[k:S2=\E[l:S3=\E[m:S4=\E[n:S5=\E[o:S6=\E[p:S7=\E[q:S8=\E[r:\
	:S9=\E[s:S0=\E[t:\
	:CY:\
	:Ct=$DSTDIR/red/QWERTY8:\
	:gt=\0151\072\010\012<\007\0169\011\013;-3./:\
	:g2=\015\072\010\012<\014\0169\011\013;:\
	:me=\E[m:\
	:m1=\E[37m\E[46m\E[1m:\
	:m2=\E[44m\E[31m\E[1m:\
	:m3=\E[35m:\
	:m4=\E[37m\E[1m\E[41m:\
	:gs=\E[12m:ge=\E[10m:\
	:Cs=:Ce=:\
	:cu=\E[219g:\
	:li#25:co#80:\
	:us=\E[1m:ue=\E[m:\
	:pt:am:eo:\
	:C2:Nf#16:Nb#16:Mf=0123456789ABCDEF:Mb=0123456789ABCDEF:\
	:Cf=\E[2;%d;%dm:\
	:Fo=\E[7m:Fe=\E[m:me=\E[10m\E[m:\
	:cd=\E[J:ce=\E[K:cl=\E[H\E[J:\
	:cm=\E[%i%d;%dH:\
	:cr=^M:nl=^J:bl=^G:ta=^I:\
	:ho=\E[H:do=\E[B:up=\E[A:nd=\E[C:le=\E[D:bt=\E[Z:\
	:Ff=\E[S:Fr=\E[T:\
	:kb=^H:kB=\E[Z:\
	:k0=\E[L:k1=\E[F:kd=\E[B:kN=\E[G:kl=\E[D:k5=\E[E:\
	:kr=\E[C:kh=\E[H:ku=\E[A:kP=\E[I:k.=\177:\
	:f1=\E[M:f2=\E[N:f3=\E[O:f4=\E[P:f5=\E[Q:\
	:f6=\E[R:f7=\E[S:f8=\E[T:f9=\E[U:f0=\E[V:\
	:dc=\E[P:dl=\E[M:ic=\E[@:al=\E[L:\
	:k3=\E[a:k4=\E[L:
.
#
tabset "" 4 *4
set keys "+TSi"
