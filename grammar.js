module.exports = grammar({
  name: 'test',

  conflicts: $ => [
    [$.quantification, $._expr]
  ],

  externals: $ => [
    $.turnstile,
    $.arrow
  ],

  rules: {
    source_file: $ => choice($.map, $._expr),

    in: $ => '\\in',
    gt: $ => '>',

    map: $ => seq($.quantification, $.arrow, $._expr),
    quantification: $ => seq($.identifier, $.in, $.identifier),
    identifier: $ => /[a-zA-Z]+/,
    _expr: $ => choice($.identifier, $.infix_op),
    infix_op: $ => prec.left(1, seq($._expr, $.infix_op_symbol, $._expr)),
    infix_op_symbol: $ => choice($.turnstile, $.in, $.gt),
  }
});
