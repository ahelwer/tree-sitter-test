module.exports = grammar({
  name: 'test',

  rules: {
    source_file: $ => repeat(seq('op', $.def_eq, 'expr')),
    def_eq: $ => choice('==', '≜')
  }
});
