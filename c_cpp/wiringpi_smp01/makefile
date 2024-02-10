#生成する実行ファイル名
TARGET = wiringpi_smp01
#.oファイル生成用の中間フォルダ
OBJSDIR = ./obj
#ヘッダインクルードフォルダ
MYINCDIR = ./inc

#コンパイル対象とするCファイル
OBJS = wiringpi_smp01.o\

#コンパイル用コマンド (c++ならばg++に変更)
CC = gcc
#Wall:警告をすべて出力、-g:デバッグ情報出力、GNU_SOURCE:非標準拡張機能の有効化
CFLAGS = -Wall -g -std=c99 -D_GNU_SOURCE
#lwiringPi:GPIOライブラリ有効化
LDFLAGS = -lwiringPi
INCDIR = -I$(MYINCDIR)

OBJS_ALL = $(addprefix $(OBJSDIR)/, $(OBJS))

all:
	mkdir -p $(OBJSDIR)
	make $(TARGET)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< $(INCDIR) -o $@
	mv $@ $(OBJSDIR)/$@
#$< 依存関係の一番最初の名前
#$@ ルールのターゲットの名前

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS_ALL) $(LDFLAGS)

clean:
	rm -f *.o
	rm -f $(OBJSDIR)/*.o
	rm $(TARGET)
