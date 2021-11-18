#
#
# Библиотека редактора red - справочные файлы и таблицы
# Всем этим компонентам место в /usr/local/lib/red
# termcap -> /usr/local/etc
#
# Здесь содержатся файлы трех типов
# 1. Таблицы кодировки (транслируются и запускаются).
# 2. Файлы инициализации редактора
# 3. Справочные файлы
# Кроме того, содержится файл termcap.
#
ALL =$(CYRTABS) $(INITABS) $(HELP)
HELP=help.*
INITABS=init.dflt init.xterm  init.xa init.xterm-256color
CYRTABS=Wyse75 VT200 PVT100 QWERTY8 alt alt-alt
DSTDIR=/usr/local
DSTCPU=re

all:  $(ALL)


Wyse75:  Wyse75.c
	cc Wyse75.c
	./a.out > Wyse75
	rm -f a.out

PVT100:PVT100.c
	cc PVT100.c
	./a.out > PVT100
	rm -f a.out

QWERTY8:  QWERTY8.c
	cc QWERTY8.c
	./a.out > QWERTY8
	rm -f a.out


alt-alt: alt-alt.c
	cc alt-alt.c
	./a.out > alt-alt
	rm -f a.out


alt: alt.c
	cc alt.c
	./a.out > alt
	rm -f a.out


lin:    lin.c
	cc lin.c
	./a.out > lin
	rm -f a.out


VT200:  VT200.c
	cc VT200.c
	./a.out > VT200
	rm -f a.out

install: all init.dflt.W help.dflt.W
	sudo rpl '$$DSTDIR' ${DSTDIR} <help.dflt.W >help.dflt
	sudo rpl '$$DSTDIR' ${DSTDIR} <init.dflt.W >init.dflt
	sudo mkdir -p $(DSTDIR)/red
	sudo cp $(ALL) $(DSTDIR)/red
#               for i in $(INITABS);do mv $(DSTDIR)/red/$$i $(DSTDIR)/red/$${i}src;sh comm_remove < $$i > $(DSTDIR)/red/$$i;done
#        -mkdir -p $(DSTDIR)/fonts
#        cp fontVT200 $(DSTDIR)/fonts/vt200
#        echo "Join 'termcap' and you '/usr/local/etc/termcap' OR '/etc/termcap'"
	 sudo tic xterm-256color.infocmp

rinstall: all
	-rsh $(DSTCPU) mkdir $(DSTDIR)/lib/red
	rcp $(ALL) $(DSTCPU):$(DSTDIR)/lib/red
	-rsh $(DSTCPU) mkdir $(DSTDIR)/lib/fonts
	rcp fontVT200 $(DSTCPU):$(DSTDIR)/lib/fonts/vt200
	echo "Join 'termcap' and you '$(DSTCPU):/usr/local/etc/termcap' OR '$(DSTCPU):/etc/termcap'"
