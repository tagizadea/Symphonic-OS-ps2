EE_BIN = ./bin/output.elf
EE_OBJS = ./src/main.o ./src/pad.o ./src/appman.o ./src/simple_gui.o
EE_LIBS = -L/usr/local/ps2dev/ps2sdk/ports/lib -L/usr/local/ps2dev/gsKit/lib -L/usr/local/ps2dev/ps2sdk/ee/lib
EE_LIBS += -lc -lm
EE_LIBS += -ldebug -lkernel -lgskit -ldmakit -lcdvd
EE_LIBS += -lfreetype -lpng -lz -lrm
EE_LIBS += -lmtap -lpad -laudsrv -lps2stuff -lmc
EE_LIBS += -lSDL2main -lSDL2_mixer -lSDL2 -lSDL2_ttf
EE_LIBS += -lps2_drivers -lmodplug -lstdc++
EE_INCS = -I/usr/local/ps2dev/ps2sdk/ports/include/ -I/usr/local/ps2dev/gsKit/include -I/usr/local/ps2dev/ps2sdk/ports/include/freetype2/
EE_INCS += -I./include
EE_CFLAGS += -U_XPAD -DUSE_RWOPS
all: $(EE_BIN) clean
	$(EE_STRIP) --strip-all $(EE_BIN)

clean:
	rm -f $(EE_OBJS)

iso:
	mkisofs -o bin.iso -V MY_APP -sysid PLAYSTATION bin/


include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal_cpp
