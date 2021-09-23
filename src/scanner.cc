#include <tree_sitter/parser.h>
#include <cstdio>

enum TokenType {
  EXTERNAL_TOKEN
};

extern "C" {
  void * tree_sitter_test_external_scanner_create() { return NULL; }
  void tree_sitter_test_external_scanner_destroy(void *payload) {}
  unsigned tree_sitter_test_external_scanner_serialize(void *payload, char *buffer) { return 0; }
  void tree_sitter_test_external_scanner_deserialize(void *payload, const char *buffer, unsigned length) {}

  bool tree_sitter_test_external_scanner_scan(
    void *payload,
    TSLexer *lexer,
    const bool *valid_symbols
  ) {
    while (' ' == lexer->lookahead) { lexer->advance(lexer, true); }
    uint32_t col = lexer->get_column(lexer);
    printf("NEXT: [%X] COL: [%d]\n", lexer->lookahead, col);
    printf("MATCH? [%d] [%d] [%d]\n", L'∧', L'\u2227', '\u2227' == lexer->lookahead);
    return !lexer->eof(lexer);
  }
}
