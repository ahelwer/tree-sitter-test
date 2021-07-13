#include <tree_sitter/parser.h>
#include <cassert>

namespace {
  enum TokenType {
    TURNSTILE,
    ARROW
  };

  struct Scanner {
    bool scan(TSLexer* const lexer, const bool* const valid_symbols) {
      if (valid_symbols[TURNSTILE] || valid_symbols[ARROW]) {
        while (lexer->lookahead == ' ') {lexer->advance(lexer, true);}
        if (lexer->lookahead == '|') {
          lexer->advance(lexer, false);
          if (lexer->lookahead == '-') {
            lexer->advance(lexer, false);
            if (lexer->lookahead == '>') {
              lexer->advance(lexer, false);
              lexer->result_symbol = ARROW;
              return true;
            } else {
              lexer->result_symbol = TURNSTILE;
              return true;
            }
          } else {
            return false;
          }
        } else {
          return false;
        }
      } else {
        return false;
      }
    }
  };
}

extern "C" {

  void* tree_sitter_test_external_scanner_create() {
    return new Scanner();
  }

  void tree_sitter_test_external_scanner_destroy(void* const payload) {
    Scanner* const scanner = static_cast<Scanner*>(payload);
    delete scanner;
  }

  unsigned tree_sitter_test_external_scanner_serialize(
    void* const payload,
    char* const buffer
  ) {
    return 0;
  }

  void tree_sitter_test_external_scanner_deserialize(
    void* const payload,
    const char* const buffer,
    unsigned const length
  ) { }

  bool tree_sitter_test_external_scanner_scan(
    void* const payload,
    TSLexer* const lexer,
    const bool* const valid_symbols
  ) {
    Scanner* const scanner = static_cast<Scanner*>(payload);
    return scanner->scan(lexer, valid_symbols);
  }
}
