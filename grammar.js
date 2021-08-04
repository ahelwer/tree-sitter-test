module.exports = grammar({
  name: 'test',

  conflicts: $ => [
    [$._unit, $.lt],
    [$.proof_step, $.lt],
  ],

  precedences: $ => [
    ['13-13', '10-10', '5-5']
  ],

  rules: {
    source_file: $ => repeat($._unit),
    _unit: $ => choice($.proof, $._expr),
    proof: $ => prec.right(repeat1($.proof_step)),
    proof_step: $ => seq($.proof_token, $._expr),
    _expr: $ => choice($.identifier, $.number, $._infix_op),
    _infix_op: $ => choice($.lt, $.gt, $.add, $.mul),
    lt: $ => prec.left('5-5', seq($._expr, '<', $._expr)),
    gt: $ => prec.left('5-5', seq($._expr, '>', $._expr)),
    add: $ => prec.left('10-10', seq($._expr, '+', $._expr)),
    mul: $ => prec.left('13-13', seq($._expr, '*', $._expr)),

    identifier: $ => /[a-zA-Z]+/,
    number: $ => /\d+/,
    proof_token: $ => prec.dynamic(1, seq(
      '<',
      alias(token.immediate(/\d+/), $.level),
      token.immediate('>'),
      alias(token.immediate(/\w*/), $.name),
    )),
  }
});
