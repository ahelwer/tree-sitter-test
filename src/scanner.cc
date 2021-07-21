#include <tree_sitter/parser.h>
#include <cassert>

namespace {
  enum class TokenType {
    TURNSTILE,
    ARROW
  };

  TSSymbol to_symbol(TokenType e) {
    return static_cast<TSSymbol>(e);
  }

  struct Scanner {
    enum class LexState {
      CONSUME_LEADING_SPACE,
      VERTICAL_BAR,
      TURNSTILE,
      ARROW
    };

    bool scan(TSLexer* const lexer, const bool* const valid_symbols) {
      if (!(valid_symbols[to_symbol(TokenType::TURNSTILE)] || valid_symbols[to_symbol(TokenType::ARROW)])) {
        return false;
      }

      LexState state = LexState::CONSUME_LEADING_SPACE;
      START_LEXER();
      switch (state) {
        case LexState::CONSUME_LEADING_SPACE:
          if (' ' == lookahead) SKIP(LexState::CONSUME_LEADING_SPACE);
          if ('\t' == lookahead) SKIP(LexState::CONSUME_LEADING_SPACE);
          if ('\r' == lookahead) SKIP(LexState::CONSUME_LEADING_SPACE);
          if ('\n' == lookahead) SKIP(LexState::CONSUME_LEADING_SPACE);
          if ('|' == lookahead) ADVANCE(LexState::VERTICAL_BAR);
          END_STATE();
        case LexState::VERTICAL_BAR:
          if ('-' == lookahead) ADVANCE(LexState::TURNSTILE);
          END_STATE();
        case LexState::TURNSTILE:
          if ('>' == lookahead) ADVANCE(LexState::ARROW);
          ACCEPT_TOKEN(to_symbol(TokenType::TURNSTILE));
          END_STATE();
        case LexState::ARROW:
          ACCEPT_TOKEN(to_symbol(TokenType::ARROW));
          END_STATE();
        default:
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
