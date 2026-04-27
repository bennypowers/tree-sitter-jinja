#include "tree_sitter/parser.h"

enum TokenType {
  RAW_TEXT,
  COMMENT_CONTENT,
};

void *tree_sitter_jinja_external_scanner_create(void) {
  return NULL;
}

void tree_sitter_jinja_external_scanner_destroy(void *payload) {}

unsigned tree_sitter_jinja_external_scanner_serialize(void *payload,
                                                      char *buffer) {
  return 0;
}

void tree_sitter_jinja_external_scanner_deserialize(void *payload,
                                                    const char *buffer,
                                                    unsigned length) {}

static bool is_whitespace(int32_t c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static bool check_endraw(TSLexer *lexer) {
  if (lexer->lookahead != 'e') return false;
  lexer->advance(lexer, false);
  if (lexer->lookahead != 'n') return false;
  lexer->advance(lexer, false);
  if (lexer->lookahead != 'd') return false;
  lexer->advance(lexer, false);

  if (lexer->lookahead == 'r') {
    lexer->advance(lexer, false);
    if (lexer->lookahead != 'a') return false;
    lexer->advance(lexer, false);
    if (lexer->lookahead != 'w') return false;
    lexer->advance(lexer, false);
  } else if (lexer->lookahead == 'v') {
    lexer->advance(lexer, false);
    if (lexer->lookahead != 'e') return false;
    lexer->advance(lexer, false);
    if (lexer->lookahead != 'r') return false;
    lexer->advance(lexer, false);
    if (lexer->lookahead != 'b') return false;
    lexer->advance(lexer, false);
    if (lexer->lookahead != 'a') return false;
    lexer->advance(lexer, false);
    if (lexer->lookahead != 't') return false;
    lexer->advance(lexer, false);
    if (lexer->lookahead != 'i') return false;
    lexer->advance(lexer, false);
    if (lexer->lookahead != 'm') return false;
    lexer->advance(lexer, false);
  } else {
    return false;
  }

  return is_whitespace(lexer->lookahead) ||
         lexer->lookahead == '%' ||
         lexer->lookahead == '-' ||
         lexer->lookahead == '~';
}

static bool scan_raw_text(TSLexer *lexer) {
  bool has_content = false;

  while (lexer->lookahead != 0) {
    if (lexer->lookahead == '{') {
      lexer->mark_end(lexer);
      lexer->advance(lexer, false);

      if (lexer->lookahead == '%') {
        lexer->advance(lexer, false);

        if (lexer->lookahead == '-' || lexer->lookahead == '~') {
          lexer->advance(lexer, false);
        }

        while (is_whitespace(lexer->lookahead)) {
          lexer->advance(lexer, false);
        }

        if (check_endraw(lexer)) {
          lexer->result_symbol = RAW_TEXT;
          return has_content;
        }
      }

      lexer->mark_end(lexer);
      has_content = true;
    } else {
      lexer->advance(lexer, false);
      lexer->mark_end(lexer);
      has_content = true;
    }
  }

  return false;
}

static bool scan_comment_content(TSLexer *lexer) {
  bool has_content = false;

  while (lexer->lookahead != 0) {
    if (lexer->lookahead == '-' || lexer->lookahead == '~') {
      lexer->mark_end(lexer);
      lexer->advance(lexer, false);

      if (lexer->lookahead == '#') {
        lexer->advance(lexer, false);
        if (lexer->lookahead == '}') {
          lexer->result_symbol = COMMENT_CONTENT;
          return has_content;
        }
        lexer->mark_end(lexer);
        has_content = true;
      } else {
        lexer->mark_end(lexer);
        has_content = true;
      }
    } else if (lexer->lookahead == '#') {
      lexer->mark_end(lexer);
      lexer->advance(lexer, false);

      if (lexer->lookahead == '}') {
        lexer->result_symbol = COMMENT_CONTENT;
        return has_content;
      }

      lexer->mark_end(lexer);
      has_content = true;
    } else {
      lexer->advance(lexer, false);
      lexer->mark_end(lexer);
      has_content = true;
    }
  }

  return false;
}

bool tree_sitter_jinja_external_scanner_scan(void *payload, TSLexer *lexer,
                                             const bool *valid_symbols) {
  if (valid_symbols[RAW_TEXT]) {
    return scan_raw_text(lexer);
  }

  if (valid_symbols[COMMENT_CONTENT]) {
    return scan_comment_content(lexer);
  }

  return false;
}
