CFLAGS = -Wall -std=c99 -O2
SRC_FILES := src/LASTNAME1_LASTNAME2.c

dev: $(SRC_FILES)
	$(CC) $(CFLAGS) -Werror -Wextra -Wpedantic -g $(SRC_FILES) -o a.out

macos: $(SRC_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o a.out

windows: $(SRC_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o a.exe
