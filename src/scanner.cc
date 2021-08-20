#include <tree_sitter/parser.h>
#include <cwctype>
#include <cassert>

enum TokenType {
  TOKEN
};

extern "C" {
  void * tree_sitter_test_external_scanner_create() {
    return NULL;
  }

  void tree_sitter_test_external_scanner_destroy(void *payload) {
    // ...
  }

  unsigned tree_sitter_test_external_scanner_serialize(
    void *payload,
    char *buffer
  ) {
    return 0;
  }

  void tree_sitter_test_external_scanner_deserialize(
    void *payload,
    const char *buffer,
    unsigned length
  ) {
    // ...
  }

  enum class State {
    CONSUME,
    A,
    A_NULL,
    END_OF_FILE
  };

  bool tree_sitter_test_external_scanner_scan(
    void *payload,
    TSLexer *lexer,
    const bool *valid_symbols
  ) {
    State state = State::CONSUME;
    START_LEXER();
    eof = lexer->eof(lexer);
    switch (state) {
      case (State::CONSUME):
        if (eof) SKIP(State::END_OF_FILE);
        if (iswspace(lookahead)) SKIP(State::CONSUME);
        if ('a' == lookahead) ADVANCE(State::A);
        END_STATE();
      case (State::A):
        if (eof) SKIP(State::END_OF_FILE);
        if (0 == lookahead) ADVANCE(State::A_NULL);
        END_STATE();
      case (State::A_NULL):
        ACCEPT_TOKEN(TOKEN);
        if ('a' == lookahead) ADVANCE(State::A);
        END_STATE();
      case (State::END_OF_FILE):
        END_STATE();
      default:
        END_STATE();
    }
  }
}
