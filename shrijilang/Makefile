# ============================================================
# SHRIJILANG — INCREMENTAL BUILD SYSTEM
# ============================================================

CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -g -O0 \
	-Iinclude \
	-Isrc \
	-Ienv \
	-Ipragya \
	-Ikrst

OUT = sri

# ============================================================
# SOURCE FILES
# ============================================================

SRC = \
	src/token.c \
	src/ast.c \
	src/parser.c \
	gyaan/core/gyaan_engine.c \
	gyaan/data/gyaan_rules.c \
	src/interpreter.c \
    src/stdlib/std_list.c \
    src/stdlib/std_dict.c \
    src/stdlib/std_math.c \
    src/stdlib/std_file.c \
    src/stdlib/std_string.c \
    src/stdlib/std_time.c \
    src/stdlib/std_random.c \
    src/stdlib/std_path.c \
    src/stdlib/std_os.c \
    src/stdlib/std_env.c \
    src/stdlib/std_json.c \
    src/stdlib/std_http.c \
  	src/runtime.c \
	src/error.c \
	src/state.c \
	src/event.c \
	src/command.c \
	src/translator.c \
	src/example_builder.c \
	src/ai_router.c \
	src/ai_intent.c \
	src/atma_lekha.c \
	src/smriti.c \
	src/smriti_session.c \
	src/smriti_personal.c \
	src/main.c \
	env/env.c \
	src/lang/grammar/grammar_registry.c \
	src/lang/grammar/grammar_core.c \
	pragya/router/l3_router.c \
	pragya/niyu/niyu_core.c \
	pragya/sakhi/sakhi_core.c \
	pragya/mira/mira_core.c \
	krst/krst_core.c \
	krst/krst_router.c \
	krst/niyu_engine.c \
	krst/krst_print.c \
    krst/krst_json.c \
	src/fix_engine.c \
	src/fix_rules.c \
	src/fix_interactive.c \
	src/typo_engine.c \
	src/error_intelligence.c \
	src/decision_engine.c \
	src/user_config.c \
	src/nirman.c \
	src/normalize_engine.c \
	src/nirman_flow_engine.c \
	src/value_print.c \
   #  src/ast_debug.c
# ============================================================
# OBJECT FILES
# ============================================================

OBJ = $(SRC:.c=.o)

# ============================================================
# FINAL BUILD
# ============================================================

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OUT) -lreadline -lm -lssl -lcrypto
# ============================================================
# OBJECT BUILD RULE
# ============================================================

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ============================================================
# CLEAN
# ============================================================

clean:
	rm -f $(OUT)
	find . -name "*.o" -delete

# ============================================================
# RUN
# ============================================================

run: $(OUT)
	./$(OUT)

# ============================================================
# REBUILD
# ============================================================

rebuild: clean $(OUT)
