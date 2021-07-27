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
    source_file: $ => repeat(choice($.map, $.proof, $._expr)),
    map: $ => seq($.quantification, $.arrow, $._expr),
    quantification: $ => seq($.identifier, $.in, $.identifier),
    proof: $ => prec.right(repeat1(seq($.proof_token, $._expr))),
    _expr: $ => choice($.identifier, $.number, $.infix_op),
    infix_op: $ => prec.left(1, seq($._expr, $.infix_op_symbol, $._expr)),
    infix_op_symbol: $ => choice($.turnstile, $.in, $.lt, $.gt),

    identifier: $ => /[a-zA-Z]+/,
    number: $ => /\d+/,
    in: $ => '\\in',
    lt: $ => '<',
    gt: $ => '>',
    proof_token: $ => seq(
      token(prec(1, '<')),
      token.immediate(/\d+/),
      token.immediate('>')
    ),
  }
});
