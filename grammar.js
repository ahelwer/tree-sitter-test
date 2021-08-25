module.exports = grammar({
  name: 'test',

  rules: {
    source_file: $ => repeat($.string),

    string: $ => seq(
      '"',
      repeat(choice(
        token.immediate(/[^\n"]/),
        $.escape_char
      )),
      token.immediate('"')
    ),

    escape_char: $ => seq(
      token.immediate('\\'),
      token.immediate(/./)
    ),
  }
});
