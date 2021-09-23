module.exports = grammar({
  name: 'test',
  
  externals: $ => [
    $.external_token
  ],

  rules: {
    source_file: $ => repeat(seq($.external_token, $.codepoint)),
    codepoint: $ => choice('x', '∧')
  }
});
