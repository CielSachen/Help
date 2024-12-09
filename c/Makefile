CFLAGS = -Wall -std=c99 -O2
SRC_FILES := main.c utils.c

dev: $(SRC_FILES)
	$(CC) $(CFLAGS) -Werror -Wextra -Wpedantic $(SRC_FILES) -o a.out

macos: $(SRC_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o a.out

windows: $(SRC_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o a.exe
