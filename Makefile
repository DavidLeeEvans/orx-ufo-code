# Makefile for ufo
# If you're running Mac, you can build using Xcode
# If you're running Linux, this Makefile should help you
# On Windows, use the Visual Studio project
# You need to have a compiled version of Orx for your platform in the lib/ folder

ODIR=obj
OUTDIR=Build
OUTPUT=$(OUTDIR)/ufo
SRC=src
CC=g++
FLAGS=-std=c++11 -c -o $(ODIR)/$(@F)
LD=-I inc/ -L lib/
# LIB=-l orx
LIB=-l orxd
OBJS=Ufo.o 
_OBJS=$(patsubst %, $(ODIR)/%, $(OBJS))

pixelshootout: copyassets $(_OBJS)
	$(CC) $(LD) $(_OBJS) $(LIB) -o $(OUTPUT)

copyassets:
	mkdir -p $(OUTDIR) $(ODIR)
	find data -name '*.png' -exec cp {} $(OUTDIR) \;
	cp -u bin/*.ini $(OUTDIR)

$(ODIR)/Ufo.o:
	$(CC) $(FLAGS) $(LD) $(SRC)/ufo.cpp
clean:
	rm -f $(OUTPUT) $(ODIR)/*.o

squeakyclean:
	rm -rf $(OUTPUT) $(ODIR)
