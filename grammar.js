module.exports = grammar({
  name: 'test',

  conflicts: $ => [
    [$.unit, $.lt],
    [$.proof_step, $.lt],
  ],

  rules: {
    source_file: $ => repeat($.unit),
    unit: $ => choice($.proof, $._expr),
    proof: $ => prec.right(repeat1($.proof_step)),
    proof_step: $ => seq($.proof_token, $._expr),
    _expr: $ => choice($.identifier, $.number, $._infix_op),
    _infix_op: $ => choice($.lt, $.gt),
    lt: $ => prec.left(seq($._expr, '<', $._expr)),
    gt: $ => prec.left(seq($._expr, '>', $._expr)),

    identifier: $ => /[a-zA-Z]+/,
    number: $ => /\d+/,
    proof_token: $ => prec.dynamic(1, seq(
      '<',
      $.proof_level,
      token.immediate('>'),
      $.proof_name,
    )),
    proof_level: $ => token.immediate(/\d+/),
    proof_name: $ => token.immediate(/\w*/)
  }
});
